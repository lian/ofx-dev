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

#ifndef _TUIO_OBJECT
#define _TUIO_OBJECT

#include "ofxTuioContainer.h"

//--------------------------------------------------------
class ofxTuioObject : public ofxTuioContainer{
	
public:
	
	ofxTuioObject(long _sid, int _fid, float _xpos, float _ypos, float _angle) : ofxTuioContainer( _sid,  _xpos,  _ypos){
        fiducialId = _fid;
	    angle = _angle;
		rotation_speed = 0.0f;
		rotation_accel = 0.0f;
		
	};
	
	ofxTuioObject(ofxTuioObject * _tuioObject) : ofxTuioContainer(_tuioObject){
        fiducialId = _tuioObject->getFiducialId();
	    angle = _tuioObject->getAngle();
		rotation_speed = _tuioObject->getRotationSpeed();
		rotation_accel = _tuioObject->getRotationAccel();
	};
	
	~ofxTuioObject(){};
	
	void update (float _xpos, float _ypos, float _angle, float _xspeed, float _yspeed, float _rspeed, float _maccel, float _raccel) {
		ofxTuioContainer::update(_xpos,_ypos,_xspeed,_yspeed,_maccel);
		angle = _angle;
		rotation_speed = _rspeed;
		rotation_accel = _raccel;
	};
	
	void update (ofxTuioObject * _tuioObject) {
		ofxTuioContainer::update(_tuioObject);
		angle = _tuioObject->getAngle();
		rotation_speed = _tuioObject->getRotationSpeed();
		rotation_accel = _tuioObject->getRotationAccel();
	};
	
	int getFiducialId() { 
		return fiducialId; 
	};
	
	float getAngle() { 
		return angle; 
	};
	
	float getAngleDegrees() { 
		return (float)(angle/PI*180); 
	};
	
	float getRotationSpeed() { 
		return rotation_speed; 
	};
	
	float getRotationAccel() { 
		return rotation_accel; 
	};
	
	
protected:
	int fiducialId;
	float angle;
	float rotation_speed, rotation_accel;
};

#endif	
