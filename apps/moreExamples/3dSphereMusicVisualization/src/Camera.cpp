/*
 *  Camera.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"
using namespace std;

Camera::Camera(){
	fieldOfView = 65.0f;
	yon = 10000.0f;
	hither = 0.5f;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	aspectRatio = (float)w/(float)h;
	
	k = 0.3;
	damp = 0.3;
	
	vel = 0;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;
		
	eye.x = ofGetWidth()/2;
	eye.y = ofGetHeight()/2;
	eye.z = 0;
	
	radius = 1000;
}

Camera::~Camera(){};

void Camera::goTo(ofxVec3f target){
	acel = (target - pos) * k;
	vel += acel;
	vel *= damp;
	pos += vel;
		
	eye.x = center->x;
	eye.y = center->y;
	eye.z = center->z;
}

void Camera::move(){
	rotY += 0.2;
	radius = 1000;
	ofxVec3f rot = ofxVec3f(0, 0, radius);
	rot.rotate(0, rotY, 0);
	ofxVec3f pos = (*center) + rot;
	goTo(pos);
	

	
	
}

void Camera::place(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, hither, yon);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z, eye.x, eye.y, eye.z, up.x, up.y, up.z);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
}
