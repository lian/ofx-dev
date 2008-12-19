/***********************************************************************
 
 Copyright (c) 2008, Memo Akten, www.memo.tv
 
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

#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXOBJCPOINTER
#include "ofMain.h"
#include "ofAddons.h"

#include "ofxMSAParticle.h"
#include "ofxMSAConstraintTypes.h"

class ofxMSAConstraint : public ofxObjCPointer {
public:	
	friend class ofxMSAPhysics;
	
	ofxMSAConstraint() {
		_isOn = true;
		_type = -1;
		_isDead = false;
		setClassName("ofxMSAConstraint");
	}
	
	virtual ~ofxMSAConstraint() {
		_a->release();
		_b->release(); 		
	}
	
	int type() {
		return _type;
	}
	
	ofxMSAParticle* getOneEnd() {
		return _a;
	}
	
	ofxMSAParticle* getTheOtherEnd() {
		return _b;
	}
	
	ofxMSAParticle* getA() {
		return _a;
	}
	
	ofxMSAParticle* getB() {
		return _b;
	}
	
	void turnOff() {
		_isOn = false;
	}
	
	void turnOn() {
		_isOn = true;
	}
	
	bool isOn() {
		return (_isOn == true);
	}
	
	bool isOff(){
		return (_isOn == false);
	}
	
	// NEW
	void kill() {
		_isDead = true;
	}

	bool isDead() {
		return _isDead;
	}
	
	virtual void update() {}
	virtual void draw() {}
	
protected:	
	int				_type;
	bool			_isOn;
	bool			_isDead;
	ofxMSAParticle	*_a, *_b;
	
	virtual void solve() = 0;
	
	virtual void debugDraw() {
		ofxVec3f vec = (*_b - *_a);
		float dist = vec.length();
		float angle = acos( vec.z / dist ) * RAD_TO_DEG;
		if(vec.z <= 0 ) angle = -angle;
		float rx = -vec.y * vec.z;
		float ry =  vec.x * vec.z;
		
		glPushMatrix();
		glTranslatef(_a->x, _a->y, _a->z);
		glRotatef(angle, rx, ry, 0.0);
		glScalef(1, 1, dist);
		glTranslatef(0, 0, 0.5);
		glutSolidCube(1);
		glPopMatrix();
	}
};



