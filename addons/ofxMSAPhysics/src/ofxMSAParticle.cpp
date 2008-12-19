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


#include "ofxMSAParticle.h"
#include "ofxMSAPhysics.h"

ofxMSAParticle::ofxMSAParticle(float x, float y, float z, float m, float d) {
	init(x, y, z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofxVec3f &v, float m, float d) {
	init(v.x, v.y, v.z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofxMSAParticle &p) {
	init(p.x, p.y, p.z, p._mass, p._drag);
	_isFixed = p._isFixed;
}


void ofxMSAParticle::init(float x, float y, float z, float m, float d) {
	set(x, y, z);
	_oldPos.set(x, y, z);
	_isDead = false;
	_age = 0;
	setMass(m);
	setDrag(d);
	makeFree();
	setClassName("ofxMSAParticle");
}

void ofxMSAParticle::setParams(ofxMSAPhysicsParams *p) {
	params = p;
}

void ofxMSAParticle::setMass(float m) {
	if(m==0) m=0.00001f;
	_mass = m;
	_invMass = 1.0f/m;
}

float ofxMSAParticle::getMass() {
	return _mass;
}

float ofxMSAParticle::getInvMass() {
	return _invMass;
}


void ofxMSAParticle::setDrag(float d) {
	_drag = d;
}

float ofxMSAParticle::getDrag() {
	return _drag;
}

bool ofxMSAParticle::isFixed() {
	return (_isFixed == true);
}

bool ofxMSAParticle::isFree() {
	return (_isFixed == false);
}

void ofxMSAParticle::makeFixed() {
	_isFixed = true;
}

void ofxMSAParticle::makeFree() {
	_oldPos.set(this->x, this->y, this->z);
	_isFixed = false;
}

void ofxMSAParticle::moveTo(ofxVec3f &targetPos) {
	ofxVec3f diff = targetPos - *this;
	moveBy(diff);
}

void ofxMSAParticle::moveBy(ofxVec3f &diffPos) {
	*this += diffPos;
	_oldPos += diffPos;
}

void ofxMSAParticle::moveTo(float x, float y, float z) {
	ofxVec3f temp;
	temp.set(x, y, z);
	moveTo(temp);
}

void ofxMSAParticle::moveBy(float x, float y, float z) {
	ofxVec3f temp;
	temp.set(x, y, z);
	moveBy(temp);
}

void ofxMSAParticle::setVelocity(ofxVec3f vel) {
	_oldPos = *this - vel;
}

void ofxMSAParticle::setVelocity(float x, float y, float z) {
	ofxVec3f temp;
	temp.set(x, y, z);
	setVelocity(temp);		
}

// NEW
void ofxMSAParticle::addVelocity(ofxVec3f &vel) {
//	*this += vel;
	_oldPos -= vel;

}

void ofxMSAParticle::addVelocity(float x, float y, float z) {
	ofxVec3f temp;
	temp.set(x, y, z);		
	addVelocity(temp);
}

ofxVec3f ofxMSAParticle::getVelocity() {
	return (*this - _oldPos);
}

void ofxMSAParticle::kill() {
	_isDead = true;
}


bool ofxMSAParticle::isDead() {
	return _isDead;
}


void ofxMSAParticle::doVerlet() {
	if (!_isFixed) {
		ofxVec3f temp;
		if(params->doGravity) {
			ofxVec3f gravityForce = params->gravity;
			addVelocity(gravityForce);
		}
		
		temp.set(this->x, this->y, this->z);			
		*this += (temp - _oldPos) * params->drag * _drag + params->timeStep2;
		_oldPos.set(temp.x, temp.y, temp.z);
	}
}


void ofxMSAParticle::debugDraw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(2, 5, 5);
	glPopMatrix();
}
