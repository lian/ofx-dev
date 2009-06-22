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

#include "ofxParticle.h"

ofxParticle::ofxParticle(){
	init(0,0,10,1,0.8f);
}

ofxParticle::ofxParticle(float _x, float _y, float _radius, float _mass, float _drag){
	init(_x, _y, _radius, _mass, _drag);
}

ofxParticle::ofxParticle(ofxVec2f iniPos, float _radius, float _mass, float _drag){
	init(iniPos.x, iniPos.y, _radius, _mass, _drag);
}

void ofxParticle::init(float _x, float _y, float _radius, float _mass, float _drag){
	x = _x;
	y = _y;
	oldPos.x = x;
	oldPos.y = y;
	mass = _mass;
	invMass = 1.0f/mass;
	radius = _radius;
	drag = _drag;
	bActive = true;
	bCollide = false;
}

void ofxParticle::update(float timeStep){
	if(!bActive) return;
	float tempX = x, tempY = y;
	accel *= invMass;
	x += (x - oldPos.x)*drag + accel.x * timeStep*timeStep;
	y += (y - oldPos.y)*drag + accel.y * timeStep*timeStep;
	accel.set(0,0);
	oldPos.x = tempX;
	oldPos.y = tempY;
}

void ofxParticle::render(){
	ofCircle(x, y, radius);
}

void ofxParticle::applyForce(ofxVec2f _force){
	accel += _force;	
}

void ofxParticle::applyImpulse(ofxVec2f _impulse){
	if(bActive){
		x += _impulse.x;
		y += _impulse.y;
	}
}

void ofxParticle::setDrag(float _drag){
	drag = _drag;	
}

float ofxParticle::getDrag(){
	return drag;	
}

void ofxParticle::setMass(float _mass){
	mass = _mass;	
	invMass = 1.0f / mass;
}

float ofxParticle::getMass(){
	return mass;	
}

float ofxParticle::getInvMass(){
	return invMass;	
}

void ofxParticle::setRadius(float _radius){
	radius = _radius;	
}

float ofxParticle::getRadius(){
	return radius;	
}

void ofxParticle::setActive(bool _bActive){
	bActive = _bActive;
}

bool ofxParticle::isActive(){
	return bActive;	
}

float ofxParticle::distanceTo(ofxParticle*p){
	float dx = p->x - x;
	float dy = p->y - y;
	return sqrt(dx*dx+dy*dy);
}

float ofxParticle::distanceToSquared(ofxParticle*p){
	float dx = p->x - x;
	float dy = p->y - y;
	return dx*dx+dy*dy;
}

bool ofxParticle::isPointInside(const ofxVec2f& p){
	float dx = p.x - x;
	float dy = p.y - y;
	return dx*dx+dy*dy < radius*radius;
}

void ofxParticle::moveTo(ofxVec2f& _target){
	moveTo(_target.x, _target.y);
}

void ofxParticle::moveTo(float _x, float _y){
	float diffX = _x - x;
	float diffY = _y - y;
	oldPos.x += diffX;
	oldPos.y += diffY;
	x = _x;
	y = _y;
}

void ofxParticle::moveBy(ofxVec2f& _amount){
	moveBy(_amount.x, _amount.y);
}

void ofxParticle::moveBy(float _x, float _y){
	x += _x;
	y += _y;
	oldPos.x += _x;
	oldPos.y += _y;
}

void ofxParticle::lerp(ofxVec2f& _target, float _interp){
	ofxVec2f diff = _target - *this;
	diff *= _interp;
	moveBy(diff);
}

void ofxParticle::moveTowards(ofxVec2f& _target, float _strength){
	ofxVec2f diff = _target - *this;
	diff *= _strength;
	applyForce(diff);
}

void ofxParticle::setVel(ofxVec2f _vel){
	oldPos.x = x - _vel.x;
	oldPos.y = y - _vel.y;
}

ofxVec2f ofxParticle::getVel(){
	return ofxVec2f(x - oldPos.x, y - oldPos.y);
}

void ofxParticle::enableCollisions(bool _bCollisions){
	bCollide = _bCollisions;
}

bool ofxParticle::collisionsEnabled(){
	return bCollide;
}







