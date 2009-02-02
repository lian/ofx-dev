// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// Particles are generated each cycle through,
// fall with gravity and fade out over time
// A ParticleSystem object manages a variable size 
// list of particles.

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	ofSetFrameRate(60);
	ofxVec2f ps_loc(ofGetWidth()/2,ofGetHeight()/2);
	ofxVec2f ps_loc2(600,200);
	ps.init(2, ps_loc);
}

//--------------------------------------------------------------
void testApp::update(){
	ps.run();
	ps.addParticle();
}

//--------------------------------------------------------------
void testApp::draw(){
	ps.render();
}