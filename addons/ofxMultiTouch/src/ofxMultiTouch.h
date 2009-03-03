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


#pragma once

#include <list>
#include "ofxMultiTouchListener.h"

class ofxMultiTouchHandler : public ofxMultiTouchListener {
public:
	void addListener(ofxMultiTouchListener* o) {
		listeners.push_back(o);
	}
	
	void removeListener(ofxMultiTouchListener* o) {
		listeners.remove(o);
	}
	
	// multitouch engine should call this when a 'down' is detected
	// use ofxMultiTouchCustomData *data to send any platform specific data
	void touchDown(int x, int y, int touchId, ofxMultiTouchCustomData *data = 0) {
		for(std::list<ofxMultiTouchListener*>::iterator it=listeners.begin(); it!=listeners.end(); ++it) {
			ofxMultiTouchListener* o = *it;
			o->touchDown(x, y, touchId, data);
		}
	}
	
	// multitouch engine should call this when a 'move' (drag) is detected
	// use ofxMultiTouchCustomData *data to send any platform specific data
	void touchMoved(int x, int y, int touchId, ofxMultiTouchCustomData *data = 0) {
		for(std::list<ofxMultiTouchListener*>::iterator it=listeners.begin(); it!=listeners.end(); ++it) {
			ofxMultiTouchListener* o = *it;
			o->touchMoved(x, y, touchId, data);
		}
	}
	
	// multitouch engine should call this when an 'up' is detected
	// use ofxMultiTouchCustomData *data to send any platform specific data
	void touchUp(int x, int y, int touchId, ofxMultiTouchCustomData *data = 0) {
		for(std::list<ofxMultiTouchListener*>::iterator it=listeners.begin(); it!=listeners.end(); ++it) {
			ofxMultiTouchListener* o = *it;
			o->touchUp(x, y, touchId, data);
		}
	}
	
	// multitouch engine should call this when a 'double tap' is detected
	// use ofxMultiTouchCustomData *data to send any platform specific data	
	void touchDoubleTap(int x, int y, int touchId, ofxMultiTouchCustomData *data = 0) {
		for(std::list<ofxMultiTouchListener*>::iterator it=listeners.begin(); it!=listeners.end(); ++it) {
			ofxMultiTouchListener* o = *it;
			o->touchDoubleTap(x, y, touchId, data);
		}
	}

	
protected:
	std::list<ofxMultiTouchListener*> listeners;
	
};

extern ofxMultiTouchHandler ofxMultiTouch;

