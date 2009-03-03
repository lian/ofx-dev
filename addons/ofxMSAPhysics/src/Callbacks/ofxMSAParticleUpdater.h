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

#include "ofxObjCPointer.h"
#include "ofMain.h"

#include "ofxMSAParticle.h"


/********************* Particle updater class *************************/
class ofxMSAParticleUpdater : public ofxObjCPointer {
public:
	bool ignoreFixedParticles;
	
	ofxMSAParticleUpdater() {
		setClassName("ofxMSAParticleUpdater");
		ignoreFixedParticles = true;
	}
	
	virtual void update(ofxMSAParticle* p) = 0;
};



/********************* Particle updateable class (for individual particles, or the whole physics class *************************/
/********************* To allow forcefields on individual particles, or the whole particle system  *************************/
class ofxMSAParticleUpdatable {
public:
	ofxMSAParticleUpdatable() {}
	
	virtual ~ofxMSAParticleUpdatable() {
		for(vector<ofxMSAParticleUpdater*>::iterator it = _updaters.begin(); it != _updaters.end(); it++) {
			ofxMSAParticleUpdater* updater = *it;
			if(updater) {
				updater->release();
				updater = NULL;
			}
		}
		_updaters.clear();
	}
	
	ofxMSAParticleUpdatable* addUpdater(ofxMSAParticleUpdater* updater) {
		_updaters.push_back(updater);
		updater->retain();
		return this;	// so you can carry on adding updater
	}
	
	void applyUpdaters(ofxMSAParticle* particle) {
		for(vector<ofxMSAParticleUpdater*>::iterator it = _updaters.begin(); it != _updaters.end(); it++) {
			ofxMSAParticleUpdater* updater = *it;
			if(!(updater->ignoreFixedParticles && particle->isFixed())) updater->update(particle);
		}
	}
	
	
protected:
	vector<ofxMSAParticleUpdater*> _updaters;
};
