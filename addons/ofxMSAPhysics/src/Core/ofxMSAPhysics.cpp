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

#include "ofxMSAPhysics.h"
#include "binner.h"

ofxMSAPhysics::ofxMSAPhysics() {
	verbose = false;
	setTimeStep(0.000010);
	setDrag();
	setNumIterations();
	enableCollision();
	setGravity();
	clearWorldSize();
	
#ifdef MSAPHYSICS_USE_RECORDER
	_frameCounter = 0;
	setReplayMode(OFX_MSA_DATA_IDLE);
	setReplayFilename("recordedData/physics/physics");
#endif	
}

ofxMSAPhysics::~ofxMSAPhysics() {
	clear();
}



ofxMSAParticle* ofxMSAPhysics::makeParticle(float x, float y, float z, float m, float d) {
	ofxMSAParticle *p = new ofxMSAParticle(x, y, z, m, d);
	addParticle(p);
	p->release();	// cos addParticle(p) retains it
	return p;
}

ofxMSASpring* ofxMSAPhysics::makeSpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength) {
	if(a==b) return NULL;
	ofxMSASpring* c = new ofxMSASpring(a, b, _strength, _restLength);
	addConstraint(c);
	c->release();	// cos addConstraint(c) retains it
	return c;
}

ofxMSAAttraction* ofxMSAPhysics::makeAttraction(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _minimumDistance) {
	if(a==b) return NULL;
	ofxMSAAttraction* c = new ofxMSAAttraction(a, b, _strength, _minimumDistance);
	addConstraint(c);
	c->release();	// cos addConstraint(c) retains it
	return c;
}

ofxMSACollision* ofxMSAPhysics::makeCollision(ofxMSAParticle *a, ofxMSAParticle *b) {
	if(a==b) return NULL;
	if(getConstraint(a, b, OFX_MSA_CONSTRAINT_TYPE_COLLISION) != NULL) return NULL;	
	ofxMSACollision* c = new ofxMSACollision(a, b);
	addConstraint(c);
	c->release();	// cos addConstraint(c) retains it
	return c;
}




ofxMSAParticle* ofxMSAPhysics::addParticle(ofxMSAParticle *p) {
	p->verbose = verbose;
	_particles.push_back(p);
	p->setInstanceName(string("particle ") + ofToString(_particles.size(), 0));
	p->_params = &params;
	p->_physics = this;

#ifdef MSAPHYSICS_USE_RECORDER
	if(_replayMode == OFX_MSA_DATA_SAVE)
		_recorder.setSize(numberOfParticles());
#endif
	p->retain();
	return p;		// so you can configure the particle or use for creating constraints
}

ofxMSAConstraint* ofxMSAPhysics::addConstraint(ofxMSAConstraint *c) {
	c->verbose = verbose;	
	_constraints[c->type()].push_back(c);
	c->_params = &params;
	
	c->retain();
	(c->_a)->retain();
	(c->_b)->retain();
	
	switch(c->type()) {
		case OFX_MSA_CONSTRAINT_TYPE_CUSTOM:
			c->setInstanceName(string("constraint ") + ofToString(_constraints[OFX_MSA_CONSTRAINT_TYPE_CUSTOM].size(), 0));
			break;

		case OFX_MSA_CONSTRAINT_TYPE_SPRING:
			c->setInstanceName(string("spring ") + ofToString(_constraints[OFX_MSA_CONSTRAINT_TYPE_SPRING].size(), 0));
			break;
			
		case OFX_MSA_CONSTRAINT_TYPE_ATTRACTION:
			c->setInstanceName(string("attraction ") + ofToString(_constraints[OFX_MSA_CONSTRAINT_TYPE_ATTRACTION].size(), 0));
			break;
			
		case OFX_MSA_CONSTRAINT_TYPE_COLLISION:
			c->setInstanceName(string("collision ") + ofToString(_constraints[OFX_MSA_CONSTRAINT_TYPE_COLLISION].size(), 0));
			break;
	}
	
	return c;
}


ofxMSAParticle*		ofxMSAPhysics::getParticle(uint i) {
	return i < numberOfParticles() ? _particles[i] : NULL;
}

ofxMSAConstraint*	ofxMSAPhysics::getConstraint(uint i) {
	return i < numberOfConstraints() ? _constraints[OFX_MSA_CONSTRAINT_TYPE_CUSTOM][i] : NULL;
}

ofxMSASpring*		ofxMSAPhysics::getSpring(uint i) {
	return i < numberOfSprings() ? (ofxMSASpring*)_constraints[OFX_MSA_CONSTRAINT_TYPE_SPRING][i] : NULL;
}

ofxMSAAttraction*	ofxMSAPhysics::getAttraction(uint i) {
	return i < numberOfAttractions() ? (ofxMSAAttraction*)_constraints[OFX_MSA_CONSTRAINT_TYPE_ATTRACTION][i] : NULL;
}

ofxMSACollision*	ofxMSAPhysics::getCollision(uint i) {
	return i < numberOfCollisions() ? (ofxMSACollision*)_constraints[OFX_MSA_CONSTRAINT_TYPE_COLLISION][i] : NULL;
}



uint ofxMSAPhysics::numberOfParticles() {
	return _particles.size();
}

uint ofxMSAPhysics::numberOfConstraints() {
	return _constraints[OFX_MSA_CONSTRAINT_TYPE_CUSTOM].size();
}

uint ofxMSAPhysics::numberOfSprings() {
	return _constraints[OFX_MSA_CONSTRAINT_TYPE_SPRING].size();
}

uint ofxMSAPhysics::numberOfAttractions() {
	return _constraints[OFX_MSA_CONSTRAINT_TYPE_ATTRACTION].size();
}


uint ofxMSAPhysics::numberOfCollisions() {
	return _constraints[OFX_MSA_CONSTRAINT_TYPE_COLLISION].size();
}


ofxMSAPhysics* ofxMSAPhysics::enableCollision() {
	params.isCollisionEnabled = true;
	return this;
}


ofxMSAPhysics* ofxMSAPhysics::disableCollision() {
	params.isCollisionEnabled = false;
	return this;
}

bool ofxMSAPhysics::isCollisionEnabled() {
	return params.isCollisionEnabled;
}


ofxMSAPhysics* ofxMSAPhysics::addToCollision(ofxMSAParticle* p) {
	for(int i=0; i< numberOfParticles(); i++) {
		ofxMSAParticle *target = getParticle(i);
		if(target->hasCollision()) makeCollision(target, p);
	}
	return this;
}


ofxMSAPhysics* ofxMSAPhysics::removeFromCollision(ofxMSAParticle* p) {
	for(int i=0; i<numberOfCollisions(); i++) {
		ofxMSAConstraint *c = getCollision(i);
		if(c->_a == p || c->_b == p) c->kill();
	}
	return this;
}



ofxMSAPhysics*  ofxMSAPhysics::setDrag(float drag) {
	params.drag = drag;
	return this;	
}

ofxMSAPhysics*  ofxMSAPhysics::setGravity(float gy) {
	setGravity(0, gy, 0);
	return this;	
}

ofxMSAPhysics*  ofxMSAPhysics::setGravity(ofPoint &g) {
	params.gravity= g;
	params.doGravity = msaLengthSquared(params.gravity) > 0;
	return this;	
}

ofxMSAPhysics*  ofxMSAPhysics::setGravity(float gx, float gy, float gz) {
	params.gravity.set(gx, gy, gz);
	params.doGravity = msaLengthSquared(params.gravity) > 0;
	return this;	
}

ofPoint& ofxMSAPhysics::getGravity() {
	return params.gravity;
}

ofxMSAPhysics*  ofxMSAPhysics::setTimeStep(float timeStep) {
	params.timeStep = timeStep;
	params.timeStep2 = timeStep * timeStep;
	return this;	
}

ofxMSAPhysics*  ofxMSAPhysics::setNumIterations(float numIterations) {
	params.numIterations = numIterations;
	return this;	
}


ofxMSAPhysics* ofxMSAPhysics::setWorldMin(ofPoint worldMin) {
	params.worldMin = worldMin;
	params.doWorldEdges = true;
	ofPoint worldSize = params.worldMax - params.worldMin;
	setupBins(worldSize.x, worldSize.y, worldSize.z, 5, 5, 5);	// TODO: sort this out
	return this;	
}

ofxMSAPhysics* ofxMSAPhysics::setWorldMax(ofPoint worldMax) {
	params.worldMax = worldMax;
	params.doWorldEdges = true;
	return this;	
}

ofxMSAPhysics* ofxMSAPhysics::setWorldSize(ofPoint worldMin, ofPoint worldMax) {
	setWorldMin(worldMin);
	setWorldMax(worldMax);
	return this;	
}

ofxMSAPhysics* ofxMSAPhysics::clearWorldSize() {
	params.doWorldEdges = false;
	return this;	
}



ofxMSAPhysics*  ofxMSAPhysics::setParticleCount(uint i) {
	_particles.reserve(i);
#ifdef MSAPHYSICS_USE_RECORDER
	//	if(_replayMode == OFX_MSA_DATA_SAVE)
	_recorder.setSize(i);
#endif
	return this;	
}


ofxMSAPhysics* ofxMSAPhysics::setConstraintCount(uint i){
	_constraints[OFX_MSA_CONSTRAINT_TYPE_CUSTOM].reserve(i);
	return this;
}

ofxMSAPhysics* ofxMSAPhysics::setSpringCount(uint i){
	_constraints[OFX_MSA_CONSTRAINT_TYPE_SPRING].reserve(i);
	return this;
}

ofxMSAPhysics* ofxMSAPhysics::setAttractionCount(uint i){
	_constraints[OFX_MSA_CONSTRAINT_TYPE_ATTRACTION].reserve(i);
	return this;
}

ofxMSAPhysics* ofxMSAPhysics::setCollisionCount(uint i){
	_constraints[OFX_MSA_CONSTRAINT_TYPE_COLLISION].reserve(i);
	return this;
}


void ofxMSAPhysics::clear() {
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->release();
	}
	_particles.clear();
	
	
	for(int i=0; i<OFX_MSA_CONSTRAINT_TYPE_COUNT; i++) {
		for (vector<ofxMSAConstraint*>::iterator it = _constraints[i].begin(); it != _constraints[i].end(); it++) {
			ofxMSAConstraint* constraint = *it;
			constraint->release();
		}
		_constraints[i].clear();
	}
}





void ofxMSAPhysics::update(int frameNum) {
#ifdef MSAPHYSICS_USE_RECORDER
	if(frameNum < 0) frameNum = _frameCounter;
	if(_replayMode == OFX_MSA_DATA_LOAD) {
		load(frameNum);
	} else {
		updateParticles();
		updateAllConstraints();
		if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.save(frameNum);
	}
	_frameCounter++;
#else
	updateParticles();
	updateAllConstraints();
#endif
}


void ofxMSAPhysics::draw() {
	for(int i=0; i<OFX_MSA_CONSTRAINT_TYPE_COUNT; i++) {
		for (vector<ofxMSAConstraint*>::iterator it = _constraints[i].begin(); it != _constraints[i].end(); it++) {
			ofxMSAConstraint* constraint = *it;
			constraint->draw();
		}
	}
	
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->draw();
	}
}

void ofxMSAPhysics::debugDraw() {
	for(int i=0; i<OFX_MSA_CONSTRAINT_TYPE_COUNT; i++) {
		for (vector<ofxMSAConstraint*>::iterator it = _constraints[i].begin(); it != _constraints[i].end(); it++) {
			ofxMSAConstraint* constraint = *it;
			constraint->debugDraw();
		}
	}
	
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->debugDraw();
	}
}

#ifdef MSAPHYSICS_USE_RECORDER
void ofxMSAPhysics::load(uint frameNum) {
	_recorder.load(frameNum);
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->set(_recorder.get());// * _playbackScaler);
	}
}
#endif

void ofxMSAPhysics::updateParticles() {
	vector<ofxMSAParticle*>::iterator it = _particles.begin();
	int num = 0;
	while(it != _particles.end()) {
		ofxMSAParticle* particle = *it;
		if(particle->_isDead) {							// if particle is dead
			it = _particles.erase(it);
			particle->release();
		} else {
			num++;
			particle->doVerlet();
			particle->update();
			applyUpdaters(particle);
			if(params.doWorldEdges) {
				particle->checkWorldEdges();	
				particle->computeBinFlags();
			}
#ifdef MSAPHYSICS_USE_RECORDER
			if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.add(*particle);
#endif			
			it++;
		}
	}
}


void ofxMSAPhysics::updateConstraintsByType(vector<ofxMSAConstraint*> constraints) {
}

void ofxMSAPhysics::updateAllConstraints() {
	// iterate all constraints and update
	for (int i = 0; i < params.numIterations; i++) {
		for(int i=0; i<OFX_MSA_CONSTRAINT_TYPE_COUNT; i++) {
			
			// if doing collision constraints and collision is disabled skip them
			if(i == OFX_MSA_CONSTRAINT_TYPE_COLLISION && !params.isCollisionEnabled) continue;		
			
			vector<ofxMSAConstraint*>::iterator it = _constraints[i].begin();
			while(it != _constraints[i].end()) {
				ofxMSAConstraint* constraint = *it;
				if(constraint->_isDead || constraint->_a->_isDead || constraint->_b->_isDead) {
					constraint->kill();
					it = _constraints[i].erase(it);
					constraint->release();
				} else {
					if(constraint->shouldSolve()) constraint->solve();
					it++;
				}
			}
			
		}
	}
}


#ifdef MSAPHYSICS_USE_RECORDER
ofxMSAPhysics*  ofxMSAPhysics::setReplayMode(uint i, float playbackScaler) {
	_replayMode = i;
	_playbackScaler = playbackScaler;
	//	if(_replayMode == OFX_MSA_DATA_SAVE)		// NEW
	_recorder.setSize(i);
	return this;	
}


ofxMSAPhysics*  ofxMSAPhysics::setReplayFilename(string f) {
	_recorder.setFilename(f);
	return this;	
}
#endif




ofxMSAConstraint* ofxMSAPhysics::getConstraint(ofxMSAParticle *a, ofxMSAParticle *b, int constraintType) {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints[constraintType].begin(); it != _constraints[constraintType].end(); it++) {
		ofxMSAConstraint* s = *it;
		if(((*s->_a == *a && *s->_b == *b) || (*s->_a == *b && *s->_b == *a)) && !s->_isDead) {
			return s;
		}
	}
	return NULL;
}


ofxMSAConstraint* ofxMSAPhysics::getConstraint(ofxMSAParticle *a, int constraintType) {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints[constraintType].begin(); it != _constraints[constraintType].end(); it++) {
		ofxMSAConstraint* s = *it;
		if (((*s->_a == *a ) || (*s->_b == *a)) && !s->_isDead) {
			return s;
		}
	}
	return NULL;
}
