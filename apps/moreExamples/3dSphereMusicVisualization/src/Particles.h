
#ifndef PARTICLES_H
#define PARTICLES_H

#include "ofMain.h"

#include "ofxVectorMath.h"

#include "perlin.h"
#include "Constants.h"


class Particles{
public:
	ofxVec3f pos, acel, vel;
	ofxVec3f center;
	int minDist;
	int minDistSQ;
	float r, g, b;
	int life;
	int floor;
	float size, iniSize;
	float G;
	Perlin *noise;
	ofxVec3f *camPos;
	
	
	Particles(ofxVec3f iniPos, ofxVec3f _vel,  Perlin *_noise, ofxVec3f *_camPos);
	~Particles();
	
	void move();
	void render();
};

#endif