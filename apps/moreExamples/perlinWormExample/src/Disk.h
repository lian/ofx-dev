#pragma once

#include "ofMain.h"

#include "ofxVectorMath.h"
#include "ofx3DUtils.h"

#define NUMP 10

class Disk{
public:

ofxVec3f p[NUMP];
ofxVec3f contourP[NUMP];
ofxVec3f center;
ofxVec3f vel, accel;
float radius;

Disk(ofxVec3f iniPos = ofxVec3f(0, 0, 0), float radius = 30);

void move(ofxVec3f target, float rotY, float rotZ);
};