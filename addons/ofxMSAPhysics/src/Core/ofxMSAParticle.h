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

#include "ofxMSAPhysicsParams.h"

class ofxMSAParticle : public ofPoint, public ofxObjCPointer {
public:	
	friend class ofxMSAPhysics;
	
	ofxMSAParticle(float x = 0, float y = 0, float z = 0, float mass = 1.0f, float drag = 1.0f);	
	ofxMSAParticle(ofPoint &v, float m = 1.0f, float d = 1.0f);	
	ofxMSAParticle(ofxMSAParticle &p);	

	virtual void	init(float x, float y, float z, float m = 1.0f, float d = 1.0f);	
	
	ofxMSAParticle* setMass(float t = 1);
	float			getMass();
	float			getInvMass();

	ofxMSAParticle* setDrag(float t = 1);
	float			getDrag();
	
	ofxMSAParticle* setBounce(float t = 1);
	float			getBounce();
	
	ofxMSAParticle* setRadius(float t = 15);
	float			getRadius();
	
	// even with collision disabled you can still create your own collision constraint between two particles
	ofxMSAParticle* enableCollision();
	ofxMSAParticle* disableCollision();
	bool			hasCollision();
	
	bool			isFixed();
	bool			isFree();
	ofxMSAParticle* makeFixed();
	ofxMSAParticle* makeFree();
   
	ofxMSAParticle* moveTo(ofPoint &targetPos);	
    ofxMSAParticle* moveBy(ofPoint &diffPos);    
    ofxMSAParticle* moveTo(float x, float y, float z);	
    ofxMSAParticle* moveBy(float x, float y, float z);    
	
    ofxMSAParticle* setVelocity(ofPoint &vel);    
    ofxMSAParticle* setVelocity(float x, float y, float z);    
    ofxMSAParticle* addVelocity(ofPoint &vel);    
    ofxMSAParticle* addVelocity(float x, float y, float z);	
	ofPoint&		getVelocity();

	// override these functions if you create your own particle type with custom behaviour and/or drawing
	virtual void	update() {}
	virtual void	draw() {}

	void			kill();
	bool			isDead();
	
	bool			isInSameBinAs(ofxMSAParticle* p);
	
protected:
	ofxMSAPhysicsParams *_params;
	ofxMSAPhysics		*_physics;
	
	
	ofPoint			_oldPos, _vel;
	float			_mass, _invMass;
	float			_drag;
	float			_bounce;
	float			_radius;
	float			_age;
	bool			_isDead;
	bool			_isFixed;
	bool			_globalCollisionEnabled;
	unsigned int	_xBinFlags, _yBinFlags, _zBinFlags;
	
	void			computeBinFlags();
	void			doVerlet();
	void			checkWorldEdges();
	
	virtual void debugDraw();
};

