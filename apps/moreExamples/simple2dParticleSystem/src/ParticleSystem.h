// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// A class to describe a group of Particles
// An ArrayList is used to manage the list of Particles 

#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

#include "Particle.h"

class ParticleSystem {

	public:

		vector<Particle> particles;     // A dynamic array for all the particles
		ofxVec2f origin;				// An origin point for where particles are birthed
		
		ParticleSystem();
		ParticleSystem(int num, ofxVec2f v);
		
		void init(int num, ofxVec2f v);
		
		void run();
		
		void render();

		void addParticle();

		void addParticle(Particle p);

		// A method to test if the particle system still has particles
		bool dead();
		
		bool isParticleDead(Particle _particle);
  
};
#endif



