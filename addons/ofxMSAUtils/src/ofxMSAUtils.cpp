/*
 *  ofxMSAUtils.cpp
 *  Meshmerizer
 *
 *  Created by Mehmet Akten on 19/02/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "ofxMSAUtils.h"

void msaClear() {
	glClearColor(ofBgColorPtr()[0], ofBgColorPtr()[1], ofBgColorPtr()[2], ofBgColorPtr()[3]);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void msaConstrain(float &pos, float &vel, float min, float max, float bounce) {
	if(pos < min) {
		pos = min;
		vel = fabs(vel) * bounce;
	} else if(pos > max) {
		pos = max;
		vel = -fabs(vel) * bounce;
	}
}	

void msaConstrain(ofPoint &pos, ofPoint &vel, ofPoint &min, ofPoint &max, float bounce) {
	msaConstrain(pos.x, vel.x, min.x, max.x, bounce);
	msaConstrain(pos.y, vel.y, min.y, max.y, bounce);
	msaConstrain(pos.z, vel.z, min.z, max.z, bounce);
}


void msaDrawFPS() {
	msaDrawFPS(10, ofGetHeight() - 10);
}

void msaDrawFPS(int x, int y) {
	ofDisableAlphaBlending();
	ofFill();
	glColor4f(0, 0, 0, 1);
	ofRect(x - 10, y - 20, x + 100, y + 10);
	glColor4f(0.9, 0.9, 0.9, 1);
	ofDrawBitmapString("FPS: "+ofToString(ofGetFrameRate(), 2), x, y);
}

void msaDrawFPS(int color) {
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
	ofSetColor(color);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 20, ofGetHeight()-20);
}


void msaSetCursor(bool forceOn) {
	if(forceOn || ofGetWindowMode() == OF_WINDOW) ofShowCursor();
	else ofHideCursor();
}


static GLfloat tex_coords[] = {
0, 0,
1, 0,
1, 1,
0, 1
};

static GLfloat verts[] = {
-0.5f, -0.5f,
0.5f, -0.5f,
0.5f, 0.5f,
-0.5f, 0.5f
};


void msaDrawQuadAtCorner() {
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
	glEnableClientState(GL_VERTEX_ARRAY);		
	glVertexPointer(2, GL_FLOAT, 0, verts );
	glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

void msaDrawQuadAtCenter() {
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer(2, GL_FLOAT, 0, verts );
	glEnableClientState(GL_VERTEX_ARRAY);		
	glVertexPointer(2, GL_FLOAT, 0, verts );
	glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}


void msaDrawTexture(GLuint texId, GLenum textureTarget ) {
	glEnable(textureTarget);
	glBindTexture(textureTarget, texId);
	msaDrawQuadAtCenter();
	glDisable(textureTarget);
}
