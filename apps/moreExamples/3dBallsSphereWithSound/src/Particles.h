
#ifndef PARTICLES_H
#define PARTICLES_H

#include "ofMain.h"

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofAddons.h"
#include "ofx3D.h"

#include "perlin.h"
#include "Constants.h"
#include "Ponto.h"


class Particles{
public:
	ofxVec3f pos, acel, vel;
	int color[3];
	int life, iniLife, type;
	float size;
	float G;
	bool	doTail;
	Perlin *noise;
	
	Ponto pontos[NumP];

	Particles(ofxVec3f iniPos, ofxVec3f _vel,  Perlin *_noise, int _type);
	~Particles();
	
	void move();
	void render();
	void moveTrail();
	void renderTrail();
};

#endif