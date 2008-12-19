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

#include "ofxMSAPhysics.h"

ofxMSAPhysics::ofxMSAPhysics() {
	setTimeStep(0.000010);
	setNumIterations();
	setGravity();
	setDrag();
	_frameCounter = 0;
	setReplayMode(OFX_MSA_DATA_IDLE);
	setReplayFilename("recordedData/physics/physics");
}

ofxMSAPhysics::~ofxMSAPhysics() {
	clear();
}

ofxMSAParticle* ofxMSAPhysics::makeParticle(float x, float y, float z, float m, float d) {
	ofxMSAParticle *p = new ofxMSAParticle(x, y, z, m, d);
	addParticle(p);
	return p;
}

ofxMSASpring* ofxMSAPhysics::makeSpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength) {
	if(a==b || getConstraint(a, b)) return NULL;
	ofxMSASpring* s = new ofxMSASpring(a, b, _strength, _restLength);
	addConstraint(s);
	return s;
}

ofxMSAParticle* ofxMSAPhysics::addParticle(ofxMSAParticle *p) {
	_particles.push_back(p);
	p->setInstanceName(string("particle ") + ofToString((int)_particles.size()));
	p->setParams(&params);
	if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.setSize(numberOfParticles());
	return p;		// so you can configure the particle or use for creating constraints
}

ofxMSAConstraint* ofxMSAPhysics::addConstraint(ofxMSAConstraint *s) {
	if(getConstraint(s->_a, s->_b) == NULL) {
		_constraints.push_back(s);
		s->setInstanceName(string("constraint ") + ofToString((int)_constraints.size()));
		(s->_a)->retain();
		(s->_b)->retain();
	}
	return s;		// so you can configure the constraint
}


ofxMSAParticle* ofxMSAPhysics::getParticle(int i) {
	return _particles.at(i);
}

ofxMSAConstraint* ofxMSAPhysics::getSpring(int i) {
	return _constraints.at(i);
}


int ofxMSAPhysics::numberOfParticles() {
	return _particles.size();
}

int ofxMSAPhysics::numberOfSprings() {
	return _constraints.size();
}

void ofxMSAPhysics::setDrag(float drag) {
	params.drag = drag;
}

void ofxMSAPhysics::setTimeStep(float timeStep) {
	params.timeStep = timeStep;
	params.timeStep2 = timeStep * timeStep;
}

void ofxMSAPhysics::setNumIterations(float numIterations) {
	_numIterations = numIterations;
}

void ofxMSAPhysics::setGravity(float gy) {
	setGravity(0, gy, 0);
}

ofxVec3f& ofxMSAPhysics::getGravity() {
	return params.gravity;
}


void ofxMSAPhysics::setGravity(float gx, float gy, float gz) {
	params.gravity.set(gx, gy, gz);
	params.doGravity = params.gravity.lengthSquared() > 0;
}

void ofxMSAPhysics::setGravity(ofxVec3f &g) {						// NEW
	params.gravity.set(g);
	params.doGravity = params.gravity.lengthSquared() > 0;
}

void ofxMSAPhysics::setReplayMode(int i, float playbackScaler) {
	_replayMode = i;
	_playbackScaler = playbackScaler;
	if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.setSize(i);
}


void ofxMSAPhysics::setReplayFilename(string f) {
	_recorder.setFilename(f);
}


void ofxMSAPhysics::clear() {
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->release();
	}
	_particles.clear();
	
	for (vector<ofxMSAConstraint*>::iterator it = _constraints.begin(); it != _constraints.end(); it++) {
		ofxMSAConstraint* constraint = *it;
		constraint->release();
	}
	_constraints.clear();
}

void ofxMSAPhysics::setParticleCount(int i) {
	_particles.reserve(i);
	if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.setSize(i);
}


void ofxMSAPhysics::setConstraintCount(int i){
	_particles.reserve(i);
}



void ofxMSAPhysics::update(int frameNum) {
	if(frameNum < 0) frameNum = _frameCounter;
	
	params.invWidth = 1.0f/ofGetWidth();
	params.invHeight = 1.0f/ofGetHeight();

	if(_replayMode == OFX_MSA_DATA_LOAD) {
		load(frameNum);
	} else {
		updateParticles();
		updateConstraints();
		if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.save(frameNum);
	}
	_frameCounter++;
}


void ofxMSAPhysics::draw() {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints.begin(); it != _constraints.end(); it++) {
		ofxMSAConstraint* constraint = *it;
		constraint->draw();
	}
	
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->draw();
	}
}

void ofxMSAPhysics::debugDraw() {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints.begin(); it != _constraints.end(); it++) {
		ofxMSAConstraint* constraint = *it;
		constraint->debugDraw();
	}
	
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->debugDraw();
	}
}


void ofxMSAPhysics::load(int frameNum) {
	_recorder.load(frameNum);
	for(vector<ofxMSAParticle*>::iterator it = _particles.begin(); it != _particles.end(); it++) {
		ofxMSAParticle* particle = *it;
		particle->set(_recorder.get() * _playbackScaler);
	}
}


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
			if(_replayMode == OFX_MSA_DATA_SAVE) _recorder.add(*particle);
			it++;
		}
	}
}


void ofxMSAPhysics::updateConstraints() {
	for (int i = 0; i < _numIterations; i++) {
		vector<ofxMSAConstraint*>::iterator it = _constraints.begin();
		while(it != _constraints.end()) {
			ofxMSAConstraint* constraint = *it;
			if(constraint->_isDead || constraint->_a->_isDead || constraint->_b->_isDead) {
				constraint->kill();
				it = _constraints.erase(it);
				constraint->release();
			} else {
				constraint->solve();
				it++;
			}
		}
	}
}


ofxMSAConstraint* ofxMSAPhysics::getConstraint(ofxVec3f *a, ofxVec3f *b) {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints.begin(); it != _constraints.end(); it++) {
		ofxMSAConstraint* s = *it;
		if ((*s->_a == *a && *s->_b == *b) || (*s->_a == *b && *s->_b == *a)) {
			return s;
		}
	}
	return NULL;
}

ofxMSAConstraint* ofxMSAPhysics::getConstraint(ofxVec3f *a) {
	for (vector<ofxMSAConstraint*>::iterator it = _constraints.begin(); it != _constraints.end(); it++) {
		ofxMSAConstraint* s = *it;
		if (((*s->_a == *a ) || (*s->_b == *a)) && !s->_isDead) {
			return s;
		}
	}
	return NULL;
}
