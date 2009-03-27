#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxObjLoader.h"

class testApp : public ofBaseApp {
	
	public:
  
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		//my 3d model
		ofxObjLoader crane;
        bool bMousePressed;
};

#endif	
