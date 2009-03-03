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

#include "ofxMouse.h"


ofxMouse* ofxMouse::_thisInstance = 0;


ofxMouse* ofxMouse::get() {
	if(_thisInstance == 0) {  
		_thisInstance = new ofxMouse;
    }
    return _thisInstance;
	
}



ofxMouse::ofxMouse() {
	printf("ofxMouse::ofxMouse()\n");
	ofMouseEvents.addListener(this);
	ofAppEvents.addListener(this);
	
	for(int i=0; i<MAX_MOUSE_BUTTONS; i++) button[i] = false;
	
	isFirstMove = true;
	
	vel.set(0, 0);
	prev.set(0, 0);
}


string ofxMouse::toString() {
	char sz[255];
	sprintf(sz, "MOUSE Position: (%i, %i) | Previous:  (%i, %i) | Velocity:  (%i, %i) | Button1: %i | Button2: %i | Button3: %i \n", x, y, prev.x, prev.y, vel.x, vel.y, button[0], button[1], button[2] );
	return string(sz);
}

bool ofxMouse::isButtonDown(int b) {
	return button[b];
}



void ofxMouse::update() {
	if(!isFirstMove) vel = *this - prev;
}

void ofxMouse::draw() {
	prev.set(*this);
}

void ofxMouse:: mouseMoved( int _x, int _y ) {
	set(_x, _y, 0);
	isFirstMove = false;
//		norm.set(_x * 1.0f/ofGetWidth(), _y * 1.0f/ofGetHeight());
}

void ofxMouse::mouseDragged( int _x, int _y, int _button ) {
	mouseMoved(_x, _y);
	isFirstMove = false;
}

void ofxMouse::mousePressed( int _x, int _y, int _button ) {
	mouseMoved(_x, _y);
	button[_button] = true;
}

void ofxMouse::mouseReleased() {
}

void ofxMouse::mouseReleased(int _x, int _y, int _button ) {
	mouseMoved(_x, _y);
	button[_button] = false;
}

