/***********************************************************************
 
 This class is for drawing a fluidsolver using the openFrameworks texture
 
 /***********************************************************************
 
 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/ 


#include "ofxMSAFluidDrawer.h"

ofxMSAFluidDrawer::ofxMSAFluidDrawer() {
	//	printf("ofxMSAFluidDrawer::ofxMSAFluidDrawer()\n");	
	_pixels				= NULL;
	_byteCount			= 0;
	_fluidSolver		= NULL;
	_didICreateTheFluid	= false;
	alpha				= 1;
	setDrawMode(FLUID_DRAW_COLOR);
}

ofxMSAFluidDrawer::~ofxMSAFluidDrawer() {
	//	printf("ofxMSAFluidDrawer::~ofxMSAFluidDrawer()\n");		
	deleteFluidSolver();
}



ofxMSAFluidSolver* ofxMSAFluidDrawer::setup(int NX, int NY) {
	//	printf("ofxMSAFluidDrawer::createFluidSolver(%i, %i, %.6f, %.6f, %.6f)\n", NX, NY, dt, visc, fadeSpeed);
	deleteFluidSolver();
	_fluidSolver = new ofxMSAFluidSolver;
	_fluidSolver->setup(NX, NY);
	createTexture();
	
	return _fluidSolver;
}

ofxMSAFluidSolver* ofxMSAFluidDrawer::setup(ofxMSAFluidSolver* f) {
	deleteFluidSolver();
	_fluidSolver = f;
	createTexture();
	
	return _fluidSolver;
}

ofxMSAFluidSolver* ofxMSAFluidDrawer::getFluidSolver() {
	return _fluidSolver;
}

void ofxMSAFluidDrawer::createTexture() {
	if(_pixels) delete []_pixels;
	int texWidth = _fluidSolver->getWidth()-2;
	int texHeight =_fluidSolver->getHeight()-2;
	
	_pixels = new unsigned char[texWidth * texHeight * 4];
	
#ifdef FLUID_TEXTURE
	tex.allocate(texWidth, texHeight, GL_RGBA);	
#endif
}


void ofxMSAFluidDrawer::reset() {
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::reset() - Fluid not ready\n");
		return;
	}
	_fluidSolver->reset();
}

void ofxMSAFluidDrawer::update() {
	if(!isFluidReady()) {
		printf("ofxMSAFluidDrawer::updateFluid() - Fluid not ready\n");
		return;
	}
	_fluidSolver->update();
}


void ofxMSAFluidDrawer::setDrawMode(int newDrawMode) {
	drawMode = newDrawMode;
	if(drawMode < 0) drawMode = FLUID_DRAW_MODE_COUNT-1;
	else if(drawMode >= FLUID_DRAW_MODE_COUNT) drawMode = 0;
}

void ofxMSAFluidDrawer::incDrawMode() {
	setDrawMode(drawMode + 1);
}

void ofxMSAFluidDrawer::decDrawMode() {
	setDrawMode(drawMode - 1);
}

int ofxMSAFluidDrawer::getDrawMode() {
	return drawMode;
}

const char* ofxMSAFluidDrawer::getDrawModeName() {
	switch(drawMode) {
		case 0:
			return "FLUID_DRAW_COLOR";
		case 1:
			return "FLUID_DRAW_MOTION";
		case 2:
			return "FLUID_DRAW_SPEED";
		case 3:
			return "FLUID_DRAW_VECTORS";
		default:
			return "FLUID DRAW MODE NOT FOUND";
	}
}



void ofxMSAFluidDrawer::draw(float x, float y) {
	draw(x, y, ofGetWidth(), ofGetHeight());
}


void ofxMSAFluidDrawer::draw(float x, float y, float renderWidth, float renderHeight) {
	switch(drawMode) {
		case FLUID_DRAW_COLOR:
			drawColor(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_MOTION:
			drawMotion(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_SPEED:
			drawSpeed(x, y, renderWidth, renderHeight);
			break;
			
		case FLUID_DRAW_VECTORS:
			drawVectors(x, y, renderWidth, renderHeight);
			break;
			
	}
}


void ofxMSAFluidDrawer::drawColor(float x, float y, float renderWidth, float renderHeight, bool withAlpha) {
	int fw = _fluidSolver->getWidth();
	int fh = _fluidSolver->getHeight();
	
	ofPoint vel;
	ofPoint color;
	int index = 0;
	for(int j=1; j < fh-1; j++) {
		for(int i=1; i < fw-1; i++) {
			_fluidSolver->getInfoAtCell(i, j, &vel, &color);
			float speed2 = fabs(vel.x) * fw + fabs(vel.y) * fh;
			int speed = MIN(speed2 * 255 * alpha, 255);
			int r = _pixels[index++] = MIN(color.x * 255 * alpha, 255);
			int g = _pixels[index++] = MIN(color.y * 255 * alpha, 255);		
			int b = _pixels[index++] = MIN(color.z * 255 * alpha, 255);	
			int a = _pixels[index++] = withAlpha ? MAX(b, MAX(r, g)) : 255;
		}
	}  
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, tex.getWidth(), tex.getHeight(), GL_RGBA);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
}



void ofxMSAFluidDrawer::drawMotion(float x, float y, float renderWidth, float renderHeight, bool withAlpha) {
	int fw = _fluidSolver->getWidth();
	int fh = _fluidSolver->getHeight();
	
	ofPoint vel;
	int index = 0;
	for(int j=1; j < fh-1; j++) {
		for(int i=1; i < fw-1; i++) {
			_fluidSolver->getInfoAtCell(i, j, &vel, NULL);
			float speed2 = fabs(vel.x) * fw + fabs(vel.y) * fh;
			int speed = MIN(speed2 * 255 * alpha, 255);
			int r = _pixels[index++] = MIN(fabs(vel.x) * fw * 255 * alpha, 255);
			int g = _pixels[index++] = MIN(fabs(vel.y) * fh * 255 * alpha, 255);		
			int b = _pixels[index++] = 0;
			int a = _pixels[index++] = withAlpha ? speed : 255;
			
		}
	}  
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, tex.getWidth(), tex.getHeight(), GL_RGBA);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
}


void ofxMSAFluidDrawer::drawSpeed(float x, float y, float renderWidth, float renderHeight, bool withAlpha) {
	int fw = _fluidSolver->getWidth();
	int fh = _fluidSolver->getHeight();
	
	ofPoint vel;
	int index = 0;
	for(int j=1; j < fh-1; j++) {
		for(int i=1; i < fw-1; i++) {
			_fluidSolver->getInfoAtCell(i, j, &vel, NULL);
			float speed2 = fabs(vel.x) * fw + fabs(vel.y) * fh;
			int speed = MIN(speed2 * 255 * alpha, 255);
			int r = _pixels[index++] = speed;
			int g = _pixels[index++] = speed;
			int b = _pixels[index++] = speed;
			int a = _pixels[index++] = withAlpha ? speed : 255;
		}
	}  
	
#ifdef FLUID_TEXTURE
	tex.loadData(_pixels, tex.getWidth(), tex.getHeight(), GL_RGBA);
	tex.draw(x, y, renderWidth, renderHeight);
#endif
}


void ofxMSAFluidDrawer::drawVectors(float x, float y, float renderWidth, float renderHeight) {
	int fw = _fluidSolver->getWidth();
	int fh = _fluidSolver->getHeight();
	
//	int xStep = renderWidth / 10;		// every 10 pixels
//	int yStep = renderHeight / 10;		// every 10 pixels

	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(renderWidth/(fw-2), renderHeight/(fh-2), 1.0);
	
	float velMult = 50000;
	float maxVel = 5./20000;
	
	ofPoint vel;
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);
	for (int j=0; j<fh-2; j++ ){
		for (int i=0; i<fw-2; i++ ){
			_fluidSolver->getInfoAtCell(i+1, j+1, &vel, NULL);
			float d2 = vel.x * vel.x + vel.y * vel.y;
			if(d2 > maxVel * maxVel) {
				float mult = maxVel * maxVel/ d2;
//				float mult = (d2 - maxVel * maxVel) / d2;
				vel.x *= mult;
				vel.y *= mult;
			}
			vel *= velMult;
			
//			if(dx*dx+dy*dy > velThreshold) {
//				float speed2 = fabs(vel.x) * fw + fabs(vel.y) * fh;
#ifndef TARGET_OPENGLES
				glBegin(GL_LINES);
				glColor3f(0, 0, 0); glVertex2f(i, j);
				glColor3f(1, 1, 1); glVertex2f(i + vel.x, j + vel.y);
				glEnd();
#endif			
//			printf("%.8f, %.8f\n", vel.x, vel.y);
//			}
		}
	}
	glPopMatrix();
	
}



void ofxMSAFluidDrawer::deleteFluidSolver() {
	//	printf("ofxMSAFluidDrawer::deleteFluidSolver()\n");	
	if(_fluidSolver && _didICreateTheFluid) {
		delete _fluidSolver;
		_fluidSolver = NULL;
		
		if(_pixels) delete []_pixels;
		_pixels = NULL;
		
#ifdef FLUID_TEXTURE		
		tex.clear();
#endif		
	}	
}

bool ofxMSAFluidDrawer::isFluidReady() {
	if(!_fluidSolver) {
		printf("ofxMSAFluidDrawer::isFluidReady() - No fluid solver\n");
		return false;
	}
	
	if(!_fluidSolver->isInited()) {
		printf("ofxMSAFluidDrawer::isFluidReady() - Fluid solver not initialized yet, call init()\n");
		return false;
	}
	
	return true;
}

