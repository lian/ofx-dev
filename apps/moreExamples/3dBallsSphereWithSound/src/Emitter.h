#ifndef EMITTER_H
#define EMITTER_H


#include "ofMain.h"

#include "ofxVectorMath.h"

#include "ofx3D.h"

#include "perlin.h"
#include "Constants.h"



class Emitter{
public:
	float rotX, rotY, radius, currentRadius;
	int band, type;
	
	ofxVec3f pos, acel, vel;
	
	Emitter();
	~Emitter();
	
	void updateRadius(float _target);
	void move(ofxVec3f target);
	void render();
};


#endif EMITTER_H