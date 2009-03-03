/***********************************************************************
 
 This class is for drawing a fluidsolver using the openFrameworks texture
 
 /***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/


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
	_drawMode = newDrawMode;
}


void ofxMSAFluidDrawer::draw(float x, float y) {
	draw(x, y, ofGetWidth(), ofGetHeight());
}


void ofxMSAFluidDrawer::draw(float x, float y, float renderWidth, float renderHeight) {
	switch(_drawMode) {
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

