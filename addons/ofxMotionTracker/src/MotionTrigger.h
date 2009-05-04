/*
 *  MotionTrigger.h
 *  openFrameworks
 *
 *  Created by Pat Long on 06/04/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MOTION_TRIGGER
#define _MOTION_TRIGGER

#include "ofxMotionTracker.h"

#define DEFAULT_TRIGGER_ANGLE 90
#define DEFAULT_TRIGGER_ANGLE_SPREAD 45
#define DEFAULT_TRIGGER_MAGNITUDE 100
#define DEFAULT_CAMERA_ID 1

#define DRAW_TRIGGER_ARC // requires the ofGraphics::ofCircleSlice() mod from http://www.openframeworks.cc/forum/viewtopic.php?t=1811

class MotionTrigger : public MotionTracker{
protected:
	float triggerAngle, triggerAngleSpread, triggerMagnitude;
	int triggerDelay, fireTime;
	bool firing;
	ofRectangle* triggerArea;
	
	virtual void fire();
	virtual void ceaseFire();
	bool isReadyToFire();
	bool shouldTrigger();
	
public:
	MotionTrigger();
	~MotionTrigger();
	virtual void init(float triggerAngle=DEFAULT_TRIGGER_ANGLE, float triggerAngleSpread=DEFAULT_TRIGGER_ANGLE_SPREAD, float triggerMagnitude=DEFAULT_TRIGGER_MAGNITUDE, int cameraID=DEFAULT_CAMERA_ID);
	
	bool isFiring();
	
	float getTriggerAngle();
	float getTriggerAngleSpread();
	float getTriggerMagnitude();
	int getTriggerDelay();
	void setTriggerAngle(float triggerAngle);
	void setTriggerAngleSpread(float triggerAngleSpread);
	void setTriggerMagnitude(float triggerMagnitude);
	void setTriggerDelay(int triggerDelay);
	
	void setTriggerArea(ofRectangle* triggerArea);
	
	virtual void draw();
	void drawOpticalFlowTrigger(int x, int y, int w, int h);
	virtual void update();
};

#endif
