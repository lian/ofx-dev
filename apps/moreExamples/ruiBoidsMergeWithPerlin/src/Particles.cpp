/*
 *  Particles.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Particles.h"

Particles::Particles(){
	size = ofRandom(2, 5);
	fieldDivide = 1000;	
	G = ofRandom(5, 15);
	life = (int)ofRandom(40, 300);
	step = 2;
	
	r = (int)ofRandom(30, 100);
	g = (int)ofRandom(0, 20);
	b = (int)ofRandom(0, 40);

}

Particles::~Particles(){}

void Particles::partSetup(GLfloat _x, GLfloat _y, GLfloat _z, Perlin *_noise){
	x = _x;
	y = _y;
	z = _z;
	noise  = _noise;
}

void Particles::move(){
life--;
	float radXZ = noise->Get(x/fieldDivide, z/fieldDivide)*TWO_PI;
	float radY = noise->Get(x/fieldDivide, y/fieldDivide)*TWO_PI;
	vx = cos(radXZ)*10+ofRandom(-step, step);
	vy = -sin(radY)*10+ofRandom(-step, step)+G;
	vz = sin(radXZ)*10+ofRandom(-step, step);
	
	x += vx;
	y += vy;
	z += vz;
	

}

void Particles::render(){
	ofSetColor(r, g, b, 100);
	// ofCircle(x, y, z, size);
	ofCircle(x, y, size);
}











