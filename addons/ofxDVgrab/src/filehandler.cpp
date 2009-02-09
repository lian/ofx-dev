/*
* filehandler.cc -- saving DV data into different file formats
* Copyright (C) 2000 Arne Schirmacher <arne@schirmacher.de>
* Raw DV, JPEG, and Quicktime portions Copyright (C) 2003 Dan Dennedy <dan@dennedy.org>
* Portions of Quicktime code borrowed from Arthur Peters' dv_utils.
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

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::ostringstream;
using std::setw;
using std::setfill;
using std::ends;

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "filehandler.h"
#include "error.h"
#include "frame.h"
#include "dvframe.h"


FileTracker *FileTracker::instance = NULL;

FileTracker::FileTracker( ) : mode( CAPTURE_MOVIE_APPEND )
{
	return ;
	printf( ">> Constructing File Capture tracker" );
}

FileTracker::~FileTracker( )
{
	return ;
	printf( ">> Destroying File Capture tracker" );
}

FileTracker &FileTracker::GetInstance( )
{
	if ( instance == NULL )
		instance = new FileTracker();

	return *instance;
}

void FileTracker::SetMode( FileCaptureMode mode )
{
	this->mode = mode;
}

FileCaptureMode FileTracker::GetMode( )
{
	return this->mode;
}

char *FileTracker::Get( int index )
{
	return list[ index ];
}

void FileTracker::Add( const char *file )
{
	return ;
	if ( this->mode != CAPTURE_IGNORE )
	{
		printf( ">>>> Registering %s with the tracker", file );
		list.push_back( strdup( file ) );
	}
}

unsigned int FileTracker::Size( )
{
	return list.size();
}

void FileTracker::Clear( )
{
	while ( Size() > 0 )
	{
		free( list[ Size() - 1 ] );
		list.pop_back( );
	}
	this->mode = CAPTURE_MOVIE_APPEND;
}

FileHandler::FileHandler() :
    isFirstFile( -1 ), isNewFile( false ), done( false ), autoSplit( false ), timeSplit(0), maxFrameCount( 0 ), framesWritten( 0 ),
	currentCollectionSize( 0 ), lastCollectionFreeSpace( 0 ), filename( "" )
{
	prevTimeCode.sec = -1;
}


FileHandler::~FileHandler()
{
}


void FileHandler::CollectionCounterUpdate()
{
	if ( GetSizeSplitMode() == 1)
	{
		currentCollectionSize += GetFileSize();

		// Shove this cut into the last collection if there's room
		if (currentCollectionSize <= lastCollectionFreeSpace)
		{
			currentCollectionSize = 0;
			lastCollectionFreeSpace = lastCollectionFreeSpace - currentCollectionSize;
		}
		else
			lastCollectionFreeSpace = 0;

		// Start a new collection if we've gone over the Minimum Collection Size
		if (currentCollectionSize >= GetMinColSize())
		{
			if (currentCollectionSize < GetMaxColSize())
				lastCollectionFreeSpace = GetMaxColSize() - currentCollectionSize;
			else
				lastCollectionFreeSpace = 0;
			currentCollectionSize = 0;
		}
	}
}


bool FileHandler::GetAutoSplit()
{
	return autoSplit;
}

int FileHandler::GetTimeSplit()
{
	return timeSplit;
}


bool FileHandler::GetTimeStamp()
{
	return timeStamp;
}


bool FileHandler::GetTimeSys()
{
	return timeSys;
}


bool FileHandler::GetTimeCode()
{
	return timeCode;
}


string FileHandler::GetBaseName()
{
	return base;
}


string FileHandler::GetExtension()
{
	return extension;
}


int FileHandler::GetMaxFrameCount()
{
	return maxFrameCount;
}

off_t FileHandler::GetMaxFileSize()
{
	return maxFileSize;
}

int FileHandler::GetSizeSplitMode()
{
	return sizeSplitMode;
}

off_t FileHandler::GetMaxColSize()
{
	return maxColSize;
}

off_t FileHandler::GetMinColSize()
{
	return minColSize;
}


void FileHandler::SetAutoSplit( bool flag )
{
	autoSplit = flag;
}


void FileHandler::SetTimeSplit( int secs )
{
	timeSplit = secs;
}


void FileHandler::SetTimeStamp( bool flag )
{
	timeStamp = flag;
}


void FileHandler::SetTimeSys( bool flag )
{
	timeSys = flag;
}


void FileHandler::SetTimeCode( bool flag )
{
	timeCode = flag;
}


void FileHandler::SetBaseName( const string& s )
{
	base = s;
}


void FileHandler::SetMaxFrameCount( int count )
{
	assert( count >= 0 );
	maxFrameCount = count;
}


void FileHandler::SetEveryNthFrame( int every )
{
	assert ( every > 0 );

	everyNthFrame = every;
}


void FileHandler::SetMaxFileSize( off_t size )
{
	assert ( size >= 0 );
	maxFileSize = size;
}

void FileHandler::SetSizeSplitMode( int mode )
{
	sizeSplitMode  = mode;
}

void FileHandler::SetMaxColSize( off_t size )
{
	maxColSize  = size;
}


void FileHandler::SetMinColSize( off_t size )
{
	minColSize  = size;
}

void FileHandler::SetFilmRate( bool flag)
{
	filmRate = flag;
}

void FileHandler::SetRemove2332( bool flag)
{
	remove2332 = flag;
}

bool FileHandler::Done()
{
	return done;
}

bool FileHandler::WriteFrame( Frame *frame )
{
	/* If the file size, collection size, or max frame count would be exceeded
	 * by this frame, and we can start a new file on this frame, close the current file.
	 * If the autosplit flag is set, a new file will be created.
	 */
	if ( FileIsOpen() && frame->CanStartNewStream() )
	{
		bool startNewFile = false;
		off_t newFileSize = GetFileSize() + frame->GetDataLen();
		bool maxFileSizeExceeded = newFileSize >= GetMaxFileSize();
		bool maxColSizeExceeded = GetCurrentCollectionSize() + newFileSize >= GetMaxColSize();

		if ( GetFileSize() > 0 )
		{
			if ( GetMaxFileSize() > 0 && maxFileSizeExceeded )
				startNewFile = true;

			if ( GetMaxColSize() > 0 && GetSizeSplitMode() == 1 && maxColSizeExceeded )
				startNewFile = true;
		}

		if ( GetMaxFrameCount() > 0 && framesWritten >= GetMaxFrameCount() )
			startNewFile = true;

		if ( startNewFile )
		{
			CollectionCounterUpdate();
			Close();
			done = !GetAutoSplit();
		}
	}

	TimeCode tc;
	int time_diff = 0;
	if ( frame->GetTimeCode( tc ) )
		time_diff = TIMECODE_TO_SEC(tc) - TIMECODE_TO_SEC(prevTimeCode);
	bool discontinuity = prevTimeCode.sec != -1 && ( time_diff > 1 || time_diff < 0 );

	bool isTimeSplit = false;
	if ( timeSplit != 0 )
	{
		struct tm rd;
		if ( frame->GetRecordingDate( rd ) )
		{
			time_t now = mktime( &rd );
			if ( now >= prevTime + timeSplit )
				isTimeSplit = true;
			prevTime = now;
		}
	}

	// If the user wants autosplit, start a new file if a new recording is detected
	// either by explicit frame flag or a timecode discontinuity
	if ( FileIsOpen() && ( ( GetAutoSplit() && ( frame->IsNewRecording() || discontinuity ) )
		|| isTimeSplit ) )
	{
		CollectionCounterUpdate();
		Close();
	}

	isNewFile = false;

	if ( ! FileIsOpen() )
	{
		static int counter = 0;

		prevTimeCode.sec = -1;

		if ( GetTimeStamp() )
		{
			ostringstream	sb, sb2;
			struct tm	date;
			string	recDate;

			if ( frame->GetRecordingDate( date ) )
			{
				sb << setfill( '0' )
				<< setw( 4 ) << date.tm_year + 1900 << '.'
				<< setw( 2 ) << date.tm_mon + 1 << '.'
				<< setw( 2 ) << date.tm_mday << '_'
				<< setw( 2 ) << date.tm_hour << '-'
				<< setw( 2 ) << date.tm_min << '-'
				<< setw( 2 ) << date.tm_sec << ends;
				recDate = sb.str();
			}
			else
			{
				goto TimeSys;
			}
			sb2 << GetBaseName() << recDate << GetExtension() << ends;
			filename = sb2.str();
		}
		else if ( GetTimeSys() )
		{
TimeSys:
			ostringstream sb;
			time_t timesys;
			struct tm date;

			time( &timesys );
			localtime_r( &timesys, &date );

			sb << GetBaseName()
			<< setfill( '0' )
			<< setw( 4 ) << date.tm_year + 1900 << '.'
			<< setw( 2 ) << date.tm_mon + 1 << '.'
			<< setw( 2 ) << date.tm_mday << '_'
			<< setw( 2 ) << date.tm_hour << '-'
			<< setw( 2 ) << date.tm_min << '-'
			<< setw( 2 ) << date.tm_sec
			<< GetExtension() << ends;
			filename = sb.str();
		}
		else if ( GetTimeCode() )
		{
			ostringstream sb;
			TimeCode tc;

			if ( frame->GetTimeCode( tc ) )
			{
				sb << GetBaseName()
				<< setfill( '0' )
				<< setw( 2 ) << tc.hour << ':'
				<< setw( 2 ) << tc.min << ':'
				<< setw( 2 ) << tc.sec << ':'
				<< setw( 2 ) << tc.frame
				<< GetExtension();
			}
			else
			{
				sb << GetBaseName()
				<< "EE:EE:EE:EE"
				<< GetExtension();
			}
			sb << ends;
			filename = sb.str();
		}
		else
		{
			struct stat stats;
			do
			{
				ostringstream sb;
				sb << GetBaseName() << setfill( '0' ) << setw( 3 ) << ++ counter
					<< GetExtension() << ends;
				filename = sb.str();
			}
			while ( stat( filename.c_str(), &stats ) == 0 );
		}

		if ( ! Create( filename ) )
		{
			printf( ">>> Error creating file!" );
			return false;
		}
		isNewFile = true;
		if ( isFirstFile == -1 )
			isFirstFile = 1;
		else if ( isFirstFile == 1 )
			isFirstFile = 0;
		framesWritten = 0;
		framesToSkip = 0;
	}

	/* write frame */

	if ( framesToSkip == 0 )
	{
		if ( 0 > Write( frame ) )
		{
			printf( ">>> Error writing frame!" );
			return false;
		}
		framesToSkip = everyNthFrame;
		++framesWritten;
	}
	framesToSkip--;

	if ( !frame->GetTimeCode( prevTimeCode ) )
		prevTimeCode.sec = -1;

	return true;
}

/********************************************************************************/

DVHandler::DVHandler( unsigned int deinterlace) :
		isOpen( false ), count( 0 ), deinterlace( deinterlace )
{


}


DVHandler::~DVHandler()
{
	Close();
	//jpeg_destroy_compress( &cinfo );
}

bool DVHandler::Create( const string& filename )
{
	this->filename = filename;
	isOpen = true;
	count = 0;
	return true;
}


int DVHandler::Write( Frame *frame )
{
	DVFrame *dvframe = (DVFrame*)frame;

	dvframe->ExtractHeader();

	if ( frame->IsNewRecording() && GetAutoSplit() )
		count = 0;

	dvframe->ExtractRGB( image_buffer );

    if(deinterlace == 3) {
//        memcpy ((unsigned char *) image_buffer_prev, (unsigned char *) image_buffer, 720*576*3);//dvframe->GetWidth()*dvframe->GetHeight()*3);
        //memcpy ((unsigned char *) image_buffer_in, (unsigned char *) image_buffer, 720*576*3);
    }

	switch ( deinterlace )
	{
	    case 1 :
            dvframe->DeinterlaceAverage( image_buffer, 3 );
            break;
        case 2:
            dvframe->DeinterlaceLinearBlend( image_buffer, image_buffer, 3 );
            break;
        case 3:
            dvframe->DeinterlaceBobWeave( ( uint8_t* ) image_buffer_in, ( uint8_t* ) image_buffer_prev, ( uint8_t* ) image_buffer, 3 );
            break;
        default :
            break;
	}

    if(deinterlace == 3) {
        memcpy ((unsigned char *) image_buffer_prev, (unsigned char *) image_buffer, 720*576*3);
        //memcpy ((unsigned char *) image_buffer_in, (unsigned char *) image_buffer, new_width*new_height*3);
    }

	return 0;
}

int DVHandler::Close( void )
{
	isOpen = false;
	return 0;
}

//#endif

