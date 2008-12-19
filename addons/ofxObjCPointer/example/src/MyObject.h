/*
 *  testData.h
 *  objcPointerTest
 *
 *  Created by Mehmet Akten on 15/10/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#include "ofxObjCPointer.h"

#pragma once

/********** Example dummy class which inherits ofxObjCPointer functionality *************/
class MyObject : public ofxObjCPointer {
public:
	MyObject(float _a, float _b, float _c, float _d) {
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
	
	float a, b, c, d;
};