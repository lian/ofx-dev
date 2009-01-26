#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofAddons.h"
#include "ofx2dFluid.h"
#include "ofBall.h"

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
		
		//the fluid
		ofx2dFluid fluid;
	
		//reusable object to pass color and position info
		ofxFluidObject f_object;
		//reusable object to pass force and position info
		ofxForceObject force;
	
		//velocity data
		ofPoint vel;
		//density data
		float dens;
		//mouse down coordinates
		float mx, my;
	
		//switch color
		bool colorSwitch;
		
		//the ball
		ofBall ball;
		ofBall ball2;
	

		
};

#endif
	
