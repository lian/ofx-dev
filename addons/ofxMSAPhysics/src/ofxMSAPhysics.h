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

/* based on
 
 http://www.gamasutra.com/resource_guide/20030121/jacobson_01.shtml
 
 */

#pragma once

#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXOBJCPOINTER
#define OF_ADDON_USING_OFMSADATARECORDER
#include "ofMain.h"
#include "ofAddons.h"

#include <vector>

#include "ofxMSAParticle.h"
#include "ofxMSAConstraint.h"
#include "ofxMSASpring.h"
#include "ofxMSAPhysicsParams.h"
#include "ofxMSAPhysicsCallbacks.h"


class ofxMSAPhysics : public ofxMSAParticleUpdatable {
	
public:	
	friend class ofxMSAParticle;
	
	ofxMSAPhysics();
	~ofxMSAPhysics();
	
	ofxMSAParticle*		makeParticle(float x, float y, float z, float m = 1.0f, float d = 1.0f);
	ofxMSASpring*		makeSpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength);
	
	ofxMSAParticle*		addParticle(ofxMSAParticle *p);
	ofxMSAConstraint*	addConstraint(ofxMSAConstraint *s);
	
	ofxMSAParticle*		getParticle(int i);
	ofxMSAConstraint*	getSpring(int i);
	
	void setDrag(float drag = 0.99);					// set the drag. 1: no drag at all, 0.9: quite a lot of drag, 0: particles can't even move
	void setGravity(float gy);							// set gravity 
	void setGravity(float gx = 0, float gy = 0, float gz = 0);		// default values
	void setGravity(ofxVec3f &g);						// NEW
	ofxVec3f& getGravity();

	void setTimeStep(float timeStep);
	void setNumIterations(float numIterations = 20);	// default value
	
	int numberOfParticles();
	int numberOfSprings();

	void update(int frameNum = -1);						// NEW
	void draw();										// NEW
	void debugDraw();									// NEW
	void clear();
	
	void setParticleCount(int i);						// preallocate buffer for particles if known (can grow if needed)
	void setConstraintCount(int i);						// preallocate buffer for constraints if known (can grow if needed)

	void setReplayMode(int i, float playbackScaler = 1.0f);		// when playing back recorded data, optionally scale positions up (so you can record in lores, playback at highres)
	void setReplayFilename(string f);
	
protected:
	vector<ofxMSAParticle*>		_particles;
	vector<ofxMSAConstraint*>	_constraints;
	
	ofxMSADataRecorder<ofxVec3f>_recorder;
	
	int							_numIterations;
	int							_frameCounter;
	int							_replayMode;
	float						_playbackScaler;
	ofxMSAPhysicsParams			params;

	void updateConstraints();
	void updateParticles();
	void load(int frameNum);
	
	ofxMSAConstraint *getConstraint(ofxVec3f *a, ofxVec3f *b);
	ofxMSAConstraint *getConstraint(ofxVec3f *a);
};
