#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXFIDUCIALFINDER
#include "ofAddons.h"

class testApp : public ofBaseApp {
	
	public:
	
		ofVideoGrabber 		vidGrabber;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage	grayDiff;
		ofxCvColorImage		colorImg;
	
		ofxFiducialTracker	fidfinder;
	
		int 				threshold;
		bool				bLearnBakground;
		bool				backgroundSubOn;
	
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		
};

#endif
