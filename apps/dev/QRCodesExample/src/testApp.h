#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxQRCodes.h"


class testApp : public ofBaseApp {
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		ofImage						orgImg;
		ofxCvColorImage				colorImg;
		ofxCvGrayscaleImage			detectImage;

		string	debug_string;
};

#endif
