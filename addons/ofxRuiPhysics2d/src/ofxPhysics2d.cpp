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

#include "ofxPhysics2d.h"


ofxPhysics2d::ofxPhysics2d(ofxVec2f _grav, bool _bCollisions, int _numIterations, ofxVec2f _worldMin, ofxVec2f _worldMax, bool _bCheckBounds){
	gravity.set(_grav);
	bCollisions = _bCollisions;
	numIterations = _numIterations;
	bCheckBounds = _bCheckBounds;
	worldMin.set(_worldMin);
	worldMax.set(_worldMax);
	collisionSolver = new ofxCollisionConstraint(NULL, NULL);
}

ofxPhysics2d::~ofxPhysics2d(){
	for(int i=0; i<particles.size(); i++){
		delete particles[i];	
	}
	particles.clear();
	for(int i=0; i<constraints.size(); i++){
		delete constraints[i];
	}
	constraints.clear();
}

void ofxPhysics2d::update(float timeStep){
	for(int i=0; i<particles.size(); i++){
		particles[i]->applyImpulse(gravity);
		particles[i]->update(timeStep);
	}
	
	for(int n=0; n<numIterations; n++){
		for(int i=0; i<constraints.size(); i++){
			constraints[i]->update();
		}
		if(bCollisions){
			for(int i=0; i<particles.size(); i++){
				for(int j=i+1; j<particles.size(); j++){
					if(particles[i]->collisionsEnabled() && particles[j]->collisionsEnabled()){
						collisionSolver->setA(particles[i]);
						collisionSolver->setB(particles[j]);
						collisionSolver->update();
					}
				}
			}
		}
		if(bCheckBounds){
			boundsConstrain();
		}
	}
}

void ofxPhysics2d::renderParticles(){
	for(int i=0; i<particles.size(); i++){
		particles[i]->render();
	}
}

void ofxPhysics2d::renderConstraints(){
	for(int i=0; i<constraints.size(); i++){
		constraints[i]->render();	
	}
}

void ofxPhysics2d::render(){
	renderParticles();
	renderConstraints();
}

void ofxPhysics2d::addParticle(ofxParticle* _p, bool _enableCollisions){
	particles.push_back(_p);
	_p->enableCollisions(_enableCollisions);
}

void ofxPhysics2d::deleteParticle(uint _i){
	if(_i >= particles.size()) return;
	delete particles[_i];
	particles.erase(particles.begin() + _i);
}

void ofxPhysics2d::deleteParticle(ofxParticle* _p){
	for(int i=0; i<particles.size(); i++){
		if(_p == particles[i]){
			particles.erase(particles.begin() + i);
			delete _p;
			return;
		}
	}
}

void ofxPhysics2d::addConstraint(ofxConstraint* _c){
	constraints.push_back(_c);
}

void ofxPhysics2d::deleteConstraint(uint _i){
	if(_i >= constraints.size()) return;
	delete constraints[_i];
	constraints.erase(constraints.begin() + _i);
}

void ofxPhysics2d::deleteConstraint(ofxConstraint*_c){
	for(int i=0; i<constraints.size(); i++){
		if(_c == constraints[i]){
			delete constraints[i];
			constraints.erase(constraints.begin() + i);
			return;
		}
	}
}

void ofxPhysics2d::add(ofxParticle*p){
	particles.push_back(p);
	p->enableCollisions(bCollisions);
}

void ofxPhysics2d::add(ofxParticle*p, bool _enableCollisions){
	particles.push_back(p);
	p->enableCollisions(_enableCollisions);
}

void ofxPhysics2d::add(ofxConstraint*c){
	constraints.push_back(c);
}

ofxParticle* ofxPhysics2d::getParticle(uint _i){
	return particles[_i];
}
ofxConstraint* ofxPhysics2d::getConstraint(uint _i){
	return constraints[_i];	
}

bool ofxPhysics2d::hasParticle(ofxParticle*p){
	for(int i=0; i<particles.size(); i++){
		if(particles[i] == p) return true;	
	}
	return false;
}

bool ofxPhysics2d::hasConstraint(ofxConstraint*c){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i] == c) return true;	
	}
	return false;
}

bool ofxPhysics2d::has(ofxParticle*p){
	return hasParticle(p);
}

bool ofxPhysics2d::has(ofxConstraint*c){
	return hasConstraint(c);	
}

void ofxPhysics2d::setNumIterations(uint _n){
	numIterations = _n;	
}

int ofxPhysics2d::getNumIterations(){
	return numIterations;	
}

void ofxPhysics2d::enableCollisions(bool _bEnable){
	bCollisions = _bEnable;
}

bool ofxPhysics2d::collisionsEnabled(){
	return bCollisions;	
}

void ofxPhysics2d::checkBounds(bool _bCheck){
	bCheckBounds = _bCheck;
}

bool ofxPhysics2d::boundsCheck(){
	return bCheckBounds;
}

void ofxPhysics2d::enableCollisionsForParticle(uint _i, bool _bEnable){
	if(_i<particles.size())particles[_i]->enableCollisions(_bEnable);
}

void ofxPhysics2d::removeConstraintsWithParticle(ofxParticle*p){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->getA() == p or constraints[i]->getB() == p){
			constraints.erase(constraints.begin() + i);
		}
	}
}

bool ofxPhysics2d::hasConstraintsWithParticle(ofxParticle*p){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->getA() == p or constraints[i]->getB() == p)return true;
	}
	return false;
}

void ofxPhysics2d::deleteConstraintsWithParticle(ofxParticle *p){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->getA() == p or constraints[i]->getB() == p){
			delete constraints[i];
			constraints.erase(constraints.begin() + i);
		}
	}
}

ofxConstraint* ofxPhysics2d::getConstraintWithParticle(ofxParticle *p){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->getA() == p or constraints[i]->getB() == p){
			return constraints[i];	
		}
	}
	return NULL;
}

ofxParticle* ofxPhysics2d::getNearestParticle(ofxVec2f point){
	if(particles.size() == 0) return NULL;
	if(particles.size() == 1) return particles[0];
	int _index = 0;
	float minDistSQ, dx, dy, distSQ;
	dx = particles[0]->x - point.x;
	dy = particles[0]->y - point.y;
	minDistSQ = dx*dx+dy*dy;
	for(int i=1; i<particles.size(); i++){
		dx = particles[i]->x - point.x;
		dy = particles[i]->y - point.y;
		distSQ = dx*dx+dy*dy;
		if(distSQ < minDistSQ){
			minDistSQ = distSQ;
			_index = i;
		}
	}
	return particles[_index];
}


ofxParticle* ofxPhysics2d::getParticleUnderPoint(ofPoint& point){
	for(int i=0; i<particles.size(); i++){
		float dx = particles[i]->x - point.x;
		float dy = particles[i]->y - point.y;
		float radius = particles[i]->getRadius();
		if(dx*dx+dy*dy < radius*radius) return particles[i];
	}
	return NULL;
}

void ofxPhysics2d::boundsConstrain(){
	for(int i=0; i<particles.size(); i++){
		particles[i]->x = MAX(worldMin.x + particles[i]->getRadius(), MIN(worldMax.x - particles[i]->getRadius(), particles[i]->x));
		particles[i]->y = MAX(worldMin.y + particles[i]->getRadius(), MIN(worldMax.y - particles[i]->getRadius(), particles[i]->y));
	}
}

int ofxPhysics2d::getNumParticles(){
	return particles.size();	
}

int ofxPhysics2d::getNumConstraints(){
	return constraints.size();	
}

vector<ofxParticle*>& ofxPhysics2d::getParticles(){
	return particles;
}

vector<ofxConstraint*>& ofxPhysics2d::getConstraints(){
	return constraints;
}

ofxVec2f& ofxPhysics2d::getGravity(){
	return gravity;
}

void ofxPhysics2d::setGravity(ofxVec2f _gravity){
	gravity.set(_gravity);
}

void ofxPhysics2d::removeAllParticles(){
	particles.clear();
}

void ofxPhysics2d::deleteAllParticles(){
	for(int i=0; i<particles.size(); i++){
		delete particles[i];
	}
	particles.clear();
}

void ofxPhysics2d::removeAllConstraints(){
	constraints.clear();
}

void ofxPhysics2d::deleteAllConstraints(){
	for(int i=0; i<constraints.size(); i++){
		delete constraints[i];
	}
	constraints.clear();
}

void ofxPhysics2d::removeAll(){
	removeAllParticles();
	removeAllConstraints();
}

void ofxPhysics2d::deleteAll(){
	deleteAllParticles();
	deleteAllConstraints();
}

void ofxPhysics2d::reserveForParticles(int numberOfParticles){
	particles.reserve(numberOfParticles);
}

void ofxPhysics2d::reserveForConstraints(int numberOfConstraints){
	constraints.reserve(numberOfConstraints);
}











