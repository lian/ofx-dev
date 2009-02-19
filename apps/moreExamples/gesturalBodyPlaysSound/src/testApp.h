#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

#include "NSvidbutton.h"

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
		
		ofVideoGrabber 		vidGrabber;
		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		ofxCvColorImage		colorImg;

		ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
		
		float 	counter;
		bool 	bSmooth;
		
		float maxX, maxY;

		int nPixelsWhite;
		int xPos, yPos, width, height;
		
	//	vector<NSvidbutton> buttons[]; // C++ dynamic Array of type NSvidbutton with maximum size = 5
		NSvidbutton buttons[5]; // C++ dynamic Array of type NSvidbutton with maximum size = 5
		int NButtons;
		
};

#endif
