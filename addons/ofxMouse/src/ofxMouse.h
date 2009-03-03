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

#define MAX_MOUSE_BUTTONS	10

#define OF_ADDON_USING_OFXVECTORMATH
#include "ofMain.h"
#include "ofAddons.h"

#include <string>

class ofxMouse : public ofMouseListener, public ofAppListener, public ofxVec3f {
public:
	ofxVec2f prev;
	ofxVec2f vel;
//	ofxVec2f norm;
	
	static ofxMouse *get();
	bool isButtonDown(int b);
	string toString();	

	void update();
	void draw();
	
	void mouseMoved( int _x, int _y );	
	void mouseDragged( int _x, int _y, int _button );	
	void mousePressed( int _x, int _y, int _button );	
	void mouseReleased();
	void mouseReleased(int _x, int _y, int _button );	

protected:
	
	bool				button[MAX_MOUSE_BUTTONS];	// is the nth button down
	bool				isFirstMove;
	ofxMouse();

	
private:
	static ofxMouse		*_thisInstance;
};


