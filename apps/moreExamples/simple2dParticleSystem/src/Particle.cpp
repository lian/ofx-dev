// Simple Particle System
// Based on code by
// Daniel Shiffman <http://www.shiffman.net>

// A simple Particle class

#include "Particle.h"

//--------------------------------------------------------------
// One constructor
Particle::Particle(ofxVec2f a, ofxVec2f v, ofxVec2f l, float r_) {
	acc = a;
	vel = v;
	loc = l;
	r = r_;
	timer = 150.0;
}

//--------------------------------------------------------------
// Another constructor (the one we are using here)
Particle::Particle(ofxVec2f l) {
	acc.set(0,0.10);
	vel.set(ofRandom(-1,1),ofRandom(-2,0));
	loc = l;
	r = 5.0;
	timer = 150.0;
}

//--------------------------------------------------------------
// Method to update location
void Particle::update() {            
	vel += acc;
	loc += vel;
	timer -= 1.0;
}

//--------------------------------------------------------------
// Method to display
void Particle::render() {
	ofEnableAlphaBlending();
	ofSetColor(255,255,255,timer);
	ofFill();
	ofEllipse(loc.x,loc.y,r,r);
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
// Is the particle still useful?
bool Particle::dead() {
	if (timer <= 0.0) {
		return 1;
	} else {
		return 0;
	}
}



