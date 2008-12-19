#include "Thingy.h"

Thingy::Thingy() {
	//
	printf("created thingy at random position: %p\n", this);
	// choose a random starting position
	float random_x = ofRandom( 0, ofGetWidth()  );
	float random_y = ofRandom( 0, ofGetHeight() );
	// call the setup
	setup( random_x, random_y );
}

Thingy::Thingy(const Thingy &thingy) {
	printf("copied thingy: %p\n", this);
	setup(thingy.pos.x, thingy.pos.y);
}

Thingy::Thingy(float _x, float _y) {
	printf("created thingy(x,y): %p\n", this);
	// use given starting position
	setup(_x, _y);
}

Thingy::~Thingy() {
	// this could be useful for whenever we get rid of an object
	printf("killed thingy: %p\n", this);
}

void Thingy::setup(float _x, float _y) {
	// set up position & size of thingy
	pos.x = _x;
	pos.y = _y;
	speed.x = 0;
	speed.y = 0;
	radius = ofRandom( 5, 20 );
}

void Thingy::update() {
	// move around
	pos.x += ofRandom(-1,1);
	pos.y += ofRandom(-1,1);
	// block at edges of screen
	pos.x = max(radius, min(pos.x, ofGetScreenWidth()-radius)  );
	pos.y = max(radius, min(pos.y, ofGetScreenHeight()-radius) );
}

void Thingy::draw() {
	// drawing parameters
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetColor( 255,0,0,180 );
	// draw the thingy insides
	ofFill();
	ofCircle( pos.x, pos.y, radius );
	// draw the thingy border
	ofNoFill();
	ofCircle( pos.x, pos.y, radius );
}

bool Thingy::mousePressed(float _x, float _y) {
	// when given an x & y we figure out distance
	float vx = pos.x - _x; 
	float vy = pos.y - _y;
	float dist = (float)sqrt(vx*vx + vy*vy);
	// and return whether that distance is inside of the radius of our circle
	return (dist <= radius);
}
