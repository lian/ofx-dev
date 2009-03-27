#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"


#define _USE_LIVE_VIDEO		// uncomment this to use a live camera

class testApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif
        
        ofxCvColorImage			colorImg;
        
        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		
        ofxCvContourFinder		contourFinder;
		ofxCvHaarFinder			haarFinder;

		int						threshold;
		bool					bLearnBakground;
		
		
};

#endif
