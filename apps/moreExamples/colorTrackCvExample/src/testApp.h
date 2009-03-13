#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

#include "ofxCvColorTrack.h"

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

		ofVideoGrabber 		vidGrabber0;
		ofVideoGrabber		vidGrabber1;
		
		ofxCvColorImage  colorImg0;
		ofxCvColorImage	colorImg1;
		ofxCvColorImage  posterized;
		
		ofxCvColorTrack	cTracker0;
		ofxCvColorTrack	cTracker1;

		ofxCvContourFinder 	contourFinder0;
		ofxCvContourFinder 	contourFinder1;


		int					threshold;
		float					xAvg;
		float					yAvg;
		bool				bLearnBakground;


};

#endif
