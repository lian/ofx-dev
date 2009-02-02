#include "ofGraphics.h"
#include "Emitter.h"

Emitter::Emitter(){
	
	radius = 0;
	currentRadius = 0;
	type   = 0;
}

Emitter::~Emitter(){}


void Emitter::updateRadius(float target){
	float damp = 0.6;
	int minRadius = 150;
	if(currentRadius < target) currentRadius = target;
	else currentRadius *= damp;
	radius = currentRadius + minRadius;
}


void Emitter::move(ofxVec3f target){
	float k = 0.5, damp = 0.5;
	acel = (target - pos) * k;
	vel += acel;
	vel *= damp;
	pos += vel;
}

void Emitter::render(){
	glColor3f(1.0f, 0.0f, 0.0f);
	ofCircle(pos.x, pos.y, (radius)*2);
	// ofTranslate(0, 0, pos.z);	
	// if (type == 0) {
	// 	ofCircle(pos.x, pos.y, (radius)*2);
	//    // ofCircle(pos.x, pos.y, pos.z, size*scale);
	// } else if (type == 1) {
	// 	ofCube((radius)*4, pos.x, pos.y);
	// } else if (type == 2) {
	// 	ofSphere((radius)*4, pos.x, pos.y, 5);
	// }
	// ofTranslate(0, 0, -pos.z);
}
