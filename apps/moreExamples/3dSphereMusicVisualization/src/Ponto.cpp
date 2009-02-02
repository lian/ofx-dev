

#include "Ponto.h"
using namespace std;

Ponto::Ponto(){
	k = 0.7;
	damp = 0.4;
	pos.x = ofRandom(0, ofGetWidth());
	pos.y = ofRandom(0, ofGetHeight());
	pos.z = ofRandom(-500, 500);
	acel = 0;
	vel = 0;
	alphaVal = 0;
}

Ponto::~Ponto(){}

void Ponto::move(ofxVec3f target){
	acel = (target - pos) * k;
	vel += acel;
	vel *= damp;
	pos += vel;
}

void Ponto::updateRadius(float _radius){
	float damp = 0.99;
	int minRadius = 120;
	if(currentRadius < _radius) currentRadius = _radius;
	else currentRadius *= damp;
	radius = currentRadius + minRadius;
	
}

void Ponto::updateAlpha(float _alpha){
float damp = 0.9;
if(alphaVal < _alpha) alphaVal = _alpha;
else alphaVal *= damp;
}


