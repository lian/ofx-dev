/* 
 * Copyright (c) 2009, Rui Madeira
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */



#pragma once

#include "core/ofxParticle.h"
#include "core/ofxConstraint.h"
#include "core/ofxSpring.h"
#include "core/ofxMaxDistSpring.h"
#include "core/ofxMinDistSpring.h"
#include "core/ofxInequalityConstraint.h"
#include "core/ofxSupportConstraint.h"
#include "core/ofxFollowerConstraint.h"
#include "core/ofxCollisionConstraint.h"

class ofxPhysics2d{
protected:
	vector<ofxParticle*>particles;
	vector<ofxConstraint*>constraints;
	ofxCollisionConstraint*collisionSolver;
	ofxVec2f gravity;
	void boundsConstrain();
	bool bCollisions;
	bool bCheckBounds;
	ofxVec2f worldMin, worldMax;
	int numIterations;
public:
	
	ofxPhysics2d(ofxVec2f _grav = ofxVec2f(), 
				 bool _bCollisions = false, 
				 int _numIterations = 10,
				 ofxVec2f _worldMin = ofxVec2f(), 
				 ofxVec2f _worldMax = ofxVec2f(ofGetWidth(), ofGetHeight()),
				 bool _bCheckBounds = true);
	~ofxPhysics2d();
	
	void update(float timeStep = 1.0f);
	void renderParticles();
	void renderConstraints();
	void render();
	void addParticle(ofxParticle *_p, bool _addToCollisions = false);
	void deleteParticle(uint _i);
	void deleteParticle(ofxParticle*_p);
	void addConstraint(ofxConstraint*_c);
	void add(ofxParticle*p);
	void add(ofxParticle*p, bool _enableCollisions);
	void add(ofxConstraint*c);
	void deleteConstraint(uint _i);
	void deleteConstraint(ofxConstraint*_c);
	ofxParticle* getParticle(uint _i);
	ofxConstraint* getConstraint(uint _i);
	bool hasParticle(ofxParticle*p);
	bool hasConstraint(ofxConstraint*c);
	bool has(ofxParticle* p);
	bool has(ofxConstraint* c);
	void setNumIterations(uint _n);
	int getNumIterations();
	void enableCollisions(bool _bEnable);
	bool collisionsEnabled();
	void checkBounds(bool _bCheck);
	bool boundsCheck();
	void enableCollisionsForParticle(uint _i, bool _bEnable);
	void removeConstraintsWithParticle(ofxParticle *p);
	void deleteConstraintsWithParticle(ofxParticle *p);
	bool hasConstraintsWithParticle(ofxParticle*p);
	ofxConstraint* getConstraintWithParticle(ofxParticle*p);
	ofxParticle* getNearestParticle(ofxVec2f point);
	ofxParticle* getParticleUnderPoint(ofPoint& point);
	int getNumParticles();
	int getNumConstraints();
	vector<ofxParticle*>& getParticles();
	vector<ofxConstraint*>& getConstraints();
	ofxVec2f& getGravity();
	void setGravity(ofxVec2f _gravity);
	
	void removeAllParticles();
	void deleteAllParticles();
	void removeAllConstraints();
	void deleteAllConstraints();
	void removeAll();
	void deleteAll();
	void reserveForParticles(int numberOfParticles);
	void reserveForConstraints(int numberOfConstraints);
};

