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
#include "ofMain.h"
#include "ofAddons.h"

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
		if(isOff()) return;
		
		ofxVec3f delta = (*_b) - (*_a);
		float deltaLength = delta.length();
		float diff = (deltaLength - restLength) / (deltaLength * (_a->_invMass + _b->_invMass));
	
		float force = (diff * strength);
//		delta *= restLength * restLength / ( delta * delta + restLength * restLength) - 0.5;
		
		if (!_a->_isFixed) *_a += (_a->_invMass * force) * delta;
		if (!_b->_isFixed) *_b -= (_b->_invMass * force) * delta;
	}
	
};
