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

#include "ofMain.h"


class ofxMSAInteractiveObject : public ofRectangle {
public:
	bool		enabled;				// set this to false to temporarily disable all events
	bool		verbose;
	
	ofxMSAInteractiveObject();			// constructor
	virtual ~ofxMSAInteractiveObject();	// destructor
	
	void enableAllEvents();				// enable all event callbacks
	void disableAllEvents();			// disable all event callbacks
	
	void enableMouseEvents();			// call this if object should receive mouse events
	void disableMouseEvents();			// call this if object doesn't need to receive mouse events (default)
	
	void enableKeyEvents();				// call this if object should receive key events
	void disableKeyEvents();			// call this if object doesn't need to receive key events (default)
	
	void enableAppEvents();				// call this if object should update/draw automatically	(default)
	void disableAppEvents();			// call this if object doesn't need to update/draw automatically
	
	void setPos(float _x, float _y);	// set position of object
	void setSize(float _w, float _h);	// set size of object
	
	void setPosAndSize(float _x, float _y, float _w, float _h);		// set pos and size
	
	bool isMouseOver();					// returns true if mouse is over object (based on position and size)
	bool isMouseDown();					// returns true if mouse button is down and over object (based on position and size)
	int	 getMouseX();					// returns mouse X (in screen coordinates)
	int  getMouseY();					// returns mouse Y (in screen coordinates)
	int  getLastMouseButton();			// returns last mouse button to have activity
	
	bool hitTest(int tx, int ty);		// returns true if given (x, y) coordinates (in screen space) are over the object (based on position and size)
	
	void killMe();						// if your object is a pointer, and you are done with it, call this


	// extend ofxMSAInteractiveObject and override all of any of the following methods
	virtual void setup()	{}	// called when app starts
	virtual void update()	{}	// called every frame to update object
    virtual void draw()		{}	// called every frame to draw object
	virtual void exit()		{}	// called when app quites
	
	// these behave very similar to those in flash
	virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
	virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
	virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
	virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down
	virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
	virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
	virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
	virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object
	
	virtual void keyPressed( int key ){}
	virtual void keyReleased( int key ){}
	
	
	// you shouldn't need access to any of these unless you know what you are doing
	// (i.e. disable auto updates and call these manually)
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
    void _draw(ofEventArgs &e);
	void _exit(ofEventArgs &e);
	
	void _mouseMoved(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);	
	void _mouseDragged(ofMouseEventArgs &e);	
	void _mouseReleased(ofMouseEventArgs &e);
	
	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);
	
	
protected:
	int			_mouseX, _mouseY, _mouseButton;
	bool		_mouseOver;
	bool		_mouseDown;
	ofRectangle	oldRect;
};