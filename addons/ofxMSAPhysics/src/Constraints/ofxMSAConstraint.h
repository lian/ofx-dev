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
#include "ofxObjCPointer.h"

#include "ofxMSAPhysicsUtils.h"
#include "ofxMSAParticle.h"
#include "ofxMSAConstraintTypes.h"

class ofxMSAConstraint : public ofxObjCPointer {
public:	
	friend class ofxMSAPhysics;
	
	ofxMSAConstraint() {
		_isOn = true;
		_type = -1;
		_isDead = false;
		verbose = true;
		_params = NULL;

		setClassName("ofxMSAConstraint");
	}
	
	virtual ~ofxMSAConstraint() {
		_a->release();
		_b->release(); 		
	}
	
	inline int type() {
		return _type;
	}
	
	inline ofxMSAParticle* getOneEnd() {
		return _a;
	}
	
	inline ofxMSAParticle* getTheOtherEnd() {
		return _b;
	}
	
	inline ofxMSAParticle* getA() {
		return _a;
	}
	
	inline ofxMSAParticle* getB() {
		return _b;
	}
	
	inline void turnOff() {
		_isOn = false;
	}
	
	inline void turnOn() {
		_isOn = true;
	}
	
	inline bool isOn() {
		return (_isOn == true);
	}
	
	inline bool isOff(){
		return (_isOn == false);
	}
	
	inline void kill() {
		_isDead = true;
	}

	inline bool isDead() {
		return _isDead;
	}
	
	// only worth solving the constraint if its on, and at least one end is free
	inline bool shouldSolve() {
		return _isOn && (_a->isFree() || _b->isFree());
	}
	
	virtual void update() {}
	virtual void draw() {}
	

	
protected:	
	int				_type;
	bool			_isOn;
	bool			_isDead;
	ofxMSAParticle	*_a, *_b;
	ofxMSAPhysicsParams *_params;	
	virtual void solve() = 0;
	
	virtual void debugDraw() {
		ofPoint vec = (*_b - *_a);
		float dist = msaLength(vec);
		float angle = acos( vec.z / dist ) * RAD_TO_DEG;
		if(vec.z <= 0 ) angle = -angle;
		float rx = -vec.y * vec.z;
		float ry =  vec.x * vec.z;
		
		glPushMatrix();
		glTranslatef(_a->x, _a->y, _a->z);
		glRotatef(angle, rx, ry, 0.0);
		glScalef(1, 1, dist);
		glTranslatef(0, 0, 0.5);
#ifndef TARGET_OF_IPHONE		
		glutSolidCube(1);
#endif		
		glPopMatrix();
	}
};



