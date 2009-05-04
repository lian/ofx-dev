/*
 *  MotionTrigger.cpp
 *  openFrameworks
 *
 *  Created by Pat Long on 06/04/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "MotionTrigger.h"

MotionTrigger::MotionTrigger(){
}

MotionTrigger::~MotionTrigger(){
}

void MotionTrigger::init(float triggerAngle, float triggerAngleSpread, float triggerMagnitude, int cameraID){
	MotionTracker::init(640, 480, cameraID);
	this->setMirrorVideo(true);
	this->triggerAngle = triggerAngle;
	this->triggerAngleSpread = triggerAngleSpread;
	this->triggerMagnitude = triggerMagnitude;
	this->triggerDelay = 0;
	this->fireTime = -1;
	this->triggerArea = NULL;
}

void MotionTrigger::fire(){
	this->firing = true;
	this->fireTime = -1;
}

void MotionTrigger::ceaseFire(){
	this->firing = false;
}

bool MotionTrigger::isReadyToFire(){
	if(this->triggerDelay == 0 && this->shouldTrigger())
		return true;
	
	int currentTime = ofGetElapsedTimeMillis();
	if(this->fireTime <= 0 && this->shouldTrigger())
		this->fireTime = currentTime + this->triggerDelay;
	else if(this->fireTime > 0 && (currentTime - this->fireTime) >= this->triggerDelay)
		return true;
	
	return false;
}

bool MotionTrigger::shouldTrigger(){
	float angle, magnitude;
	this->getVelAverageAngleMag(&angle, &magnitude, this->triggerArea);
	bool check = false;
	if(magnitude > this->triggerMagnitude){
		// normalize the optical flow angle
		angle -= 90.0; // needed to offset/correct from optical flow solver
		angle = tiNormalizeAngle(angle);
		
		float angleLow = tiNormalizeAngle(this->triggerAngle - this->triggerAngleSpread);
		float angleHigh = tiNormalizeAngle(this->triggerAngle + this->triggerAngleSpread);
		
		if(angleLow <= angleHigh){
			if(angle >= angleLow && angle <= angleHigh)
				check = true;
		}
		else{
			// an angle bounds case (ie. handle the 0/360 loop around)
			if((angle >= angleLow && angle <= 360.0) || (angle >= 0.0 && angle <= angleHigh))
				check = true;
		}
	}
	return check;
}

bool MotionTrigger::isFiring(){
	return this->firing;
}

float MotionTrigger::getTriggerAngle(){
	return this->triggerAngle;
}

float MotionTrigger::getTriggerAngleSpread(){
	return this->triggerAngleSpread;
}

float MotionTrigger::getTriggerMagnitude(){
	return this->triggerMagnitude;
}

int MotionTrigger::getTriggerDelay(){
	return this->triggerDelay;
}

void MotionTrigger::setTriggerAngle(float triggerAngle){
	this->triggerAngle = triggerAngle;
}

void MotionTrigger::setTriggerAngleSpread(float triggerAngleSpread){
	this->triggerAngleSpread = triggerAngleSpread;
}

void MotionTrigger::setTriggerMagnitude(float triggerMagnitude){
	this->triggerMagnitude = triggerMagnitude;
}

void MotionTrigger::setTriggerArea(ofRectangle* triggerArea){
	this->triggerArea = triggerArea;
}

void MotionTrigger::setTriggerDelay(int triggerDelay){
	this->triggerDelay = triggerDelay;
}

void MotionTrigger::draw(){
	this->drawDebugVideo(0, 480, 320, 240);
	this->drawColor(0, 0, 640, 480);
	this->drawOpticalFlowTrigger(640, 0, 640, 480);
}

void MotionTrigger::drawOpticalFlowTrigger(int x, int y, int w, int h){
	float ratioX = ((float)w / (float)this->camWidth) / 2.0;
	float ratioY = ((float)h / (float)this->camHeight) / 2.0;
	
	ofSetColor(255, 255, 0);
	this->drawOpticalFlowAverage(x, y, w, h, this->triggerArea);
	
	ofSetColor(255, 0, 0);
	float centerX = x + w/2.0;
	float centerY = y + h/2.0;
	float x2, y2;
	
	float lowAngle = tiNormalizeAngle(this->triggerAngle - this->triggerAngleSpread);
	x2 = centerX + tiAngleXComponent(lowAngle, this->triggerMagnitude * ratioX);
	y2 = centerY + tiAngleYComponent(lowAngle, this->triggerMagnitude * ratioY);
	ofLine(centerX, centerY, x2, y2);
	
	float highAngle = tiNormalizeAngle(this->triggerAngle + this->triggerAngleSpread);
	x2 = centerX + tiAngleXComponent(highAngle, this->triggerMagnitude * ratioX);
	y2 = centerY + tiAngleYComponent(highAngle, this->triggerMagnitude * ratioY);
	ofLine(centerX, centerY, x2, y2);
	
#ifdef DRAW_TRIGGER_ARC
	ofNoFill();
	ofSetCircleResolution(360);
	// ofCircleSlice(centerX, centerY, this->triggerMagnitude * ratioX, lowAngle, highAngle);
	ofCircle(centerX, centerY, this->triggerMagnitude * ratioX);
	ofSetCircleResolution(CIRC_RESOLUTION);
	ofFill();
#endif
	
	if(this->isFiring())
		ofCircle(centerX, centerY, this->triggerMagnitude * ratioX * 0.5);
	
	ofSetColor(255, 255, 255);
}

void MotionTrigger::update(){
	MotionTracker::update();
	if(this->isReadyToFire())
		this->fire(); // FIRE!!!
	else
		this->ceaseFire();
}
