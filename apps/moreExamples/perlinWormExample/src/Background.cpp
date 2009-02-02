#include "Background.h"

Background::Background(){
	
}

void Background::render(){
	glDisable(GL_DEPTH_TEST);
	ofSetupScreen();
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(ofGetWidth(), 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(ofGetWidth(), ofGetHeight());
	glVertex2f(0.0f, ofGetHeight());
	glEnd();
	glEnd();
	glEnable(GL_DEPTH_TEST);
}