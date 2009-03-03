/***********************************************************************
 
 This class interfaces the fluid solver with ofxMSAPhysics (applies fluid velocity as forces to particles)
 
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

#ifdef OF_ADDON_USING_OFXMSAPHYSICS

#include "ofxMSAParticleUpdater.h"
#include "ofxMSAFluid.h"



class ofxMSAFluidParticleUpdater : public ofxMSAParticleUpdater {
public:
	ofxMSAFluidParticleUpdater() {
		_fluidSolver = NULL;
	}
	
	void init(ofxMSAFluidSolver* f) {
		_fluidSolver = f;
		
	}
	
	void update(ofxMSAParticle* p) {
		ofPoint vel;
		_fluidSolver->getInfoAtPos(p->x * p->params->invWidth, p->y * p->params->invHeight, &vel, NULL);
		float invMass = p->getInvMass();
		p->addVelocity(vel.x * invMass, vel.y * invMass, 0);
	}
	
	
protected:
	ofxMSAFluidSolver *_fluidSolver;
	
};

#endif