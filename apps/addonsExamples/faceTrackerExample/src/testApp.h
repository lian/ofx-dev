#ifndef _TEST_APP
#define _TEST_APP


#define OF_ADDON_USING_OFXOPENCV

#include "ofMain.h"
#include "ofAddons.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera

//this is not part of the addon yet, so include it seperately
#include "ofxCvHaarFinder.h"

class testApp : public ofBaseApp {

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
