/*
	TUIO C++ Library for OpenFrameworks
    http://www.openframeworks.cc
	
	Copyright (c) 2008 by Matthias Dörfelt based on the Classes by Martin Kaltenbrunner
	which can be found at http://reactivision.sourceforge.net/
	
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _TUIO_CURSOR
#define _TUIO_CURSOR

#include "ofxTuioContainer.h"

//--------------------------------------------------------
class ofxTuioCursor : public ofxTuioContainer{
	
public:
	
	ofxTuioCursor(long _sid, int _fid, float _xpos, float _ypos) : ofxTuioContainer( _sid,  _xpos,  _ypos){
		fingerId = _fid;
	};
	
	ofxTuioCursor(ofxTuioCursor * _tuioCursor) : ofxTuioContainer(_tuioCursor){
		fingerId = _tuioCursor->getFingerId();
	};
	
	~ofxTuioCursor(){};
	
	int getFingerId(){
		return fingerId;
	};
	
protected:
	int fingerId;
};

#endif	
