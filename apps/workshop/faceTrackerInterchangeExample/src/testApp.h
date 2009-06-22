#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"

#define _USE_LIVE_VIDEO     // uncomment this to use a live camera
                            // otherwise, we'll use a movie file
                            // devcpp -> please "rebuild all" ctrl-f11

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();
        
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

        #ifdef _USE_LIVE_VIDEO
		ofVideoGrabber 		vidGrabber;
	#else
		ofVideoPlayer 		vidPlayer;
	#endif
        
        ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvColorImage		colorImg;
        
        ofxCvContourFinder 	contourFinder;
        ofxCvHaarFinder      	haarfinder;
        ofImage             	jesus;
        
	int 			threshold;
	bool			bLearnBakground;
        
        // audio
	float * left;
	float * right;

};

#endif
