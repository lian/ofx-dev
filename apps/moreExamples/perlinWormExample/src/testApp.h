#ifndef _TEST_APP
#define _TEST_APP

#define  OF_ADDON_USING_OFXVECTORMATH
#include "ofMain.h"
#include "ofAddons.h"
#include "ofx3DUtils.h"


#include "Perlin.h"
#include "Worm.h"
#include "Background.h"

#define NUMW 50

//#define GRAB_FRAME_SEQUENCE

#ifdef GRAB_FRAME_SEQUENCE
#include "FrameGrabber.h"
#endif

class testApp : public ofSimpleApp{
	
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
		
		//
		
		ofxVec3f center;
		Perlin *noise;
		
		ofxCamera camera;
		ofxLight camLight;
		ofxLight upLight;
		ofxLight frontLight;
		ofxLight backLight;
			
		Worm *worms[NUMW];
		int num;
		
		Background background;

		bool bShowMouse;
		bool bPause;
		
		#ifdef GRAB_FRAME_SEQUENCE
		FrameGrabber *frameGrabber;
		#endif
};

#endif
	
