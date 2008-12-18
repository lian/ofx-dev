#ifndef OFVTHREADLISTENER_H_
#define OFVTHREADLISTENER_H_

#include "ofxCvVideoThread.h"

//------------------------------------------------------------
//  listener:

class ofxCvVThreadEventArgs{
	
};

class ofxCvVThreadListener{
public:
	ofxCvVThreadListener(){}
	
	virtual ~ofxCvVThreadListener(){};

	void _xVThreadNewFrame( const void* sender, ofxCvVThreadEventArgs& event ) {
		ofxCvVideoThread * vThread = (ofxCvVideoThread*)sender;
		
		vThread->addReadingThread();
		
		switch (vThread->imgType){
		case OFX_VTHREAD_PLAIN_RGB24:
			xVThreadNewFrame( vThread->getPixels() );
		break;
		case OFX_VTHREAD_CV_COLOR:
			xVThreadNewFrame(vThread->getCvColorImage());
		break;
		case OFX_VTHREAD_CV_GREY:
			xVThreadNewFrame(vThread->getCvGrayImage());
		break;
		}
		
		vThread->removeReadingThread();
	}
	
	void subscribeNewFrame(ofxCvVideoThread* vThread){
		vThread->addNewFrameListener(this);
	}
	
protected:

	virtual void xVThreadNewFrame(unsigned char * frame)=0;
	virtual void xVThreadNewFrame(ofxCvGrayscaleImage * frame)=0;
	virtual void xVThreadNewFrame(ofxCvColorImage * frame)=0;
	
};

#endif /*OFVTHREADLISTENER_H_*/
