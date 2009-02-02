// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// A simple Particle class

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"
#define OF_ADDON_USING_OFXVECTORMATH
#include "ofAddons.h"


class Particle {

	public:
	
		ofxVec2f loc;
		ofxVec2f vel;
		ofxVec2f acc;
		float r;
		float timer;

		// One constructor
		Particle(ofxVec2f a, ofxVec2f v, ofxVec2f l, float r_);

		// Another constructor (the one we are using here)
		Particle(ofxVec2f l);

		// Method to update location
		void update();

		// Method to display
		void render();

		// Is the particle still useful?
		bool dead();
};
#endif


