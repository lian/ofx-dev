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


#include "ofMain.h"

#include "ofAppiPhoneWindow.h"
#include "iPhoneGlobals.h"



// use for checking if stuff has been initialized
#define NOT_INITIALIZED			-1000000



/******** Constructor ************/

ofAppiPhoneWindow::ofAppiPhoneWindow() {
	printf("ofAppiPhoneWindow::ofAppiPhoneWindow()\n");
	nFrameCount = 0;
	bEnableSetupScreen = true;
	
	windowPos.set(NOT_INITIALIZED, NOT_INITIALIZED);
	windowSize.set(NOT_INITIALIZED, NOT_INITIALIZED);
	screenSize.set(NOT_INITIALIZED, NOT_INITIALIZED);
}



/******** Initialization methods ************/

void ofAppiPhoneWindow::setupOpenGL(int w, int h, int screenMode) {
	printf("ofAppiPhoneWindow::setupOpenGL()\n");
	
	windowMode = screenMode;	// use this as flag for displaying status bar or not
	iPhoneGlobals.iPhoneOFWindow = this;

	// w & h are ignored, currently Apple don't allow windows which aren't fullscreen
	// DO NOTHING ELSE, opengl will be setup by the app which creates an opengl view
}


void ofAppiPhoneWindow::initializeWindow() {
	// DO NOTHING, window will be created when the app is launched
}


void  ofAppiPhoneWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr) {
	printf("ofAppiPhoneWindow::runAppViaInfiniteLoop()\n");
	iPhoneGlobals.baseApp = appPtr;		// save reference to our testApp
	
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	UIApplicationMain(nil, nil, nil, @"iPhoneAppDelegate");		// this will run the infinite loop checking all events
	[pool release];	
}




/******** Set Window properties ************/

void setWindowPosition(int x, int y) {
	// DO NOTHING, you're not really allowed to play with window for now
}

void setWindowShape(int w, int h) {
	// DO NOTHING, you're not really allowed to play with window for now
}



/******** Get Window/Screen properties ************/

// return cached pos, read if nessecary
ofPoint	ofAppiPhoneWindow::getWindowPosition() {
	if(windowPos.x == NOT_INITIALIZED) {
		CGPoint p = [[[UIApplication sharedApplication] keyWindow] bounds].origin;
		windowPos.set(p.x, p.y, 0);
	}
	return windowPos;
}


// return cached size, read if nessecary
ofPoint	ofAppiPhoneWindow::getWindowSize() {
	if(windowSize.x == NOT_INITIALIZED) {
		CGSize s = [[[UIApplication sharedApplication] keyWindow] bounds].size;
		windowSize.set(s.width, s.height, 0);
	}
	return windowSize;
}


// return cached size, read if nessecary
ofPoint	ofAppiPhoneWindow::getScreenSize() {
	if(screenSize.x == NOT_INITIALIZED) {
		CGSize s = [[UIScreen mainScreen] bounds].size;
		screenSize.set(s.width, s.height, 0);
	}
	return screenSize;
}

int	ofAppiPhoneWindow::getWindowMode() {
	return windowMode;
}

float ofAppiPhoneWindow::getFrameRate() {
	return ofFrameRate;
}

/******** Other stuff ************/
void ofAppiPhoneWindow::setFrameRate(float targetRate) {
	[iPhoneGlobals.appDelegate setFrameRate:targetRate];
}

int	ofAppiPhoneWindow::getFrameNum() {
	return nFrameCount;
}

void ofAppiPhoneWindow::setWindowTitle(string title) {
}


void ofAppiPhoneWindow::setFullscreen(bool fullscreen) {
	[[UIApplication sharedApplication] setStatusBarHidden:fullscreen animated:YES];
	
	if(fullscreen) windowMode		= OF_FULLSCREEN;
	else windowMode					= OF_WINDOW;
}

void ofAppiPhoneWindow::toggleFullscreen() {
	if(windowMode == OF_FULLSCREEN) setFullscreen(false);
	else setFullscreen(true);
}


void ofAppiPhoneWindow::enableSetupScreen(){
	bEnableSetupScreen = true;
};

void ofAppiPhoneWindow::disableSetupScreen(){
	bEnableSetupScreen = false;
};


void ofAppiPhoneWindow::timerLoop() {
	iPhoneGlobals.baseApp->update();
	
	// this could be taken out and included in ofAppBaseWIndow
	glViewport( 0, 0, ofGetWidth(), ofGetHeight() );
	float * bgPtr = ofBgColorPtr();
	bool bClearAuto = ofbClearBg();
	if ( bClearAuto == true){
		glClearColor(bgPtr[0],bgPtr[1],bgPtr[2], bgPtr[3]);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	if(bEnableSetupScreen ) ofSetupScreen();		
	
	iPhoneGlobals.baseApp->draw();
	[iPhoneGlobals.glView swapBuffers];
	
	
	
	// -------------- fps calculation:
  	timeNow = ofGetElapsedTimef();
	if( (timeNow-timeThen) > 0.05f || nFramesForFPS == 0 ) {
		fps = (double)nFramesForFPS / (timeNow-timeThen);
		timeThen = timeNow;
		nFramesForFPS = 0;
		ofFrameRate = 0.9f * ofFrameRate + 0.1f * fps;
  	}
	nFramesForFPS++;
  	// --------------
	
	nFrameCount++;		// increase the overall frame count
}
