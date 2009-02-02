#pragma once

#include "ofMain.h"

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofAddons.h"

class Ponto{
public:
	ofxVec3f acel, vel, pos;
	float k, damp;
	float ang;
	Ponto();
	Ponto(ofxVec3f iniPos);
	void move(ofxVec3f target);

};