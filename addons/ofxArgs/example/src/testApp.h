#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxArgs.h"

class testApp : public ofSimpleApp{
	private:
		ofxArgs* args;
		string option1, option2;
		bool flag1;
	
	public:
		testApp(ofxArgs* args);
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
	
