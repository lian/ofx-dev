// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// A class to describe a group of Particles
// An ArrayList is used to manage the list of Particles 

#include "ParticleSystem.h"

//--------------------------------------------------------------
ParticleSystem::ParticleSystem() {
   
}

//--------------------------------------------------------------
ParticleSystem::ParticleSystem(int num, ofxVec2f v) {
	origin.set(v);					// Store the origin point		
	for (int i = 0; i < num; i++) {
		particles.push_back(Particle(origin));    // Add "num" amount of particles to the arraylist
	}

}
//--------------------------------------------------------------
void ParticleSystem::init(int num, ofxVec2f v) {
	origin.set(v);					// Store the origin point			
	for (int i = 0; i < num; i++) {
		particles.push_back(Particle(origin));    // Add "num" amount of particles to the arraylist
	}

}
//--------------------------------------------------------------
void ParticleSystem::run() {
	// Cycle through the ArrayList backwards b/c we are deleting
	for (int i = particles.size()-1; i >= 0; i--) {
		particles[i].update();
		if (particles[i].dead()) {
			particles.erase(particles.begin() + i);
		}
	}
}
//--------------------------------------------------------------
void ParticleSystem::render() {
	// Cycle through the ArrayList and render particles	
	for (int i = 0; i < particles.size(); i++) {
		particles[i].render();
	}
}

//--------------------------------------------------------------
void ParticleSystem::addParticle() {
	particles.push_back(Particle(origin));
}

//--------------------------------------------------------------
void ParticleSystem::addParticle(Particle p) {
	particles.push_back(p);
}

//--------------------------------------------------------------
// A method to test if the particle system still has particles
bool ParticleSystem::dead() {
	if (particles.empty()) {
		return 1;
	} else {
		return 0;
	}
}





