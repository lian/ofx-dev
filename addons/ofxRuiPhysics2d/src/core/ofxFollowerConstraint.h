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

#include "ofxPhysics2d.h"
//a follows b :)
class ofxFollowerConstraint: public ofxConstraint{
protected:
	
public:
	ofxFollowerConstraint(ofxParticle *follower, ofxParticle* leader, float _strength):
	ofxConstraint(follower, leader, 0.0f, _strength, OFX_FOLLOWER_CONTRAINT){
		
	}
	
	virtual void update(){
		if(!isOn())return;
		if(!a->isActive() and !b->isActive()) return;
		delta.x = b->x - a->x;
		delta.y = b->y - a->y;
		delta *= strength;
		delta *= a->getInvMass();
		a->x += delta.x;
		a->y += delta.y;
	}
	
	virtual ofxParticle* getFollower(){
		return a;
	}
	
	virtual ofxParticle* getLeader(){
		return b;
	}
};