#ifndef PONTO_H
#define PONTO_H


#include "ofMain.h"

#include "ofxVectorMath.h"

#include "perlin.h"


class Ponto{
public:
	
	ofxVec3f acel;
	ofxVec3f vel;
	ofxVec3f pos;
	float k, damp;
	float offX, offY;
	float theta, phi;
	float alphaVal;
	int band;
	int radius, currentRadius;
	
	Ponto();
	~Ponto();
	
	void move(ofxVec3f target);
	void updateRadius(float _radius);
	void updateAlpha(float _alpha);
};

#endif