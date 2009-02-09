/*
* dvgrab.cc -- DVGrab control class
* Copyright (C) 2003 Dan Dennedy <dan@dennedy.org>
* Major rewrite of code based upon older versions of dvgrab by Arne Schirmacher
*    and some Kino code also contributed by Charles Yates.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


#include <iostream>
#include <sstream>
#include <iomanip>
using std::cerr;
using std::endl;

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <sys/select.h>
#include <libavc1394/avc1394.h>
#include <libavc1394/avc1394_vcr.h>
#include <libavc1394/rom1394.h>

#include "error.h"
#include "dvgrab.h"
#include "raw1394util.h"


extern bool g_done;
pthread_mutex_t DVgrab::capture_mutex;
pthread_t DVgrab::capture_thread;
pthread_t DVgrab::watchdog_thread;
Frame *DVgrab::m_frame;
FileHandler *DVgrab::m_writer;


DVgrab::DVgrab() :
		m_program_name( "ofDVgrab" ), m_port( -1 ), m_node( -1 ), m_showstatus( false ), m_hdv( false ), m_reader_active( false ), m_autosplit( false ),
		m_timestamp( false ), m_channel( DEFAULT_CHANNEL ), m_frame_count( DEFAULT_FRAMES ),
		m_max_file_size( DEFAULT_SIZE ), m_collection_size( DEFAULT_CSIZE ),
		m_collection_min_cut_file_size( DEFAULT_CMINCUTSIZE ), m_sizesplitmode ( 0 ),
		m_file_format( DEFAULT_FORMAT ), m_open_dml( false ), m_frame_every( DEFAULT_EVERY ),
		m_deinterlace( 0 ), m_dropped_frames( 0 ), m_buffers( DEFAULT_BUFFERS ), m_total_frames( 0 ),
		m_duration( "" ), m_noavc( false), m_guid( 0 ), m_timesys( false ), m_connection( 0 ),
		m_raw_pipe( false ), m_no_stop( false ), m_timecode( false ), m_lockstep( false ), m_lockPending( false ),
		m_lockstep_maxdrops( DEFAULT_LOCKSTEP_MAXDROPS ), m_lockstep_totaldrops( DEFAULT_LOCKSTEP_TOTALDROPS ), m_isLastTimeCodeSet( false ),
		m_isLastRecDateSet( false ), m_v4l2( false ), m_jvc_p25( false ),
		m_24p( false ), m_24pa( false ), m_timeSplit(0), m_srt( false ), m_isNewFile(false), m_isRecordMode( false ),
		m_isRewindFirst( false ), m_captureActive( false ), m_avc( 0 ), m_reader( 0 ), pixels(NULL), newFrame(false)
{
	m_frame = 0;
	m_writer = 0;
	m_input_file_name = NULL;
	m_dst_file_name = "thepicture";


	if ( m_v4l2 )
	{
		if ( !m_input_file_name )
			m_input_file_name = DEFAULT_V4L2_DEVICE;
	}
	else
	{

		if ( ! m_input_file_name && ( ! m_noavc || m_port == -1 ) ) {
			m_node = discoverAVC( &m_port, &m_guid );
		}

		if ( ( ! m_input_file_name ) && ( ! m_noavc && m_node == -1 ) ) {
			printf("no camera exists\n");
			cleanup();
			//exit(1);
		}
	}

	pthread_mutex_init( &capture_mutex, NULL );
	if ( m_port != -1 )
	{
		iec61883Connection::CheckConsistency( m_port, m_node );

		if ( ! m_noavc )
		{
			m_avc = new AVC( m_port );

			if ( ! m_avc )
			{
				throw std::string( "failed to initialize AV/C" );
			}

		}

		m_reader = new iec61883Reader( m_port, m_channel, m_buffers,
			this->testCaptureProxy, this, m_hdv );
	}
	else if ( m_v4l2 )
	{
#ifdef HAVE_LINUX_VIDEODEV2_H
		//m_reader = new v4l2Reader( m_input_file_name, m_buffers, m_hdv );
#endif
	}
	else
		throw std::string( "invalid source specified" );

	if ( m_reader )
	{
		pthread_create( &capture_thread, NULL, captureThread, this );

		m_reader->StartThread();
		printf("start thread\n");
	}
}

DVgrab::~DVgrab()
{
	cleanup();
}

bool DVgrab::captureIsActive()
{
	return m_captureActive;
}

void DVgrab::setDeinterlace(unsigned int deinterlace_type)
{
    m_deinterlace = deinterlace_type;
}

void DVgrab::startCapture()
{
	int tryCounter = 400;

	if ( m_dst_file_name )
	{
		pthread_mutex_lock( &capture_mutex );
		switch ( m_file_format )
		{

		case OF_PIXEL_FORMAT:
			m_writer = new DVHandler( m_deinterlace );
			break;

		}

		m_writer->SetTimeStamp( m_timestamp );
		m_writer->SetTimeSys( m_timesys );
		m_writer->SetTimeCode( m_timecode );
		m_writer->SetBaseName( m_dst_file_name );
		m_writer->SetMaxFrameCount( m_frame_count );
		m_writer->SetAutoSplit( m_autosplit );
		m_writer->SetTimeSplit ( m_timeSplit );
		m_writer->SetEveryNthFrame( m_frame_every );
		m_writer->SetMaxFileSize( ( off_t ) m_max_file_size * ( off_t ) ( 1024 * 1024 ) );
		if (m_collection_size) {
		  m_sizesplitmode = 1;
		}
		m_writer->SetSizeSplitMode( m_sizesplitmode );
		m_writer->SetMaxColSize( ( off_t ) ( m_collection_size ) * ( off_t ) ( 1024 * 1024 ) );
		m_writer->SetMinColSize( ( off_t ) ( m_collection_size - m_collection_min_cut_file_size ) * ( off_t ) ( 1024 * 1024 ) );
	}

	if ( m_avc )
	{
		if ( m_isRewindFirst && !m_interactive )
		{
			// Stop whatever is happening
			m_avc->Stop( m_node );

			// Wait until it is stopped
			while ( !g_done &&
				AVC1394_MASK_RESPONSE_OPERAND( m_avc->TransportStatus( m_node ), 3 )
				!= AVC1394_VCR_OPERAND_WIND_STOP )
			{
				timespec t = {0, 25000000UL};
				nanosleep( &t, NULL );
			}

			// Rewind
			if ( !g_done )
				m_avc->Rewind( m_node );

			// Wait until is done rewinding
			while ( !g_done &&
			        AVC1394_MASK_RESPONSE_OPERAND( m_avc->TransportStatus( m_node ), 3 )
			            != AVC1394_VCR_OPERAND_WIND_STOP )
			{
				timespec t = {0, 25000000UL};
				nanosleep( &t, NULL );
			}
		}

		// Now Play so we can capture something
		if ( !g_done )
			m_avc->Play( m_node );
	}

	// Wait up to N seconds to see if we got any data
	// this is a little unclean, checking global g_done from main.cc to allow interruption
	while ( !g_done && m_frame == NULL && tryCounter-- > 0 )
	{
		timespec t = {0, 25000000UL};
		nanosleep( &t, NULL );
	}

	// OK, we have data, commence capture
	if ( !g_done && m_frame )
	{
		printf( "--- Capture Started ---\n" );
		m_captureActive = true;
		m_total_frames = 0;

		// parse the SMIL time value duration
//		if ( m_timeDuration == NULL && ! m_duration.empty() )
//			m_timeDuration = new SMIL::MediaClippingTime( m_duration, m_frame->GetFrameRate() );

		if ( m_dst_file_name )
			pthread_mutex_unlock( &capture_mutex );
	}

	// No data received in N seconds, throw an error
	else if ( !g_done )
	{
		if ( m_dst_file_name )
			pthread_mutex_unlock( &capture_mutex );
		const char *err = m_hdv ? "no HDV. Try again before giving up." : "no DV";
		if ( m_hdv )
			reset_bus( m_port );
		throw std::string( err );
	}
	else
	{
		if ( m_dst_file_name )
			pthread_mutex_unlock( &capture_mutex );
	}
}


void DVgrab::stopCapture()
{
	pthread_mutex_lock( &capture_mutex );
	if ( m_writer != NULL )
	{
		std::string filename = m_writer->GetFileName();
		int frames = m_writer->GetFramesWritten();
		//float size = ( float ) m_writer->GetFileSize() / 1024 / 1024;

		m_writer->Close();
		delete m_writer;
		m_writer = NULL;

        printf( "%d frames captured...\n",frames );
		printf( "\n--- Capture Stopped ---\n\n" );

		if ( m_dropped_frames > 0 )
			printf( "Warning: %d dropped frames.\n", m_dropped_frames );
		m_dropped_frames = 0;
		m_captureActive = false;
	}
	pthread_mutex_unlock( &capture_mutex );
}


void DVgrab::testCapture( void )
{
	pthread_attr_t thread_attributes;

	printf( "Bus Reset, launching watchdog thread\n" );

	pthread_attr_init( &thread_attributes );
	pthread_attr_setdetachstate( &thread_attributes, PTHREAD_CREATE_DETACHED );
	pthread_create( &watchdog_thread, NULL, watchdogThreadProxy, this );
}

void* DVgrab::watchdogThreadProxy( void* arg )
{
	DVgrab *self = static_cast< DVgrab* >( arg );
	self->watchdogThread();

	return NULL;
}

void DVgrab::watchdogThread()
{
	if ( m_reader )
	{
		if ( ! m_reader->WaitForAction( 1 ) )
		{
			cleanup();
			printf( "Error: timed out waiting for DV after bus reset" );
			throw;
		}
		// Otherwise, reestablish the connection
		if ( m_connection )
		{
			int newChannel = m_connection->Reconnect();
			if ( newChannel != m_channel )
			{
				cleanup();
				printf( "Error: unable to reestablish connection after bus reset" );
				throw;

				// TODO: the following attempt to recreate reader and restart capture
				// does not work
#if 0
				bool restartCapture = m_captureActive;

				if ( m_captureActive )
					stopCapture();
				m_reader_active = false;
				if ( m_reader )
				{
					m_reader->TriggerAction( );
					pthread_join( capture_thread, NULL );
					m_reader->StopThread();
					delete m_reader;
				}
				printf( "Closed existing reader" );
				m_reader = new iec61883Reader( m_port, m_channel, m_buffers,
					this->testCaptureProxy, this, m_hdv );
				if ( m_reader )
				{
					printf( "new reader created" );
					pthread_create( &capture_thread, NULL, captureThread, this );
					m_reader->StartThread();
				}
				printf( "restarting capture" );
				if ( restartCapture )
					startCapture();
#endif
			}
		}
	}
}

void DVgrab::testCaptureProxy( void* arg )
{
	DVgrab *self = static_cast< DVgrab * >( arg );
	self->testCapture();
}

void *DVgrab::captureThread( void *arg )
{
	DVgrab * me = ( DVgrab* ) arg;
	me->captureThreadRun();
	return NULL;
}

void DVgrab::sendCaptureStatus( const char *name, float size, int frames, TimeCode *tc, struct tm *rd, bool newline )
{
	char tc_str[64], rd_str[128];

	if ( tc )
		sprintf( tc_str, "%2.2d:%2.2d:%2.2d.%2.2d",
			tc->hour, tc->min, tc->sec, tc->frame );
	else
		sprintf( tc_str, "??:??:??.??" );

	if ( rd )
		sprintf( rd_str, "%4.4d.%2.2d.%2.2d %2.2d:%2.2d:%2.2d",
			rd->tm_year + 1900, rd->tm_mon + 1, rd->tm_mday,
			rd->tm_hour, rd->tm_min, rd->tm_sec );
	else
		sprintf( rd_str, "????.??.?? ??:??:??" );

	//printfParams( 2, 0, "\"%s\": %8.2f MiB %5d frames timecode %s date %s%s",
		//name, size, frames, tc_str, rd_str, newline ? "\n" : "" );
}

void DVgrab::writeFrame()
{
	// All access to the writer is protected
	pthread_mutex_lock( &capture_mutex );

	// see if we have exceeded requested duration
//	if ( m_timeDuration && m_timeDuration->isResolved() &&
//	     ( ( float )m_total_frames++ / m_frame->GetFrameRate() * 1000.0 + 0.5 ) >=
//	     m_timeDuration->getResolvedOffset() )
//	{
//		printf("Requested duration exceeded!\n");
//		pthread_mutex_unlock( &capture_mutex );
//		stopCapture();
//		m_reader_active = false;
//	}
//	else
	if ( m_writer != NULL )
	{
		std::string fileName = m_writer->GetFileName();
		float size = ( float ) m_writer->GetFileSize() / 1024 / 1024;
		int framesWritten = m_writer->GetFramesWritten();
		TimeCode tc, *timeCode = &tc;
		struct tm rd, *recDate = &rd;
		TimeCode *lasttc = m_isLastTimeCodeSet ? &m_lastTimeCode : 0;
		struct tm *lastrd = m_isLastRecDateSet ? &m_lastRecDate : 0;

		if ( !m_frame->GetTimeCode( tc ) )
			timeCode = 0;
		if ( !m_frame->GetRecordingDate( rd ) )
		{
			// If the month is invalid, then report system date/timem_reader_active
			time_t timesys;
			time( &timesys );
			localtime_r( &timesys, recDate );
		}

		if ( m_lockstep && m_lockPending && m_frame_count > 0 && m_frame->CanStartNewStream() )
		{
			// If a lock is pending due to dropped frames, close the file
			if ( m_writer->FileIsOpen() )
			{
				m_writer->CollectionCounterUpdate();
				m_writer->Close();
			}

//			if ( !m_hdv && timeCode )
//			{
//				// Convert timecode to #frames
//				SMIL::MediaClippingTime mcTime( m_frame->GetFrameRate() );
//				std::ostringstream sb;
//				sb << setfill( '0' ) << std::setw( 2 )
//				<< timeCode->hour << ':' << timeCode->min << ':'
//				<< timeCode->sec << ':' << timeCode->frame;
//				DVFrame *dvframe = static_cast<DVFrame*>( m_frame );
//				if ( dvframe->IsPAL() )
//					mcTime.parseSmpteValue( sb.str() );
//				else
//					mcTime.parseSmpteNtscDropValue( sb.str() );
//
//				// If lock step point (multiple of frame count) is reached, skip writing
//				if ( mcTime.getFrames() % m_frame_count != 0 )
//				{
//					pthread_mutex_unlock( &capture_mutex );
//					return;
//				}
//			}
			m_lockPending = false;
		}

		if ( ! m_writer->WriteFrame( m_frame ) )
		{
			pthread_mutex_unlock( &capture_mutex );
			stopCapture();
			printf("writing failed\n");
			throw std::string( "writing failed" );
		}
		else
		{
			pixels = m_writer->GetPixels();
			newFrame = true;
		}

		m_isNewFile |= m_writer->IsNewFile();

		if ( m_writer->IsNewFile() && !m_writer->IsFirstFile() )
		{
			sendCaptureStatus( fileName.c_str(), size, framesWritten, lasttc, lastrd, true );
			if ( m_dropped_frames > 0 )
				printf( "Warning: %d dropped frames.", m_dropped_frames );
			m_dropped_frames = 0;
		}
		else if ( m_showstatus )
		{
			sendCaptureStatus( m_writer->GetFileName().c_str(),
				(float) m_writer->GetFileSize() / 1024 / 1024,
				m_writer->GetFramesWritten(), timeCode, recDate, false );
		}

		if ( timeCode )
		{
			memcpy( &m_lastTimeCode, timeCode, sizeof( m_lastTimeCode ) );
			m_isLastTimeCodeSet = true;
		}
		if ( recDate )
		{
			memcpy( &m_lastRecDate, recDate, sizeof( m_lastRecDate ) );
			m_isLastRecDateSet = true;
		}
	}
	pthread_mutex_unlock( &capture_mutex );
}

void DVgrab::sendFrameDroppedStatus( const char *reason, const char *meaning )
{
	TimeCode timeCode;
	struct tm recDate;
	char tc[32], rd[32];

	if ( m_frame && m_frame->GetTimeCode( timeCode ) )
		sprintf( tc, "%2.2d:%2.2d:%2.2d.%2.2d",
			timeCode.hour, timeCode.min, timeCode.sec, timeCode.frame );
	else
		sprintf( tc, "??:??:??.??" );

	if ( m_frame && m_frame->GetRecordingDate( recDate ) )
		sprintf( rd, "%4.4d.%2.2d.%2.2d %2.2d:%2.2d:%2.2d",
			recDate.tm_year + 1900, recDate.tm_mon + 1, recDate.tm_mday,
			recDate.tm_hour, recDate.tm_min, recDate.tm_sec );
	else
		sprintf( rd, "????.??.?? ??:??:??" );

	//printf( "\n\a\"%s\": %s: timecode %s date %s", m_writer ? m_writer->GetFileName().c_str() : "stdout", reason, tc, rd );
	printf( "%s: timecode %s date %s\n", reason, tc, rd );

	printf( "%s\n",meaning );
}

void DVgrab::captureThreadRun()
{
	m_lockPending = true;
	m_reader_active = true;

	// Loop until we're informed otherwise
	while ( m_reader_active )
	{
		pthread_testcancel();
		// Wait for the reader to indicate that something has happened
		m_reader->WaitForAction( );

		int dropped = m_reader->GetDroppedFrames();

		newFrame = false;

		// Get the next frame
		if ( ( m_frame = m_reader->GetFrame() ) == NULL )
			// reader has erred or signaling a stop condition (end of pipe)
			break;

		// Check if the out queue is falling behind
		bool critical_mass = m_reader->GetOutQueueSize( ) > m_reader->GetInQueueSize( );

		// Handle exceptional situations
		if ( dropped > 0 )
		{
			m_dropped_frames += dropped;
			sendFrameDroppedStatus( "buffer underrun near",
				"This error means that the frames could not be written fast enough." );

			if ( m_lockstep && m_frame_count > 0 )
			{
				if ( m_writer->FileIsOpen() )
				{
					if ( ( m_lockstep_maxdrops > -1 && dropped > m_lockstep_maxdrops )
					||( m_lockstep_totaldrops > -1 && m_dropped_frames > m_lockstep_totaldrops ) )
					{
						printf( "Warning: closing file early due to too many dropped frames." );
						m_lockPending = true;
					}
					for ( int n = 0; n < dropped; n++ )
						writeFrame();
				}
				else
				{
					m_dropped_frames = 0;
				}
			}

		}

		if ( ! m_frame->IsComplete() )
		{
			m_dropped_frames++;
			sendFrameDroppedStatus( "frame dropped",
				"This error means that the ieee1394 driver received an incomplete frame." );

			if ( m_lockstep && m_frame_count > 0 )
			{
				if ( m_writer->FileIsOpen() )
				{
					if ( m_lockstep_totaldrops > -1 && m_dropped_frames > m_lockstep_totaldrops )
					{
						printf( "Warning: closing file early due to too many dropped frames." );
						m_lockPending = true;
					}
					writeFrame();
				}
				else
				{
					m_dropped_frames = 0;
				}
			}
		}
		else
		{
			if ( m_hdv )
			{
				writeFrame();
			}
			else
			{
				DVFrame *dvframe = static_cast<DVFrame*>( m_frame );
				TimeCode timeCode = { 0, 0, 0, 0 };
				dvframe->GetTimeCode( timeCode );
				if ( dvframe->IsNormalSpeed() &&
				     ( !m_avc ||
				       !m_isRecordMode ||
				       ( m_isRecordMode &&
				         strcmp( avc1394_vcr_decode_status( m_avc->TransportStatus( m_node ) ), "Recording" ) == 0 &&
				         !( timeCode.hour == 0 && timeCode.min == 0  && timeCode.sec == 0 && timeCode.frame == 0 )
				       )
				     )
				   )
					writeFrame();
			}

			// drop frame on stdout if getting low on buffers
			if ( !critical_mass && m_raw_pipe )
			{
				fd_set wfds;
				struct timeval tv =
					{
						0, 20000
					};
				FD_ZERO( &wfds );
				FD_SET( fileno( stdout ), &wfds );
				if ( select( fileno( stdout ) + 1, NULL, &wfds, NULL, &tv ) )
				{
					write( fileno( stdout ), m_frame->data, m_frame->GetDataLen() );
				}
			}
		}
		m_reader->DoneWithFrame( m_frame );
	}
	m_reader_active = false;
}


void DVgrab::status( )
{
	char s[ 32 ];
	unsigned int status;
	static unsigned int prevStatus = 0;
	std::string transportStatus( "" );
	std::string timecode( "" );
	std::string filename( "" );
	std::string duration( "" );

	if ( ! m_avc )
		return ;

	status = m_avc->TransportStatus( m_node );
	if ( ( int ) status >= 0 )
		transportStatus = avc1394_vcr_decode_status( status );
	if ( prevStatus == 0 )
		prevStatus = status;
	if ( status != prevStatus && AVC1394_MASK_RESPONSE_OPERAND( prevStatus, 2 ) == AVC1394_VCR_RESPONSE_TRANSPORT_STATE_WIND )
	{
		quadlet_t resp2 = AVC1394_MASK_RESPONSE_OPERAND( status, 2 );
		quadlet_t resp3 = AVC1394_MASK_RESPONSE_OPERAND( status, 3 );
		if ( resp2 == AVC1394_VCR_RESPONSE_TRANSPORT_STATE_WIND && resp3 == AVC1394_VCR_OPERAND_WIND_STOP )
			printf( "Winding Stopped" );
	}
	m_transportStatus = prevStatus = status;

	if ( m_avc->Timecode( m_node, s ) )
		timecode = s;

	if ( m_writer != NULL )
		filename = m_writer->GetFileName();
	else
		filename = "";

	if ( m_frame != NULL && m_writer != NULL )
	{
		sprintf( s, "%8.2f", ( float ) m_writer->GetFramesWritten() / m_frame->GetFrameRate() );
		duration = s;
	}
	else
		duration = "";

	fprintf( stderr, "%-80.80s\r", " " );
	fprintf( stderr, "\"%s\" %s \"%s\" %8s sec\r", transportStatus.c_str(),
	         timecode.c_str(),
	         filename.c_str(),
	         duration.c_str() );
	fflush( stderr );
}

bool DVgrab::execute( const char cmd )
{
	bool result = true;
	switch ( cmd )
	{
	case 'p':
		if ( m_avc )
		{
			m_avc->Play( m_node );
		}
		break;
	case ' ':
		if ( m_avc )
		{
			if ( isPlaying() )
				m_avc->Pause( m_node );
			else
				m_avc->Play( m_node );
		}
		break;
	case 'h':
		if ( m_avc )
		{
			m_avc->Reverse( m_node );
		}
		break;
	case 'j':
		if ( m_avc )
		{
			m_avc->Pause( m_node );
			m_avc->Rewind( m_node );
		}
		break;
	case 'k':
		if ( m_avc )
		{
			m_avc->Pause( m_node );
		}
		break;
	case 'l':
		if ( m_avc )
		{
			m_avc->Pause( m_node );
			m_avc->FastForward( m_node );
		}
		break;
	case 'a':
		if ( m_avc )
		{
			m_avc->Stop( m_node );
			m_avc->Rewind( m_node );
		}
		break;
	case 'z':
		if ( m_avc )
		{
			m_avc->Stop( m_node );
			m_avc->FastForward( m_node );
		}
		break;
	case '1':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, -14 );
		}
		break;
	case '2':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, -11 );
		}
		break;
	case '3':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, -8 );
		}
		break;
	case '4':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, -4 );
		}
		break;
	case '5':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, -1 );
		}
		break;
	case '6':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, 1 );
		}
		break;
	case '7':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, 4 );
		}
		break;
	case '8':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, 8 );
		}
		break;
	case '9':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, 11 );
		}
		break;
	case '0':
		if ( m_avc )
		{
			m_avc->Shuttle( m_node, 14 );
		}
		break;
	case 's':
	case 0x1b:    // Esc
		if ( m_captureActive )
			stopCapture();
		else if ( m_avc )
			m_avc->Stop( m_node );
		break;
	case 'c':
		startCapture();
		break;
	case 'q':
		result = false;
		break;
	case '?':
		cerr << "q=quit, p=play, c=capture, Esc=stop, h=reverse, j=backward scan, k=pause" << endl;
		cerr << "l=forward scan, a=rewind, z=fast forward, 0-9=trickplay, <space>=play/pause" << endl;
		break;
	default:
		//fprintf( stderr, "\nunkown key 0x%2.2x", cmd );
		//result = false;
		break;
	}
	return result;
}

bool DVgrab::isPlaying()
{
	if ( ! m_avc )
		return false;
	unsigned int status = m_avc->TransportStatus( m_node );
	quadlet_t resp2 = AVC1394_MASK_RESPONSE_OPERAND( status, 2 );
	quadlet_t resp3 = AVC1394_MASK_RESPONSE_OPERAND( status, 3 );
	return ( ( resp2 == AVC1394_VCR_RESPONSE_TRANSPORT_STATE_PLAY && resp3 != AVC1394_VCR_OPERAND_PLAY_FORWARD_PAUSE ) ||
		( resp2 == AVC1394_VCR_RESPONSE_TRANSPORT_STATE_RECORD && resp3 != AVC1394_VCR_OPERAND_RECORD_PAUSE ) );
}

bool DVgrab::done()
{
	if ( m_reader_active )
	{
		// Stop capture at end of tape
		if ( m_writer && m_writer->GetFileSize() > 0 && m_avc &&
		     AVC1394_MASK_RESPONSE_OPERAND( m_avc->TransportStatus( m_node ), 3 ) == AVC1394_VCR_OPERAND_WIND_STOP )
		{
			return true;
		}

		timespec t = {0, 25000000};
		return ( nanosleep( &t, NULL ) == -1 );
	}
	return true;
}

void DVgrab::cleanup()
{
	printf("Cleaning up DVgrab...\n");
	stopCapture();
	if ( m_avc && !m_no_stop )
		m_avc->Stop( m_node );
	m_reader_active = false;
	if ( m_reader )
	{
		m_reader->StopThread();
		pthread_join( capture_thread, NULL );
		delete m_reader;
	}
	delete m_avc;

}
