#ifndef OFXVIDEOMANAGER_H_
#define OFXVIDEOMANAGER_H_


#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "ofxCvVideoThread.h"

#include "ofxCvGrayscaleImage.h"
#include "ofxCvColorImage.h"
#include "ofxCvVThreadListener.h"

class ofxCvVideoThread;

//------------------------------------------------------------
//  manager:

using Poco::Delegate;
//	----------------------------------------------------------------------------------------------------

class ofxCvVThreadEventManager{
	
public:
	void addNewFrameListener(ofxCvVThreadListener * listener){
		ofxVThreadNewFrameEvent += Delegate<ofxCvVThreadListener, ofxCvVThreadEventArgs>(listener, &ofxCvVThreadListener::_xVThreadNewFrame);
	}
	
	void removeNewFrameListener(ofxCvVThreadListener * listener){
		ofxVThreadNewFrameEvent -= Delegate<ofxCvVThreadListener, ofxCvVThreadEventArgs>(listener, &ofxCvVThreadListener::_xVThreadNewFrame);
	}
	
	void notifyNewFrame(ofxCvVideoThread * sender){
		ofxVThreadNewFrameEvent.notifyAsync(sender,voidEventArgs);
		ofSleepMillis(5);
	}
	
private:
	Poco::BasicEvent<ofxCvVThreadEventArgs> ofxVThreadNewFrameEvent;
	
	ofxCvVThreadEventArgs 	voidEventArgs;
};



#endif /*OFXVIDEOMANAGER_H_*/
