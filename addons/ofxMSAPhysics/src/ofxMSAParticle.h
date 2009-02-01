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
#include "ofxObjCPointer.h"

#include "ofxMSAPhysicsParams.h"

class ofxMSAParticle : public ofxVec3f, public ofxObjCPointer {
public:	
	friend class ofxMSASpring;
	friend class ofxMSAPhysics;
	
	ofxMSAParticle(float x = 0, float y = 0, float z = 0, float m = 1.0f, float d = 1.0f);	
	ofxMSAParticle(ofxVec3f &v, float m = 1.0f, float d = 1.0f);	
	ofxMSAParticle(ofxMSAParticle &p);	

	virtual void init(float x, float y, float z, float m = 1.0f, float d = 1.0f);	
	void setParams(ofxMSAPhysicsParams *params);
	
	void setMass(float m);	
	float getMass();
	float getInvMass();

	void setDrag(float d);		// NEW
	float getDrag();			// NEW
	
	bool isFixed();
	bool isFree();
	void makeFixed();
	void makeFree();
   
	void moveTo(ofxVec3f &targetPos);	
    void moveBy(ofxVec3f &diffPos);    
    void moveTo(float x, float y, float z);	
    void moveBy(float x, float y, float z);    
	
    void setVelocity(ofxVec3f vel);    
    void setVelocity(float x, float y, float z);    
    void addVelocity(ofxVec3f &vel);    
    void addVelocity(float x, float y, float z);	
	ofxVec3f getVelocity();

	// override these functions
	virtual void update() {}
	virtual void draw() {}

	// NEW
	void kill();
	bool isDead();
	
	ofxMSAPhysicsParams *params;

	
protected:
	ofxVec3f			_oldPos;
	float				_mass, _invMass;
	float				_age;
	float				_drag;
	bool				_isDead;
	bool				_isFixed;
	
	void doVerlet();
	
	virtual void debugDraw();
};

