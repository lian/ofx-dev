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
//solves the collision between 2 particles
class ofxCollisionConstraint:public ofxConstraint{
public:
	ofxCollisionConstraint(ofxParticle*a, ofxParticle*b):ofxConstraint(a, b, 1, 1, OFX_COLLISION_CONSTRAINT){}
	void update(){
		if(!a->isActive() && !b->isActive()) return;
		rest = a->getRadius() + b->getRadius();
		delta.x = b->x - a->x;
		if(fabs(delta.x) > rest)return;
		delta.y = b->y - a->y;
		if(fabs(delta.y) > rest)return;
		float dist = delta.x*delta.x+delta.y*delta.y;
		if(dist > rest*rest) return;
		if(dist < 1) dist = 1;
		else dist = sqrt(dist);
		float moveAmount;
		if(a->isActive() && b->isActive()){
			moveAmount = (dist - rest) / (dist*(a->getInvMass() + b->getInvMass()));
			a->x += delta.x * moveAmount * a->getInvMass();
			a->y += delta.y * moveAmount * a->getInvMass();
			b->x -= delta.x * moveAmount * b->getInvMass();
			b->y -= delta.y * moveAmount * b->getInvMass();
		} else {
			moveAmount = (dist - rest) / dist;
			if(a->isActive()){
				a->x += delta.x * moveAmount;
				a->y += delta.y * moveAmount; 
			} else{
				b->x -= delta.x * moveAmount;
				b->y -= delta.y * moveAmount;
			}
		}
		
	}
};
