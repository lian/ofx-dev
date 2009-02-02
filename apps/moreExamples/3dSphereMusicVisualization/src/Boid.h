#ifndef BOID_H
#define BOID_H


#include "ofMain.h"

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofAddons.h"
#include "perlin.h"
#include "Ponto.h"
#include "Constants.h"
#include "Particles.h"

class Boid{
public:
	Ponto p[NumP];
	float rotX, rotY, radius, currentRadius;
	int r, g, b;
	int larg;
	int band;
	float alpha, currentAlpha;
	ofxVec3f *camPos;
	
	vector <Particles> *partPtr;
	
	Boid();
	~Boid();
	
	void updateRadius(float _target);
	void move(ofxVec3f target, float _alpha);
	void render();
	void renderContours();


};


#endif BOID_H