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

/* 
 based on principles mentioned at
  http://www.gamasutra.com/resource_guide/20030121/jacobson_01.shtml
 
 
fast inverse square root mentioned at
 http://en.wikipedia.org/wiki/Fast_inverse_square_root
 attributed to John Carmack but apparently much older
 */

#pragma once

//#define MSAPHYSICS_USE_RECORDER

#include "ofMain.h"

#include "ofxObjCPointer.h"

#include "ofxMSAParticle.h"
#include "ofxMSAConstraint.h"
#include "ofxMSASpring.h"
#include "ofxMSAAttraction.h"
#include "ofxMSACollision.h"

#include "ofxMSAPhysicsUtils.h"
#include "ofxMSAPhysicsParams.h"
#include "ofxMSAPhysicsCallbacks.h"

#ifdef MSAPHYSICS_USE_RECORDER
#include "ofxMSADataRecorder.h"
#endif



class ofxMSAPhysics : public ofxMSAParticleUpdatable {
	
public:	
	friend class ofxMSAParticle;
	
	bool				verbose;
	
	ofxMSAPhysics();
	~ofxMSAPhysics();
	
	ofxMSAParticle*		makeParticle(float x, float y, float z, float m = 1.0f, float d = 1.0f);
	ofxMSASpring*		makeSpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength);
	ofxMSAAttraction*	makeAttraction(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _minimumDistance = 0);
	ofxMSACollision*	makeCollision(ofxMSAParticle *a, ofxMSAParticle *b);
	
	// this method retains the particle, so you should release() it after adding (obj-c style)
	ofxMSAParticle*		addParticle(ofxMSAParticle *p);
	
	// this method retains the constraint, so you should release it after adding (obj-c style)
	ofxMSAConstraint*	addConstraint(ofxMSAConstraint *c);
	
	ofxMSAParticle*		getParticle(uint i);
	ofxMSAConstraint*	getConstraint(uint i);			// generally you wouldn't use this but use the ones below
	ofxMSASpring*		getSpring(uint i);
	ofxMSAAttraction*	getAttraction(uint i);
	ofxMSACollision*	getCollision(uint i);
	
	uint				numberOfParticles();
	uint				numberOfConstraints();		// all constraints: springs, attractions, collisions and user created
	uint				numberOfSprings();			// only springs
	uint				numberOfAttractions();		// only attractions
	uint				numberOfCollisions();		// only collisions
	
	ofxMSAPhysics*		enableCollision();
	ofxMSAPhysics*		disableCollision();
	bool				isCollisionEnabled();
	
	ofxMSAPhysics*		addToCollision(ofxMSAParticle* p);
	ofxMSAPhysics*		removeFromCollision(ofxMSAParticle* p);
	
	ofxMSAPhysics*		setDrag(float drag = 0.99);					// set the drag. 1: no drag at all, 0.9: quite a lot of drag, 0: particles can't even move
	ofxMSAPhysics*		setGravity(float gy);							// set gravity 
	ofxMSAPhysics*		setGravity(float gx = 0, float gy = 0, float gz = 0);		// default values
	ofxMSAPhysics*		setGravity(ofPoint &g);
	ofPoint&			getGravity();
	ofxMSAPhysics*		setTimeStep(float timeStep);
	ofxMSAPhysics*		setNumIterations(float numIterations = 20);	// default value
	
	ofxMSAPhysics*		setWorldMin(ofPoint worldMin);
	ofxMSAPhysics*		setWorldMax(ofPoint worldMax);
	ofxMSAPhysics*		setWorldSize(ofPoint worldMin, ofPoint worldMax);
	ofxMSAPhysics*		clearWorldSize();
	
	// preallocate buffers if you know how big they need to be (they grow automatically if need be)
	ofxMSAPhysics*		setParticleCount(uint i);
	ofxMSAPhysics*		setConstraintCount(uint i);
	ofxMSAPhysics*		setSpringCount(uint i);
	ofxMSAPhysics*		setAttractionCount(uint i);
	ofxMSAPhysics*		setCollisionCount(uint i);					

	
	void clear();
	void update(int frameNum = -1);	
	void draw();
	void debugDraw();

#ifdef MSAPHYSICS_USE_RECORDER
	ofxMSAPhysics*		setReplayMode(int i, float playbackScaler = 1.0f);		// when playing back recorded data, optionally scale positions up (so you can record in lores, playback at highres)
	ofxMSAPhysics*		setReplayFilename(string f);
#endif	
	
protected:
	vector<ofxMSAParticle*>		_particles;
	vector<ofxMSAConstraint*>	_constraints[OFX_MSA_CONSTRAINT_TYPE_COUNT];
	
	ofxMSAPhysicsParams			params;

	void						updateParticles();
	void						updateAllConstraints();
	void						updateConstraintsByType(vector<ofxMSAConstraint*> constraints);

	ofxMSAConstraint*			getConstraint(ofxMSAParticle *a, int constraintType);
	ofxMSAConstraint*			getConstraint(ofxMSAParticle *a, ofxMSAParticle *b, int constraintType);

	
#ifdef MSAPHYSICS_USE_RECORDER
	ofxMSADataRecorder<ofPoint>_recorder;
	uint						_frameCounter;
	uint						_replayMode;
	float						_playbackScaler;
	void load(uint frameNum);
#endif
};
