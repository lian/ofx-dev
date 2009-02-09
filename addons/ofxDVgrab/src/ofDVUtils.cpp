#include "ofDVUtils.h"

// C includes
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>


bool g_done = false;

void signal_handler( int sig )
{
	printf("g_done = true\n");
	g_done = true;
}

int rt_raisepri (int pri)
{
#ifdef _SC_PRIORITY_SCHEDULING
	struct sched_param scp;

	/*
	 * Verify that scheduling is available
	 */
	if ( sysconf( _SC_PRIORITY_SCHEDULING ) == -1)
	{
		printf("Warning: RR-scheduler not available, disabling.\n");
		return -1;
	}
	else
	{
		memset( &scp, '\0', sizeof( scp ) );
		scp.sched_priority = sched_get_priority_max( SCHED_RR ) - pri;
		if ( sched_setscheduler( 0, SCHED_RR, &scp ) < 0 )
		{
			printf("Warning: Cannot set RR-scheduler\n");
			return -1;
		}
	}
	return 0;

#else
	return -1;
#endif
}


//--------------------------------------------------------------------

ofDVUtils::ofDVUtils()
: dvgrab(NULL), bUseTexture(false), bGrabberInited(false), bIsFrameNew(false), pixels(NULL)
{

}


//--------------------------------------------------------------------

ofDVUtils::~ofDVUtils()
{
	delete dvgrab;
	dvgrab = NULL;
}

void ofDVUtils::initGrabber(bool _useTexture, unsigned int _deinterlace, VideoType _videoType)
{

    bUseTexture = _useTexture;

    if(_videoType == OF_DV_PAL)
    {
        width = 720;
        height = 576;
    }
    else
    {
        width = 720;
        height = 480;
    }
    pixels	= new unsigned char[width * height * 3];

    if (bUseTexture){
        // create the texture, set the pixels to black and
        // upload them to the texture (so at least we see nothing black the callback)
        tex.allocate(width,height,GL_RGB);
        memset(pixels, 0, width*height*3);
        tex.loadData(pixels, width, height, GL_RGB);
    }

	fcntl( fileno( stderr ), F_SETFL, O_NONBLOCK );
	try
	{

		dvgrab = new DVgrab() ;

		if ( rt_raisepri( 1 ) != 0 ) {
			setpriority( PRIO_PROCESS, 0, -20 );
		}

#if _POSIX_MEMLOCK > 0
		if ( mlockall( MCL_CURRENT | MCL_FUTURE ) == -1 )
			printf( "Warning: Cannot disable swapping\n" );
#endif

        dvgrab->setDeinterlace(_deinterlace);
		printf("start capture\n");
		dvgrab->startCapture();
		bGrabberInited = true;

	}
	catch ( std::string s )
	{
		printf( "*** Error: %s\n", s.c_str() );
	}
	catch ( ... )
	{
		printf( "Error: unknown\n" );
	}

}

void ofDVUtils::grabFrame()
{
    if(bGrabberInited)
    {
        bIsFrameNew = dvgrab->newFrame;
        dvgrab->newFrame = false;
        if (bUseTexture)
        {
            if(bIsFrameNew) {
                tex.loadData(dvgrab->pixels, width, height, GL_RGB);
            }
        }
    }

}

unsigned char * ofDVUtils::getPixels()
{

    if(bGrabberInited) {
        bool active = dvgrab->captureIsActive();
        if(active)
        {
            return dvgrab->pixels;
        }
    }

    return NULL;

}

bool ofDVUtils::isFrameNew()
{

    {
        return bIsFrameNew;
    }
//    else
//    {
//        if(bGrabberInited)
//        {
//            bool result = dvgrab->newFrame;
//            dvgrab->newFrame = false;
//            return result;
//        }
//        return false;
//    }
}

//------------------------------------
void ofDVUtils::draw(float _x, float _y, float _w, float _h){
	if (bUseTexture){
		tex.draw(_x, _y, _w, _h);
	}
}

//------------------------------------
void ofDVUtils::draw(float _x, float _y){
	draw(_x, _y, width, height);
}
