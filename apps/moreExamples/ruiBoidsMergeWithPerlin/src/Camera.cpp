/*
 *  Camera.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"

Camera::Camera(){
	fieldOfView = 65.0f;
	yon = 10000.0f;
	hither = 0.5f;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	aspectRatio = (float)w/(float)h;
	
	vx = vy = vz = 0;
	k = 0.1;
	damp = 0.3;
	upX = 0;
	upY = 1;
	upZ = 0;
	eyeX = eyeY = eyeZ = 0;
	
	camX = ofGetWidth()/2;
	camY = ofGetHeight()/2;
	camZ = 0;
}

Camera::~Camera(){};

void Camera::goTo(float _x, float _y, float _z){
	ax = (_x - camX)*k;
	vx += ax;
	vx *= damp;
	camX += ax;
	
	ay = (_y - camY)*k;
	vy += ay;
	vy *= damp;
	camY += vy;
	
	az = (_z - camZ) * k;
	vz += az;
	vz *= damp;
	camZ += az;
	
	eyeX = camX;
	eyeY = camY;
	eyeZ = camZ-1;
	
}

void Camera::place(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, hither, yon);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ);
}
