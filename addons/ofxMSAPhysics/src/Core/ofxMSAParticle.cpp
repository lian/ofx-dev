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


#include "ofxMSAParticle.h"
#include "ofxMSAPhysics.h"
#include "binner.h"

ofxMSAParticle::ofxMSAParticle(float x, float y, float z, float m, float d) {
	init(x, y, z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofPoint &v, float m, float d) {
	init(v.x, v.y, v.z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofxMSAParticle &p) {
	init(p.x, p.y, p.z, p._mass, p._drag);
	_isFixed = p._isFixed;
	setBounce(p._bounce);
	setRadius(p._radius);
}


void ofxMSAParticle::init(float x, float y, float z, float m, float d) {
	_params = NULL;
	_physics = NULL;
	
	set(x, y, z);
	_oldPos.set(x, y, z);
	setMass(m);
	setDrag(d);
	setBounce();
	setRadius();
	disableCollision();
	makeFree();
	_isDead = false;
	_age = 0;
	verbose = true;
	setClassName("ofxMSAParticle");
}




ofxMSAParticle* ofxMSAParticle::setMass(float t) {
	if(t==0) t=0.00001f;
	_mass = t;
	_invMass = 1.0f/t;
	return this;
}

float ofxMSAParticle::getMass() {
	return _mass;
}

float ofxMSAParticle::getInvMass() {
	return _invMass;
}


ofxMSAParticle* ofxMSAParticle::setDrag(float t) {
	_drag = t;
	return this;
}

float ofxMSAParticle::getDrag() {
	return _drag;
}

ofxMSAParticle* ofxMSAParticle::setBounce(float t) {
	_bounce = t;
	return this;
}

float ofxMSAParticle::getBounce() {
	return _bounce;
}


ofxMSAParticle* ofxMSAParticle::setRadius(float t) {
	_radius = t;
	return this;
}

float ofxMSAParticle::getRadius() {
	return _radius;
}

ofxMSAParticle* ofxMSAParticle::enableCollision(){
	_globalCollisionEnabled = true;
	if(_physics) _physics->addToCollision(this);
	return this;
}

ofxMSAParticle* ofxMSAParticle::disableCollision() {
	_globalCollisionEnabled = false;
	if(_physics) _physics->removeFromCollision(this);
	return this;
}

bool ofxMSAParticle::hasCollision() {
	return _globalCollisionEnabled;
}




bool ofxMSAParticle::isFixed() {
	return (_isFixed == true);
}

bool ofxMSAParticle::isFree() {
	return (_isFixed == false);
}

ofxMSAParticle* ofxMSAParticle::makeFixed() {
	_isFixed = true;
	return this;
}

ofxMSAParticle* ofxMSAParticle::makeFree() {
	_oldPos.set(this->x, this->y, this->z);
	_isFixed = false;
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveTo(ofPoint &targetPos) {
	ofPoint diff = targetPos - *this;
	moveBy(diff);
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveBy(ofPoint &diffPos) {
	*this += diffPos;
	_oldPos += diffPos;
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveTo(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);
	moveTo(temp);
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveBy(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);
	moveBy(temp);
	return this;
}

ofxMSAParticle* ofxMSAParticle::setVelocity(ofPoint &vel) {
	_oldPos = *this - vel;
	return this;
}

ofxMSAParticle* ofxMSAParticle::setVelocity(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);
	setVelocity(temp);		
	return this;
}

ofxMSAParticle* ofxMSAParticle::addVelocity(ofPoint &vel) {
	_oldPos -= vel;
	return this;
}

ofxMSAParticle* ofxMSAParticle::addVelocity(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);		
	addVelocity(temp);
	return this;
}

ofPoint &ofxMSAParticle::getVelocity() {
//	return (*this - _oldPos);
	return _vel; 
}

void ofxMSAParticle::kill() {
	_isDead = true;
}


bool ofxMSAParticle::isDead() {
	return _isDead;
}


void ofxMSAParticle::doVerlet() {
	if (!_isFixed) {
		if(_params->doGravity) {
			ofPoint gravityForce = _params->gravity;
			addVelocity(gravityForce);
		}
		
		ofPoint curPos = *this;
		_vel = curPos - _oldPos;
		*this += _vel * _params->drag * _drag + _params->timeStep2;
//		*this += _vel + 
		_oldPos = curPos;
	}
}

bool ofxMSAParticle::isInSameBinAs(ofxMSAParticle* p) {
	return (_xBinFlags & p->_xBinFlags) && (_yBinFlags & p->_yBinFlags) && (_zBinFlags & p->_zBinFlags);
}


void ofxMSAParticle::computeBinFlags() {
	computeBinPosition(x, y, z, &_xBinFlags, &_yBinFlags, &_zBinFlags);
}


void ofxMSAParticle::checkWorldEdges() {
//	printf("%.3f, %.3f, %.3f\n", _params->worldMin.x, _params->worldMax.y, _params->worldMax.z);
	if(x < _params->worldMin.x + _radius) {
		moveTo(_params->worldMin.x + _radius, y, z);
		setVelocity(-_vel.x * _bounce, _vel.y, _vel.z);
	} else if(x > _params->worldMax.x - _radius) {
		moveTo(_params->worldMax.x - _radius, y, z);
		setVelocity(-_vel.x * _bounce, _vel.y, _vel.z);
	}

	if( y < _params->worldMin.y + _radius) {
		moveTo(x, _params->worldMin.y + _radius, z);
		setVelocity(_vel.x, -_vel.y * _bounce, _vel.z);
	} else if(y > _params->worldMax.y - _radius) {
		moveTo(x, _params->worldMax.y - _radius, z);
		setVelocity(_vel.x, -_vel.y * _bounce, _vel.z);
	}

	if(z < _params->worldMin.z + _radius) {
		moveTo(x, y, _params->worldMin.z + _radius);
		setVelocity(_vel.x, _vel.y, -_vel.z * _bounce);
	} else if(z > _params->worldMax.z - _radius) {
		moveTo(x, y, _params->worldMax.z - _radius);
		setVelocity(_vel.x, _vel.y, -_vel.z * _bounce);
	}
}


void ofxMSAParticle::debugDraw() {
	glPushMatrix();
	glTranslatef(x, y, z);
#ifndef TARGET_OF_IPHONE		
	glutSolidSphere(_radius, 5, 5);
#endif	
	glPopMatrix();
}
