#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXMSASHAPE3D

#include "ofMain.h"
#include "ofAddons.h"

class testApp : public ofBaseApp {
	public:
		void setup();
		void draw();
		
		void fadeScreen(float fadeAmount);
		
		MSAShape3D myObj;
		ofPoint pos;
};

#endif
