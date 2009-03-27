#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxVectorMath.h"
#include "ofxXmlSettings.h"

#include "renderManager.h"


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		

        renderManager rm;

        ofRectangle guiIn;
        ofRectangle guiOut;

        bool toggleImage, doRender;
        ofImage twoScreenImage;
};

#endif
