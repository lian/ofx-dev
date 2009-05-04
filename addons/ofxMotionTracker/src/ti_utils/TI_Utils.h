/*
 *  TI_Utils.h
 *  openFrameworks
 *
 *  Created by Pat Long on 15/12/08.
 *  Copyright 2008 Tangible Interaction. All rights reserved.
 *
 */
#ifndef _TI_UTILS
#define _TI_UTILS

#include "ofMath.h"
#include <cmath>

float tiAngle(float dx, float dy);
float tiAngle(float x1, float y1, float x2, float y2);
float tiAngleXComponent(float angle, float magnitude=1.0, bool radians=false);
float tiAngleYComponent(float angle, float magnitude=1.0, bool radians=false);
float tiAngleToRadians(float angle);
float tiRadiansToAngle(float radians);
float tiNormalizeAngle(float angle);
float tiDistance(float dx, float dy);
float tiDistance(float x1, float y1, float x2, float y2);
float abs(float num);

#endif
