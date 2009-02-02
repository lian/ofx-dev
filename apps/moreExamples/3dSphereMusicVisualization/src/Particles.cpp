
#include "Particles.h"
using namespace std;

Particles::Particles(ofxVec3f iniPos, ofxVec3f _vel, Perlin *_noise, ofxVec3f *_camPos){
	pos = iniPos;
	vel = _vel;
	noise = _noise;
	life = (int)ofRandom(25, 40);
	size = ofRandom(0.5, 2);
	iniSize = size;

	r = (int)ofRandom(40, 60);
	b = (int)ofRandom(0, 10);
	g = (int)ofRandom(10, 30);
	
	G = -ofRandom(5, 15);
	
	camPos = _camPos;
	
	center = ofxVec3f(ofGetWidth()/2, ofGetHeight()/2, 0);
	minDist = 300;
	minDistSQ = minDist*minDist;
	

}

Particles::~Particles(){}

void Particles::move(){
float damp = 0.6;
	life--;
	int step = 5;
	int div = 4000;
	
	float radXZ = noise->Get(pos.x/div, pos.z/div)* TWO_PI;
	float radY = noise->Get(pos.x/div, pos.y/div)*TWO_PI;
	
	acel.x = cos(radXZ)*5+ofRandom(-step, step);
	acel.y = -sin(radY)*5+ofRandom(-step, step);
	acel.z = sin(radXZ)*5+ofRandom(-step, step);
	
	vel += acel;
	vel.y += G;
	vel *= damp;
	
	pos += vel;
}

void Particles::render(){
ofSetColor(r, g, b, 150*(size/iniSize));
ofNoFill();
	float angCam = atan2(camPos->x - pos.x,camPos->z - pos.z)*RAD_TO_DEG;
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angCam, 0, 1, 0);
	ofCircle(0, 0, iniSize*(size/iniSize));
	glPopMatrix();
	
}

