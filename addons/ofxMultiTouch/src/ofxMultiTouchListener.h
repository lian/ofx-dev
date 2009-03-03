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

// contains custom data which specific implementations can override and add to
struct ofxMultiTouchCustomData {
	int numTouches;
};


/****** protocol, delegate, interface, whatever you want to call it ******/
class ofxMultiTouchListener {
public:
	virtual ~ofxMultiTouchListener() {}				
	
	virtual void touchDown(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL)			= 0;
	virtual void touchMoved(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL)		= 0;
	virtual void touchUp(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL)			= 0;
	virtual void touchDoubleTap(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL)	= 0;
};