/*
 *  Boid.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Boid.h"

Boid::Boid(Perlin *_noise, vector <Particles> *_part){
part = _part;
	noise = _noise;
	step = 15;
	k = 0.01;
	
	/*
	float iniX = ofRandom(0, ofGetWidth());
	float iniY = ofRandom(0, ofGetHeight());
	float iniZ = ofRandom(-500, 500);
	*/
	
	float iniX = ofGetWidth()/2;
	float iniY = ofGetHeight()/2;
	float iniZ = 0;
	

	for(int i=0; i<numPoints; i++){
		p[i] = new Ponto;
		p[i]->vx = p[i]->vy = p[i]->vz = 0;
		p[i]->x = iniX;
		p[i]->y = iniY;
		p[i]->z = iniZ;
		p[i]->offX = p[i]->offY = p[i]->ang = 0;
	}
	
	r = (int)ofRandom(30, 100);
	g = (int)ofRandom(0, 20);
	b = (int)ofRandom(0, 40);
	
}
Boid::~Boid(){
	for(int i=0; i<numPoints; i++){
		delete p[i];
	}
	delete p;
}

void Boid::mover(){
	
// this part where i get the movements based on perlin noise is adapted from a Robert Hodgin source 
// which can be found here: www.flight404.com/blog/?p=113
	float radXZ = noise->Get(p[0]->x/fieldComplex, p[0]->z/fieldComplex)*TWO_PI;
	float radY = noise->Get(p[0]->x/fieldComplex, p[0]->y/fieldComplex)*TWO_PI;
	
	p[0]->vx = cos(radXZ)*15 + var(step);
	p[0]->vy = -sin(radY)*15 + var(step);
	p[0]->vz = sin(radXZ)*15 + var(step);
	
	p[0]->x += p[0]->vx;
	p[0]->y += p[0]->vy;
	p[0]->z += p[0]->vz;
	
	
	for(int i=1; i<numPoints; i++){
		p[i]->ang = atan2(p[i-1]->y - p[i]->y, p[i]->x - p[i-1]->x);
		p[i]->offY = cos(p[i]->ang)*larg*(sin(PI/(numPoints-1)*i));
		p[i]->offX = sin(p[i]->ang)*larg*(sin(PI/(numPoints-1)*i));
		
		p[i]->ax = (p[i-1]->x - p[i]->x) * pK;
		p[i]->vx += p[i]->ax;
		p[i]->vx *= pDamp;
		p[i]->x += p[i]->vx;
		
		p[i]->ay = (p[i-1]->y - p[i]->y) * pK;
		p[i]->vy += p[i]->ay;
		p[i]->vy *= pDamp;
		p[i]->y += p[i]->vy;
		
		p[i]->az = (p[i-1]->z - p[i]->z) * pK;
		p[i]->vz += p[i]->az;
		p[i]->vz *= pDamp;
		p[i]->z += p[i]->vz;
	}
}

void Boid::constrainMovement(float _averX, float _averY, float _averZ){
		 p[0]->ax = (_averX - p[0]->x) * k;
		 p[0]->vx += p[0]->ax;
		 p[0]->x += p[0]->vx;
		 
		 p[0]->ay = (_averY - p[0]->y)*k;
		 p[0]->vy += p[0]->ay;
		 p[0]->y += p[0]->vy;
		 
		 p[0]->az = (_averZ - p[0]->z) * k;
		 p[0]->vz += p[0]->az;
		 p[0]->z += p[0]->vz;
}

void Boid::render(){
	glBegin(GL_QUAD_STRIP);
	for(int i=0; i<numPoints; i++){
//	float alphaVal = 100-(100/(numPoints-1)*(i+(numPoints/6)));
float alphaVal = 100-(100/(numPoints-1));
	ofSetColor(r, g, b, alphaVal);
		glVertex3f(p[i]->x+p[i]->offX, p[i]->y+p[i]->offY, p[i]->z);
		glVertex3f(p[i]->x-p[i]->offX, p[i]->y-p[i]->offY, p[i]->z);
	}
	glEnd();
	
	/*
	ofSetColor(r, g, b, 50);
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<numPoints; i++){
		glVertex3f(p[i]->x+p[i]->offX, p[i]->y+p[i]->offY, p[i]->z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<numPoints; i++){
		glVertex3f(p[i]->x-p[i]->offX, p[i]->y-p[i]->offY, p[i]->z);
	}
	
	glEnd();
	
	glBegin(GL_LINES);
	for(int i=0; i<numPoints; i++){
		glVertex3f(p[i]->x+p[i]->offX, p[i]->y+p[i]->offY, p[i]->z);
		glVertex3f(p[i]->x-p[i]->offX, p[i]->y-p[i]->offY, p[i]->z);
	}
	glEnd();*/
	
	
}

GLfloat Boid::var(GLint _step){
	return (GLfloat)(ofRandomf() * _step);
}

