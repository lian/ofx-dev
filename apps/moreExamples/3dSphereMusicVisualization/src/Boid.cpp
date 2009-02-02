
#include "Boid.h"

Boid::Boid(){
	for(int i=0; i<NumP; i++){
		p[i].pos.x = ofGetWidth()/2;
		p[i].pos.y = ofGetHeight()/2;
		p[i].pos.z = 0;
	}
	p[0].k = 0.7;
	p[0].k = 0.5;
	radius = 0;
	currentRadius = 0;
	larg = 10;
	
	r = (int)ofRandom(40, 60);
	g = (int)ofRandom(10, 30);
	b = (int)ofRandom(0, 10);
	
	band = (int)ofRandom(0, NumBands);
	alpha = 0;
	currentAlpha = 0;
}

Boid::~Boid(){}


void Boid::updateRadius(float target){
	float damp = 0.6;
	int minRadius = 200;
	if(currentRadius < target) currentRadius = target;
	else currentRadius *= damp;
	radius = currentRadius + minRadius;
}


void Boid::move(ofxVec3f target, float _alpha){
	int minAlpha = 50;
	float damp = 0.5;
	
	if(currentAlpha < _alpha) currentAlpha = _alpha;
	currentAlpha *= damp;
	alpha = currentAlpha + minAlpha;
	alpha = MIN(alpha, 255);
	p[0].move(target);
	for(int i=1; i<NumP; i++){
		p[i].move(p[i-1].pos);
		float ang = atan2(p[i-1].pos.y - p[i].pos.y, p[i].pos.x - p[i-1].pos.x);
		float scaling = larg*sin(PI/(NumP-1)*i);
		p[i].offX = sin(ang)*scaling;
		p[i].offY = cos(ang)*scaling;
	}
}

void Boid::render(){
	glBegin(GL_QUAD_STRIP);
	for(int i=0; i<NumP; i++){
	float angCam = atan2(camPos->x - p[i].pos.x, camPos->z - p[i].pos.z);
	
	float alphaVal = alpha-(float)i/(NumP-1)*alpha;
	ofSetColor(r-(alphaVal-50)/10, g, b, alphaVal);
		glVertex3f(p[i].pos.x-p[i].offX*cos(angCam), p[i].pos.y-p[i].offY, p[i].pos.z-p[i].offX*sin(angCam));
		glVertex3f(p[i].pos.x+p[i].offX*cos(angCam), p[i].pos.y+p[i].offY, p[i].pos.z+p[i].offX*sin(angCam));
	}
	glEnd();
	//renderContours();
}

void Boid::renderContours(){
glPushAttrib(GL_COLOR_BUFFER_BIT);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ofSetColor(10,10, 10, 40);
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<NumP; i++){
		glVertex3f(p[i].pos.x-p[i].offX, p[i].pos.y-p[i].offY, p[i].pos.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<NumP; i++){
		glVertex3f(p[i].pos.x+p[i].offX, p[i].pos.y+p[i].offY, p[i].pos.z);
	}
	glEnd();
	/*
	glBegin(GL_LINES);
	for(int i=0; i<NumP; i++){
		glVertex3f(p[i].pos.x-p[i].offX, p[i].pos.y-p[i].offY, p[i].pos.z);
		glVertex3f(p[i].pos.x+p[i].offX, p[i].pos.y+p[i].offY, p[i].pos.z);
	}
	glEnd();*/
glPopAttrib();
	
}

