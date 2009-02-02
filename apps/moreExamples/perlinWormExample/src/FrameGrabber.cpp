

#include "FrameGrabber.h"


FrameGrabber::FrameGrabber(string _fileName, int _numFrames, bool _close){
	fileName = _fileName; 
	maxFrames = _numFrames;
	close = _close;
	frameCounter = 0;
	minutes = seconds = 0;
}

void FrameGrabber::grabFrame(){
	frameCounter++;
	if(frameCounter <= maxFrames){
		string file = fileName + ofToString(frameCounter, 0) + ".png";
		img.grabScreen(0,0,ofGetWidth(), ofGetHeight());
		img.saveImage(file);
		float elapsedTime = ofGetElapsedTimef();
		seconds = (int)elapsedTime%60;
		minutes = (int)(elapsedTime/60);
		
		string ellapsed = " elapsed: " + ofToString(minutes, 0) + "min "+ ofToString(seconds, 0) + "sec\n";
		std::cout << ofToString(frameCounter, 0) + " of " + ofToString(maxFrames, 0) + " frames " + 
		"at " + ofToString(ofGetFrameRate(),2) + "fps" + ellapsed;
	} else if(close)OF_EXIT_APP(0);
}
