#ifndef _VIDEO_HAND_DETECTOR_
#define _VIDEO_HAND_DETECTOR_

#include "ofMain.h"
#include "ofxOpenCV.h"
#include "videoBlob.h"
#include "videoHandFingerDetector.h"


#define MAX_N_HANDS					5
#define MAX_N_TRACKED_FINGERS		20

class videoHandDetector{
	
	public:
		
		void setup(int w, int h);
		void update(ofxCvColorImage video);
		void draw(float x, float y);
		
		ofxCvGrayscaleImage		videoImageGray;
		ofxCvContourFinder		contourFinder;
		int 					width;
		int 					height;
		ofxCvGrayscaleImage		handDetectionImage;
		videoHandFingerDetector	fingerFinder;
		
		int 					nHands;
		handBlob				hands[MAX_N_HANDS];		
		
		trackedFinger			fingers[MAX_N_TRACKED_FINGERS];
};

#endif	
