/*
 *  MyTestObject.h
 *  openFrameworks
 *
 *  Created by Mehmet Akten on 04/10/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

/********  Test sample for ofxInteractiveObject									********/
/********  Make sure you open your console to see all the events being output	********/


#pragma once

#include "ofxMSAInteractiveObject.h"

#define		IDLE_COLOR		0xFFFFFF
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0xFF0000


class MyTestObject : public ofxMSAInteractiveObject {
public:
	void setup() {
		printf("MyTestObject::setup() - hello!\n");
		enableMouseEvents();
		enableKeyEvents();
	}
	
	
	void exit() {
		printf("MyTestObject::exit() - goodbye!\n");
	}
	
	
	void update() {
		//		x = ofGetWidth()/2 + cos(ofGetElapsedTimef() * 0.2) * ofGetWidth()/4;
		//		y = ofGetHeight()/2 + sin(ofGetElapsedTimef() * 0.2) * ofGetHeight()/4;
	}
	
	
	void draw() {
		if(isMouseDown()) ofSetColor(DOWN_COLOR);
		else if(isMouseOver()) ofSetColor(OVER_COLOR);
		else ofSetColor(IDLE_COLOR);
		
		ofRect(x, y, width, height);
	}
	
	virtual void onRollOver(int x, int y) {
		printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
	}
	
	virtual void onRollOut() {
		printf("MyTestObject::onRollOut()\n");
	}
	
	virtual void onMouseMove(int x, int y){
		printf("MyTestObject::onMouseMove(x: %i, y: %i)\n", x, y);
	}
	
	virtual void onDragOver(int x, int y, int button) {
		printf("MyTestObject::onDragOver(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onDragOutside(int x, int y, int button) {
		printf("MyTestObject::onDragOutside(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onPress(int x, int y, int button) {
		printf("MyTestObject::onPress(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onRelease(int x, int y, int button) {
		printf("MyTestObject::onRelease(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void onReleaseOutside(int x, int y, int button) {
		printf("MyTestObject::onReleaseOutside(x: %i, y: %i, button: %i)\n", x, y, button);
	}
	
	virtual void keyPressed(int key) {
		printf("MyTestObject::keyPressed(key: %i)\n", key);
	}
	
	virtual void keyReleased(int key) {
		printf("MyTestObject::keyReleased(key: %i)\n", key);
	}
	
};