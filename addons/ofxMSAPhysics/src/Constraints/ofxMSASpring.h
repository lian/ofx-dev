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
#include "ofxMSAConstraint.h"

class ofxMSASpring : public ofxMSAConstraint {
public:	
	friend class ofxMSAPhysics;
	
	float restLength;
	float strength;
	
	ofxMSASpring(ofxMSAParticle *a, ofxMSAParticle *b, float _strength, float _restLength) {
		this->_a = a;
		this->_b = b;
		strength	= _strength;
		restLength	= _restLength;
		_type = OFX_MSA_CONSTRAINT_TYPE_SPRING;
		setClassName(string("ofxMSASpring"));
	}
	
protected:	
	void solve() {
		ofPoint delta = (*_b) - (*_a);
		float deltaLength2 = msaLengthSquared(delta);
		float deltaLength = sqrt(deltaLength2);	// TODO: fast approximation of square root (1st order Taylor-expansion at a neighborhood of the rest length r (one Newton-Raphson iteration with initial guess r))
		float force = strength * (deltaLength - restLength) / (deltaLength * (_a->getInvMass() + _b->getInvMass()));
		
		if (!_a->isFixed()) *_a += delta * (_a->getInvMass() * force);
		if (!_b->isFixed()) *_b -= delta * (_b->getInvMass() * force);
 	}
	
};
