#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXVECTORGRAPHICS
#define OF_ADDON_USING_OFXXMLSETTINGS


#include "ofMain.h"
#include "ofAddons.h"
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
