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

#include "ofxParticle.h"
#define OFX_SPRING 0
#define OFX_FOLLOWER_CONTRAINT 1
#define OFX_INEQUALITY_CONSTRAINT 2
#define OFX_MAX_DIST_SPRING 3
#define OFX_MIN_DIST_SPRING 4
#define OFX_SUPPORT_CONSTRAINT 5
#define OFX_COLLISION_CONSTRAINT 6

//base calss for all constraints
class ofxConstraint{
protected:
	unsigned char type;
	ofxParticle *a, *b;
	bool bOn;
	float rest;
	float strength;
	ofPoint delta;
public:
	ofxConstraint(ofxParticle *_a, ofxParticle *_b, float _rest, float _strength, unsigned char _type){
		a = _a;
		b = _b;
		bOn = true;
		rest = _rest;
		strength = _strength;
		type = _type;
	}
	
	virtual void update() = 0;
	virtual void render(){
		ofLine(a->x, a->y, b->x, b->y);
	}
	
	virtual void setOn(bool _on){
		bOn = _on;	
	}
	virtual bool isOn(){
		return bOn;	
	}
	virtual ofxParticle* getA(){
		return a;	
	}
	virtual ofxParticle* getB(){
		return b;	
	}
	
	virtual void setA(ofxParticle*_a){
		a = _a;	
	}
	
	virtual void setB(ofxParticle*_b){
		b = _b;	
	}
	
	virtual void setRest(float _rest){
		rest = _rest;	
	}
	
	float getRest(){
		return rest;	
	}
	
	virtual void setStrength(float _strength){
		strength = _strength;	
	}
	
	virtual float getStrength(){
		return strength;	
	}
	
	virtual unsigned char getType(){
		return type;
	}
};

