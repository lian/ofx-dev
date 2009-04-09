#ifndef _OF_VIDEO_PLAYER_GST
#define _OF_VIDEO_PLAYER_GST

#include "ofConstants.h"

#ifdef OF_VIDEO_PLAYER_GSTREAMER

#include "ofVideoPlayer.h"

#include <gst/gst.h>
#include <pthread.h>

class ofVideoPlayerImpl {
public:
    typedef ofVideoPlayer Generic;

	typedef struct {
		GMainLoop 		*	loop;
		GstElement 		*	pipeline;
		unsigned char 	*	pixels;
		pthread_mutex_t 	buffer_mutex;
		bool				bHasPixelsChanged;

		guint64				durationNanos;
		guint64				nFrames;
		int					pipelineState;
		float				speed;
	} ofGstVideoData;

public:
	ofVideoPlayerImpl(Generic *generic);
	~ofVideoPlayerImpl();

    Generic             *generic;
	ofGstVideoData 		gstData;
	bool				bIsMovieDone;
	bool				isStream;
	GstElement	* 		gstPipeline;
	GstElement  *		gstSink;
	gint64          	durationNanos;
	int					loopMode;

	bool				posChangingPaused;


	pthread_mutex_t 	seek_mutex;
	void                seek_lock();
	void                seek_unlock();
	void 				gstHandleMessage();
	bool 				allocate();

};

#endif	// OF_VIDEO_PLAYER_GSTREAMER

#endif	// _OF_VIDEO_PLAYER_GST
