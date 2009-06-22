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
// a support spring between 2 particles that can bend at a pivot
class ofxSupportConstraint:public ofxConstraint{
protected:
	ofxMinDistSpring*support;
	ofxSpring*springA, *springB;
	ofxParticle*pivot;
	float supportRest;
public:
	ofxSupportConstraint(ofxParticle*_begin, ofxParticle*_end, ofxParticle*_pivot, float _rest, float _supportRest, float _strength = 1.0f):
	ofxConstraint(_begin, _end, _rest, _strength, OFX_SUPPORT_CONSTRAINT){
		pivot = _pivot;
		supportRest = _supportRest;
		support = new ofxMinDistSpring(a,b,_supportRest, strength);
		springA = new ofxSpring(pivot, a, _rest, strength);
		springB = new ofxSpring(pivot, b, _rest, strength);
	}
	
	virtual ~ofxSupportConstraint(){
		delete support;
		delete springA, springB;
	}
	
	virtual void update(){
		if(!bOn) return;
		if(!(a->isActive() || b->isActive())) return;
		support->update();
		springA->update();
		springB->update();
	}
	
	virtual void render(){
		springA->render();
		springB->render();
	}
	
	virtual void setStrength(float _s){
		strength = _s;
		support->setStrength(_s);
	}
	
	virtual void setRest(float _r){
		rest = _r;
		springA->setRest(_r);
		springB->setRest(_r);
	}
	
	virtual void setSupportRest(float _r){
		supportRest = _r;
		support->setRest(_r);
	}
	
	virtual float getSupportRest(){
		return supportRest;	
	}
	
	virtual ofxParticle* getBegin(){
		return a;	
	}
	
	virtual ofxParticle* getEnd(){
		return b;	
	}
	
	virtual ofxParticle* getPivot(){
		return pivot;
	}
	
	virtual void setBegin(ofxParticle*_b){
		a = _b;	
	}
	
	virtual void setEnd(ofxParticle*_e){
		b = _e;	
	}
	
	virtual void setPivot(ofxParticle*_p){
		pivot = _p;	
	}
};

