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

#include "ofxConstraint.h"

// a constraint that is only active when the distance between the particles is smaller or bigger than the defined values
class ofxInequalityConstraint:public ofxConstraint{
protected:
	float minRest, minSQ, maxRest, maxSQ;
public:
	ofxInequalityConstraint(ofxParticle*_a, ofxParticle*_b, float _minRest, float _maxRest, float _strength):
	ofxConstraint(_a, _b, _minRest, _strength, OFX_INEQUALITY_CONSTRAINT){
		minRest = _minRest;
		maxRest = _maxRest;
		minSQ = minRest*minRest;
		maxSQ = maxRest*maxRest;
	}
	
	virtual void update(){
		if(!bOn) return;
		if(!a->isActive() and !b->isActive()) return;
		delta.x = b->x - a->x;
		delta.y = b->y - a->y;
		float dist = delta.x*delta.x+delta.y*delta.y;
		if(dist > minSQ && dist < maxSQ) return;
		if(dist < minSQ) rest = minRest;
		else rest = maxRest;
		if(dist < 1) dist = 1;
		else dist = sqrt(dist);
		float moveAmount;
		if(a->isActive() && b->isActive()){
			moveAmount = strength*(dist - rest) / dist * (a->getInvMass() + b->getInvMass());
			a->x += moveAmount * delta.x * a->getInvMass();
			a->y += moveAmount * delta.y * a->getInvMass();
			b->x -= moveAmount * delta.x * b->getInvMass();
			b->y -= moveAmount * delta.y * b->getInvMass();
		} else {
			moveAmount = strength*(dist - rest) / dist;
			if(a->isActive()){
				a->x += moveAmount*delta.x;
				a->y += moveAmount*delta.y;
			} else {
				b->x -= moveAmount*delta.x;
				b->y -= moveAmount*delta.y;
			}
		}
	}
};