#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
//#include "ofAddons.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
};

#endif
	
