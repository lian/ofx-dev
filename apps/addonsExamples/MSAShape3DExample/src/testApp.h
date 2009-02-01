#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "MSAShape3D.h"

class testApp : public ofBaseApp {
	public:
		void setup();
		void draw();
		
		void fadeScreen(float fadeAmount);
		
		MSAShape3D myObj;
		ofPoint pos;
};

#endif
