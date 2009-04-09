#include "ofVideoPlayerGST.h"

#ifdef OF_VIDEO_PLAYER_GSTREAMER

#include <gst/video/video.h>
#include "gst/app/gstappsink.h"

static bool plugin_registered = false;
static bool gst_inited = false;
//------------------------------------
void ofGstDataLock(ofVideoPlayerImpl::ofGstVideoData * data){
	pthread_mutex_lock( &(data->buffer_mutex) );
}

//------------------------------------
void ofGstDataUnlock(ofVideoPlayerImpl::ofGstVideoData * data){
	pthread_mutex_unlock( &(data->buffer_mutex) );
}



// called when the appsink notifies us that there is a new buffer ready for
// processing

static void
on_new_buffer_from_source (GstElement * elt, ofVideoPlayerImpl::ofGstVideoData * data)
{
  guint size;
  GstBuffer *buffer;

  //get the buffer from appsink
  buffer = gst_app_sink_pull_buffer (GST_APP_SINK (elt));

  size = GST_BUFFER_SIZE (buffer);
  //ofLog(OF_LOG_VERBOSE,"new buffer of size %d", size);

  ofGstDataLock(data);
	  if(data->pixels){
		  memcpy (data->pixels, GST_BUFFER_DATA (buffer), size);
		  data->bHasPixelsChanged=true;
	  }
  ofGstDataUnlock(data);

  if( !data->nFrames && data->pipelineState==GST_STATE_PLAYING && data->speed==1 ){
	  data->nFrames=data->durationNanos/buffer->duration;
  }

  /// we don't need the appsink buffer anymore
  gst_buffer_unref (buffer);
}

static gboolean
appsink_plugin_init (GstPlugin * plugin)
{
  gst_element_register (plugin, "appsink", GST_RANK_NONE, GST_TYPE_APP_SINK);

  return TRUE;
}


ofVideoPlayerImpl :: ofVideoPlayerImpl(Generic *generic)
:	generic(generic),
    gstPipeline(NULL),
//	bIsFrameNew(false),
	loopMode(OF_LOOP_NONE),
	durationNanos(0),
	bIsMovieDone(false),
	posChangingPaused(0),
	isStream(false)
{
	gstData.durationNanos		= 0;
	gstData.nFrames				= 0;
	gstData.speed				= generic->speed;

	pthread_mutex_init(&(gstData.buffer_mutex),NULL);
	pthread_mutex_init(&seek_mutex,NULL);

	if(!g_thread_supported()){
		g_thread_init(NULL);
	}
	if(!gst_inited){
		gst_init (NULL, NULL);
		gst_inited=true;
	}
	if(!plugin_registered){
		gst_plugin_register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR,
					"appsink", "Element application sink",
					appsink_plugin_init, "0.1", "LGPL", "ofVideoPlayer", "openFrameworks",
					"http://openframeworks.cc/");
		plugin_registered=true;
	}
}

ofVideoPlayerImpl :: ~ofVideoPlayerImpl() {
	// nothing to doof_preRelease_v0.06_xcode_FAT.zip
}

//----------------------------------------------------------
bool ofVideoPlayerImpl :: allocate(){
	// wait for paused state to query the duration
	GstState state = GST_STATE_PAUSED;
	gst_element_get_state(gstPipeline,&state,NULL,2*GST_SECOND);
	GstFormat format=GST_FORMAT_TIME;
	if(!gst_element_query_duration(gstPipeline,&format,&durationNanos))
		ofLog(OF_LOG_WARNING,"GStreamer: cannot query time duration");

	gstData.durationNanos = durationNanos;
	gstData.nFrames		  = 0;




	// query width, height, fps and do data allocation
	if (GstPad* pad = gst_element_get_static_pad(gstSink, "sink")) {
		if(gst_video_get_size(GST_PAD(pad), &(generic->width), &(generic->height)) && generic->bUseTexture){
			generic->pixels=new unsigned char[generic->width*generic->height*3];
			gstData.pixels=generic->pixels;
			memset(generic->pixels,0,generic->width*generic->height*3);
			generic->tex.allocate(generic->width,generic->height,GL_RGB);
			generic->tex.loadData(generic->pixels,generic->width,generic->height,GL_RGB);
			generic->allocated = true;
		}else{
			ofLog(OF_LOG_ERROR,"GStreamer: cannot query width and height");
			return false;
		}

		/*GstCaps * caps = gst_pad_get_caps(pad);
		if(caps){
			int fps_n;
			int fps_d;

			if(gst_video_parse_caps_framerate (caps,&fps_n,&fps_d))
				ofLog(OF_LOG_VERBOSE,"fps_n:%d fps_d:%d",fps_n,fps_d);
			else
				ofLog(OF_LOG_WARNING,"Gstreamer: cannot get framerate, frame seek won't work");
		}else{
			ofLog(OF_LOG_WARNING,"Gstreamer: cannot get pad caps, frame seek won't work");
		}*/
        gst_object_unref(GST_OBJECT(pad));
    }else{
		ofLog(OF_LOG_ERROR,"GStreamer: cannot get sink pad");
		return false;
	}
	generic->bLoaded = true;
	return generic->bLoaded;
}


//----------------------------------------------------------
void ofVideoPlayerImpl :: gstHandleMessage()
{
	GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(gstPipeline));
	while(gst_bus_have_pending(bus)) {
		GstMessage* msg = gst_bus_pop(bus);

		ofLog(OF_LOG_VERBOSE,"GStreamer: Got %s message", GST_MESSAGE_TYPE_NAME(msg));

		switch (GST_MESSAGE_TYPE (msg)) {

			case GST_MESSAGE_BUFFERING:
				gint pctBuffered;
				gst_message_parse_buffering(msg,&pctBuffered);
				ofLog(OF_LOG_VERBOSE,"GStreamer: buffering %i\%", pctBuffered);
				if(isStream && !generic->bLoaded){
					allocate();
				}
				if(pctBuffered<100){
					gst_element_set_state (gstPipeline, GST_STATE_PAUSED);
				}else if(!generic->getPaused()){
					gst_element_set_state (gstPipeline, GST_STATE_PLAYING);
				}
			break;

			case GST_MESSAGE_DURATION:{
				GstFormat format=GST_FORMAT_TIME;
				if(!gst_element_query_duration(gstPipeline,&format,&durationNanos))
					ofLog(OF_LOG_WARNING,"GStreamer: cannot query duration");
			}break;

			case GST_MESSAGE_STATE_CHANGED:
                GstState oldstate, newstate, pendstate;
				gst_message_parse_state_changed(msg, &oldstate, &newstate, &pendstate);
				gstData.pipelineState=newstate;
				seek_lock();
				if(posChangingPaused && newstate==GST_STATE_PLAYING){
                    gst_element_set_state (gstPipeline, GST_STATE_PAUSED);
                    posChangingPaused=false;
				}
				seek_unlock();


				ofLog(OF_LOG_VERBOSE,"GStreamer: state changed from %d to %d (%d)", oldstate, newstate, pendstate);
			break;

			case GST_MESSAGE_ASYNC_DONE:
				gstData.speed=generic->speed;
				ofLog(OF_LOG_VERBOSE,"GStreamer: async done");
			break;

			case GST_MESSAGE_ERROR: {
				GError *err;
				gchar *debug;
				gst_message_parse_error(msg, &err, &debug);

				ofLog(OF_LOG_ERROR, "GStreamer Plugin: Embedded video playback halted; module %s reported: %s",
					  gst_element_get_name(GST_MESSAGE_SRC (msg)), err->message);

				g_error_free(err);
				g_free(debug);

				gst_element_set_state(GST_ELEMENT(gstPipeline), GST_STATE_NULL);

			}break;

			case GST_MESSAGE_EOS:
				ofLog(OF_LOG_VERBOSE,"GStreamer: end of the stream.");
				bIsMovieDone = true;

				switch(loopMode){

					case OF_LOOP_NORMAL:{
						GstFormat format = GST_FORMAT_TIME;
						GstSeekFlags flags = (GstSeekFlags) (GST_SEEK_FLAG_FLUSH |GST_SEEK_FLAG_KEY_UNIT);
						gint64 pos;
						gst_element_query_position(GST_ELEMENT(gstPipeline),&format,&pos);

						float loopSpeed;
						if(pos>0)
							loopSpeed=-generic->speed;
						else
							loopSpeed=generic->speed;
						if(!gst_element_seek(GST_ELEMENT(gstPipeline),
											generic->speed,
											format,
											flags,
											GST_SEEK_TYPE_SET,
											0,
											GST_SEEK_TYPE_SET,
											durationNanos)) {
							ofLog(OF_LOG_WARNING,"GStreamer: unable to seek");
						}
					}break;

					case OF_LOOP_PALINDROME:{
						GstFormat format = GST_FORMAT_TIME;
						GstSeekFlags flags = (GstSeekFlags) (GST_SEEK_FLAG_FLUSH |GST_SEEK_FLAG_KEY_UNIT);
						gint64 pos;
						gst_element_query_position(GST_ELEMENT(gstPipeline),&format,&pos);
						float loopSpeed;
						if(pos>0)
							loopSpeed=-generic->speed;
						else
							loopSpeed=generic->speed;
						if(!gst_element_seek(GST_ELEMENT(gstPipeline),
											loopSpeed,
											GST_FORMAT_UNDEFINED,
											flags,
											GST_SEEK_TYPE_NONE,
											0,
											GST_SEEK_TYPE_NONE,
											0)) {
							ofLog(OF_LOG_WARNING,"GStreamer: unable to seek");
						}
					}break;
				}

			break;

			default:
				ofLog(OF_LOG_VERBOSE,"GStreamer: unhandled message");
			break;
		}
		gst_message_unref(msg);
	}

	gst_object_unref(GST_OBJECT(bus));
}


void ofVideoPlayerImpl :: seek_lock(){
    pthread_mutex_lock( &seek_mutex );
}
void ofVideoPlayerImpl :: seek_unlock(){
    pthread_mutex_unlock( &seek_mutex );
}

//////////////////////////////////
void ofVideoPlayer :: implInit(ofVideoPlayer *generic) {
    impl = new ofVideoPlayerImpl(generic);
}

void ofVideoPlayer :: implFree() {
    delete impl;
    impl = NULL;
}

void ofVideoPlayer :: implEnterIdleMovie() {
	impl->gstHandleMessage();
	if (bLoaded == true) {
		ofGstDataLock(&(impl->gstData));

		bHavePixelsChanged = impl->gstData.bHasPixelsChanged;
		if (bHavePixelsChanged){
			impl->gstData.bHasPixelsChanged=false;
			impl->bIsMovieDone = false;
			if(bUseTexture)
				tex.loadData(pixels, width, height, GL_RGB);
		}

		ofGstDataUnlock(&(impl->gstData));
	}
}

void ofVideoPlayer :: implCloseMovie() {
	gst_element_set_state(GST_ELEMENT(impl->gstPipeline), GST_STATE_NULL);
	//gst_object_unref(gstSink);
	gst_object_unref(impl->gstPipeline);
}

bool ofVideoPlayer :: implLoadMovie(string name) {
	bLoaded      		= false;
	bPaused 			= true;
	speed 				= 1.0f;
	bHavePixelsChanged 	= false;
	if( name.find( "://",0 ) == string::npos){
		name 			= "file://"+ofToDataPath(name,true);
		impl->isStream		= false;
	}else{
		impl->isStream		= true;
	}
	ofLog(OF_LOG_VERBOSE,"loading "+name);

	impl->gstData.loop		= g_main_loop_new (NULL, FALSE);



	impl->gstPipeline = gst_element_factory_make("playbin","player");
	g_object_set(G_OBJECT(impl->gstPipeline), "uri", name.c_str(), NULL);

	// create the oF appsink for video rgb without sync to clock
	impl->gstSink = gst_element_factory_make("appsink", NULL);
	GstCaps *caps = gst_caps_new_simple("video/x-raw-rgb", NULL);
	gst_app_sink_set_caps(GST_APP_SINK(impl->gstSink), caps);
	gst_caps_unref(caps);
	gst_base_sink_set_sync(GST_BASE_SINK(impl->gstSink), false);

	g_object_set (G_OBJECT(impl->gstPipeline),"video-sink",impl->gstSink,NULL);


	GstElement *audioSink = gst_element_factory_make("gconfaudiosink", NULL);
	g_object_set (G_OBJECT(impl->gstPipeline),"audio-sink",audioSink,NULL);


	// pause the pipeline
	if(gst_element_set_state(GST_ELEMENT(impl->gstPipeline), GST_STATE_PAUSED) ==
	   GST_STATE_CHANGE_FAILURE) {
		ofLog(OF_LOG_ERROR, "GStreamer: unable to set pipeline to paused\n");
		gst_object_unref(impl->gstPipeline);
		return false;
	}

	impl->gstData.pipeline=impl->gstPipeline;

	// set the appsink to emit signals to get eos and errors
	g_object_set (G_OBJECT (impl->gstSink), "emit-signals", TRUE, "sync", TRUE, NULL);
	g_signal_connect (impl->gstSink, "new-buffer", G_CALLBACK (on_new_buffer_from_source), &(impl->gstData));

	if(!impl->isStream){
		return impl->allocate();
	}


	// unreference all elements so they get deleted on close
	gst_object_unref(audioSink);

	return true;
}

void ofVideoPlayer :: implStart() {
	bHavePixelsChanged = true;
	bStarted = true;
	bPlaying = true;
	setPaused(false);
}

void ofVideoPlayer :: implPlay() {
	if (!bStarted){
		start();
	}else {
		bPlaying = true;
		setPaused(false);
	}
}

void ofVideoPlayer :: implStop() {
	setPaused(true);
}

void ofVideoPlayer :: implSetVolume(int volume) {
	gdouble gvolume = CLAMP(volume,0,10);
	g_object_set(G_OBJECT(impl->gstPipeline), "volume", gvolume, NULL);
}

void ofVideoPlayer :: implSetLoopState(int state) {
	impl->loopMode = state;
}

void ofVideoPlayer :: implSetPosition(float pct) {
	//pct = CLAMP(pct, 0,1);// check between 0 and 1;
	GstFormat format = GST_FORMAT_TIME;
	GstSeekFlags flags = (GstSeekFlags) (GST_SEEK_FLAG_FLUSH|GST_SEEK_FLAG_ACCURATE);
	gint64 pos = (guint64)((double)pct*(double)impl->durationNanos);
	if(bPaused){
	    impl->seek_lock();
		gst_element_set_state (impl->gstPipeline, GST_STATE_PLAYING);
		impl->posChangingPaused=true;
		impl->seek_unlock();
	}
	if(speed>0){
		if(!gst_element_seek(GST_ELEMENT(impl->gstPipeline),speed, 	format,
				flags,
				GST_SEEK_TYPE_SET,
				pos,
				GST_SEEK_TYPE_SET,
				-1)) {
		ofLog(OF_LOG_WARNING,"GStreamer: unable to change speed");
		}
	}else{
		if(!gst_element_seek(GST_ELEMENT(impl->gstPipeline),speed, 	format,
				flags,
				GST_SEEK_TYPE_SET,
				0,
				GST_SEEK_TYPE_SET,
				pos)) {
		ofLog(OF_LOG_WARNING,"GStreamer: unable to change speed");
		}
	}
}

void ofVideoPlayer :: implSetFrame(int frame) {
	float pct = (float)frame / (float)impl->gstData.nFrames;
   setPosition(pct);
}

float ofVideoPlayer :: implGetDuration() {
	return (float)impl->durationNanos/(float)GST_SECOND;
}

float ofVideoPlayer :: implGetPosition() {
	gint64 pos=0;
	GstFormat format=GST_FORMAT_TIME;
	if(!gst_element_query_position(GST_ELEMENT(impl->gstPipeline),&format,&pos))
		ofLog(OF_LOG_ERROR,"GStreamer: cannot query position");
	return (float)pos/(float)impl->durationNanos;
}

bool ofVideoPlayer :: implGetIsMovieDone() {
	return impl->bIsMovieDone;
}

void ofVideoPlayer :: implSetSpeed(float _speed) {
	GstFormat format = GST_FORMAT_TIME;
	GstSeekFlags flags = (GstSeekFlags) (GST_SEEK_FLAG_FLUSH |GST_SEEK_FLAG_ACCURATE);
	gint64 pos;

	if(speed==0){
		gst_element_set_state (impl->gstPipeline, GST_STATE_PAUSED);
		return;
	}

	if(!gst_element_query_position(GST_ELEMENT(impl->gstPipeline),&format,&pos))
		ofLog(OF_LOG_ERROR,"GStreamer: cannot query position");

	if(!bPaused)
		gst_element_set_state (impl->gstPipeline, GST_STATE_PLAYING);

	if(speed>0){
		if(!gst_element_seek(GST_ELEMENT(impl->gstPipeline),speed, 	format,
				flags,
				GST_SEEK_TYPE_SET,
				pos,
				GST_SEEK_TYPE_SET,
				-1)) {
		ofLog(OF_LOG_WARNING,"GStreamer: unable to change speed");
		}
	}else{
		if(!gst_element_seek(GST_ELEMENT(impl->gstPipeline),speed, 	format,
				flags,
				GST_SEEK_TYPE_SET,
				0,
				GST_SEEK_TYPE_SET,
				pos)) {
		ofLog(OF_LOG_WARNING,"GStreamer: unable to change speed");
		}
	}

	ofLog(OF_LOG_VERBOSE,"Gstreamer: speed change to %f", speed);
}

void ofVideoPlayer :: implSetPaused(bool _bPause) {
	if(bLoaded){
		if(bPaused)
			gst_element_set_state (impl->gstPipeline, GST_STATE_PAUSED);
		else
			gst_element_set_state (impl->gstPipeline, GST_STATE_PLAYING);
	}
}


int ofVideoPlayer :: implGetTotalNumFrames() {
	return impl->gstData.nFrames;
}

#endif	// OF_VIDEO_PLAYER_GSTREAMER
