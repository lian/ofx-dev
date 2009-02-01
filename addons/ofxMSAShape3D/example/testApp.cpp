#include "testApp.h"

void testApp::setup(){	 
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);
	ofSetFullscreen(true);
	
	// preallocate space for 5000 vertices.
	myObj.reserve(5000);	
	
	// this is not nessecary but will speed up the addition of the first 5000 glVertex() commands between glBegin / glEnd
	// Even after the first 5000 glVertex() calls, you can still carry on calling glVertex and add new vertices...
	// but the arrays will be resized with every call to glVertex so will be a bit slow. 
	// Best to reserve as much space as you think you'll need up front
	// Its ok to over-reserve thousands cos memory usage is quite low (reserve(1000) allocates 48KB)
	// By default space for 1000 vertices is allocated...
}


// create a function to slightly fade out the current screen to black
void testApp::fadeScreen(float fadeAmount) {
	// enable blending, choose normal blend mode and enable depth testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glDisable(GL_DEPTH_TEST);
	
	// choose semi-transparent black color
	myObj.glColor(0, 0, 0, fadeAmount);
	
	// draw a black semi-transparent rectangle across whole screen to fade it out a bit
	myObj.glRect(0, 0, ofGetWidth(), ofGetHeight());
}


void testApp::draw() {
	// fade screen a bit
	fadeScreen(0.05f);
	
	// disable blending, enable depth testing and clear depth buffer
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// get current time (could use ofGetElapsedTimef() but I DONT want it to be fps independant
	// cos when I'm saving frames and it's running slow I want it to behave the same
	float curTime = ofGetFrameNum() * 1.0f/60.0f;
	
	// choose start rotation based on curTime
	float theta = sin(curTime * 0.17f) * TWO_PI;
	
	// set start position offset from center of screen
	float startOffset = -50.0f * sin(curTime * 0.09f);
	pos.set(ofGetWidth()/2 + cos(theta) * startOffset, ofGetHeight()/2 + sin(theta) * startOffset, 0);
	
	// begin a triangle strip
	myObj.glBegin(GL_TRIANGLE_STRIP);
	for(int i=0; i<5000; i++) {
		// calculate and set colors
		// (RGB components modulate sinusoidally based on time and iteration count)
		myObj.glColor(sin(curTime * 0.8f + i * 0.0011f) * 0.5f + 0.5f, sin(curTime * 0.7f + i * 0.0013f) * 0.5f + 0.5f, sin(curTime * 0.3f + i * 0.0017f) * 0.5f + 0.5f);
		
		// do some maths to calculate vertex positions
		theta += sin(curTime * 0.1f + i * 0.00062f) * 2.0f * DEG_TO_RAD * i * 0.0004 + sin(curTime*0.2f + i * 0.0009f) * 3.0f * DEG_TO_RAD;
		float cos_t = cos(theta);
		float sin_t = sin(theta);
		
		// x, y cumulatively rotates, z position modules sinusoidally based on time and iteration count
		pos += ofPoint(cos_t, sin_t, sin(curTime * 0.5f + i*0.002f) * 0.5);
		
		// place vertex
		myObj.glVertex(pos.x, pos.y, pos.z);
		
		// do some math to calculate another vertex position
		// (perpendicular to rotation, and thickness modules based on time and iteration count)
		ofPoint pos2 = pos + ofPoint(sin_t, -cos_t) * ofMap(sin(curTime * 0.4f * ( 1.0f + i * 0.001f) + i * 0.06f + sin(i*0.001f) * 0.2f), -1, 1, 5, 10 +  i * 0.01f);
		
		// place second vertex (can also pass pointer (array) to coordinates)
		myObj.glVertex3v(pos2.v);
	}
	
	// end vertices and draw to screen
	myObj.glEnd();
}
