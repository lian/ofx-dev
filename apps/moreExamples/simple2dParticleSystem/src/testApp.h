// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// Particles are generated each cycle through,
// fall with gravity and fade out over time
// A ParticleSystem object manages a variable size 
// list of particles.

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ParticleSystem.h"

class testApp : public ofBaseApp {
	
	public:
		
		void setup();
		void update();
		void draw();
		
		ParticleSystem ps;
};

#endif
