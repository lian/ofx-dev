

#include "ofBall.h"


ofBall::ofBall() {
	speedX = ofRandom(-1, 1);
	speedY = ofRandom(-1, 1);
	
	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
	
	dim=20;
	
	r = 255;
	g = 0;
	b = 0;
}


void ofBall::add_velocity(float _x, float _y) {
	speedX = _x;
	speedY = _y;
}


void ofBall::update() {
	
	if(x < 0 ){
			x = 0;
			speedX *= -1;
	} else if(x > ofGetWidth()){
			x = ofGetWidth();
			speedX *= -1;
	}
	
	
	if(y < 0 ){
			y = 0;
			speedY *= -1;
	} else if(y > ofGetHeight()){
			y = ofGetHeight();
			speedY *= -1;
	} 
	
	x+=speedX;
	y+=speedY;
	
}


void ofBall::draw() {
	
	ofSetColor(r,g,b);
	ofNoFill();
	ofCircle(x, y, dim);

} 