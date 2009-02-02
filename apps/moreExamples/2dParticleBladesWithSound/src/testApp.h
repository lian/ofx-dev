#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "particle.h"

#define OF_ADDON_USING_OFXVECTORMATH
// #define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

class testApp : public ofBaseApp {
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
	
		void emitParticles(int x, int y, int vel_x, int vel_y);
		void emitParticlesColor(int x, int y, int vel_x, int vel_y, int red, int blue, int green, float alpha);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		// let's make a vector of them
		vector <particle> particles;
	
		ofSoundPlayer music;
		float * spectrum;
	
		vector <ofxVec3f> trail;
		void addTrailPoint(int x, int y, int z);
		void drawTrail();
	
		bool 	mouseDown;
		int		maxParticles;
	
};

#endif
	
