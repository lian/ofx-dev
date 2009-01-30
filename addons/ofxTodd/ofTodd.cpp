/*
 *  ofTodd.cpp
 *  openFrameworks
 *
 *  Created by Todd Vanderlin on 2/24/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofTodd.h"

void ofDrawFPS() {
	ofSetColor(0, 255, 0);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 20, ofGetHeight()-20);
}
void ofDrawFPS(int x, int y) {
	ofSetColor(0, 255, 0);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, x, y);
}
void ofDrawFPS(int color) {
	ofSetColor(color);
	string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 20, ofGetHeight()-20);
}

//------------------------------------------------------------ Mouse On
bool ofMouseOn(int mx, int my, float x, float y, float w, float h) {
}



//------------------------------------------------------------ String Utils
string ofSecondsToMinutes(float s) {
	//if(s > 0.0) {
	//		float m = s/60.0;
	//		string ms = ofToString(m);
	//		int findDot = ms.find(".", 0);
	//		ms.erase(findDot);
	//		ms.insert(findDot, ":");
	//		return "["+ofToString(findDot) + "] "+ms;
	//	}
}

//-------------------------------------------------------------

/*
 These are math function grabbed from the processing 
 utils. They are handdy and fast.
 */


//--------------------------------------------------
float ofNorm(float value, float start, float stop) {
	return (value - start) / (stop - start);
}

float ofMap(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

float sq(float a) {
    return a*a;
}

float dist(float a, float b, float c, float d) {
	return sqrt(double((a - c) * (a - c) + (b - d) * (b - d)));
}

int ofConstrain(int amt, int low, int high) {
	return (amt < low) ? low : ((amt > high) ? high : amt);
}

float ofConstrain(float amt, float low, float high) {
	return (amt < low) ? low : ((amt > high) ? high : amt);
}

float ofDegrees(float radians) {
	return radians * RAD_TO_DEG;
}

float ofRadians(float degrees) {
    return degrees * DEG_TO_RAD;
}

float ofLerp(float start, float stop, float amt) {
    return start + (stop-start) * amt;
}


//--------------------------------------------------
//PARTICLE UTILS

float ofRanWidth() {
	return ofRandom(0, ofGetWidth());
}
float ofRanHeight() {
	return ofRandom(0, ofGetHeight());
}









