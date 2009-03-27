#ifndef SPHERE_H
#define SPHERE_H

#include "ofMain.h"

#include "ofxVectorMath.h"

#include "Ponto.h"
#include "Constants.h"


class Sphere{
public:
	float radius;
	float theta, phi, u, v;
	float rotX, rotY;
	
	ofxVec3f * camPos;
	
	Ponto p[SphereNumRows][SphereNumLines];
	
	Sphere();
	~Sphere();
	
	void move();
	void render();
};

#endif;
