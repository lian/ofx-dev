/*
 *  TI_Utils.cpp
 *  openFrameworks
 *
 *  Created by Pat Long on 15/12/08.
 *  Copyright 2008 Tangible Interaction. All rights reserved.
 *
 */

#include "TI_Utils.h"

float tiAngle(float dx, float dy){
	float theta;

	// get a proper angle from one point to the next
	theta = atan2(-dy, dx);
	if(dy > 0)
		theta += 2.0 * PI;
	
	return theta;
}

float tiAngle(float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;
	return tiAngle(dx, dy);
}

float tiAngleXComponent(float angle, float magnitude, bool radians){
	if(magnitude == 0.0){
		return 0.0;
	}
	if(!radians){
		angle = tiAngleToRadians(angle);
	}
	return magnitude * cos(angle);
}

float tiAngleYComponent(float angle, float magnitude, bool radians){
	if(magnitude == 0.0){
		return 0.0;
	}
	if(!radians){
		angle = tiAngleToRadians(angle);
	}
	return magnitude * sin(angle);
}

float tiAngleToRadians(float angle){
	return angle * PI / -180.0;
}

float tiRadiansToAngle(float radians){
	return radians * 180.0 / PI;
}

float tiNormalizeAngle(float angle){
	float normalized = std::fmod(angle, (float)360.0);
	if(normalized < 0)
		normalized += 360.0;
	return normalized;
}

float tiDistance(float dx, float dy){
	return sqrt(double(dx*dx + dy*dy));
}

float tiDistance(float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;
	return tiDistance(dx, dy);
}

float abs(float num){
	return (num < 0.0)?num*-1.0:num;
}
