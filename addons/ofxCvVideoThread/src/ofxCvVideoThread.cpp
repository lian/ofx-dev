#include "ofxCvVideoThread.h"
#include "ofxCvVThreadManager.h"


ofxCvVideoThread::ofxCvVideoThread()
{
	//fileName	= "";
	
	width		= 0;
	height		= 0 ;
	speed		= 0;
	
	_isPaused	= false;
	x			= 0;
	y			= 0;
	eventManager = new ofxCvVThreadEventManager();
	_deviceID = 0;
	_bTalkToMe = false;
	readingThreads=0;
	
	frame=0;
	
}

ofxCvVideoThread::~ofxCvVideoThread()
{
	close();
}

void ofxCvVideoThread::init(int w, int h, ofxVThreadImgType _imgType){
	width = w;
	height = h;
	imgType = _imgType;
	
	colorImg.allocate(w,h);
	grayImage.allocate(w,h);
	
	startThread(true, _bTalkToMe);   // blocking, verbose
}

void ofxCvVideoThread::play(){
	_isPaused=false;
	if(!isThreadRunning())
		startThread( true, _bTalkToMe);
}

void ofxCvVideoThread::stop(){
    stopThread(); 
}

void ofxCvVideoThread::threadedFunction(){
	/*if( fileName != ""){
		vidGrabber=cvCreateFileCapture("");
		speed=60;
	}else{*/
	vidGrabber= cvCreateCameraCapture( _deviceID );
	cvSetCaptureProperty(vidGrabber,CV_CAP_PROP_FRAME_WIDTH,width);
	cvSetCaptureProperty(vidGrabber,CV_CAP_PROP_FRAME_HEIGHT,height);
	speed=cvGetCaptureProperty(vidGrabber,CV_CAP_PROP_FPS);
	
	if(_bTalkToMe) printf("source fps: %f",cvGetCaptureProperty(vidGrabber,CV_CAP_PROP_FPS));
		
	while(true){

		IplImage* image = cvQueryFrame(vidGrabber);
	

		lock();
		if(!readingThreads && image){			
			switch (imgType){
				case OFX_VTHREAD_CV_COLOR:
					colorImg.setFromCVImage(image);
				break;
				case OFX_VTHREAD_CV_GREY:
					colorImg.setFromCVImage(image);
					grayImage.setFromColorImage(colorImg);
				default:
				break;
			}
			unlock();
			eventManager->notifyNewFrame(this);
			frame++;
		}else{
			unlock();
		}
		ofSleepMillis(5);
	}
}

void ofxCvVideoThread::update(){
}

void ofxCvVideoThread::draw(){
	draw(x,y);
}

void ofxCvVideoThread::draw( int _x, int _y ){
	lock();
	switch (imgType){
		case OFX_VTHREAD_CV_COLOR:
			colorImg.draw(_x,_y);
		break;
		
		case OFX_VTHREAD_CV_GREY:
			grayImage.draw(_x,_y);
			
		default:
		break;
	}
	unlock();
}

void ofxCvVideoThread::draw( int _x, int _y, int _w, int _h ){
	lock();
	switch (imgType){
		case OFX_VTHREAD_CV_COLOR:
			colorImg.draw( _x ,_y, _w, _h );
		break;
		
		case OFX_VTHREAD_CV_GREY:
			grayImage.draw( _x ,_y, _w, _h );
			
		default:
		break;
	}
	unlock();
}


bool ofxCvVideoThread::isFrameNew(){
	return _isFrameNew;
}

void ofxCvVideoThread::close(){
	// delete cvCapture
}


unsigned char * ofxCvVideoThread::getPixels(){
	return colorImg.getPixels();
}


ofxCvColorImage * ofxCvVideoThread::getCvColorImage(){

	return	&colorImg;
}

ofxCvGrayscaleImage * ofxCvVideoThread::getCvGrayImage(){

	return	&grayImage;
}


void ofxCvVideoThread::setVerbose(bool bTalkToMe){
	_bTalkToMe = bTalkToMe;
}

void ofxCvVideoThread::setDeviceID(int deviceID){
	_deviceID = deviceID;
}

void ofxCvVideoThread::addReadingThread(){
	lock();
		readingThreads++;
	unlock();
}

void ofxCvVideoThread::removeReadingThread(){
	lock();
		readingThreads--;
	unlock();
}


//--------------------------------------------------------------------------
//  events:

void ofxCvVideoThread::addNewFrameListener(ofxCvVThreadListener * listener){
	eventManager->addNewFrameListener(listener);
}

void ofxCvVideoThread::removeNewFrameListener(ofxCvVThreadListener * listener){
	eventManager->removeNewFrameListener(listener);
}
