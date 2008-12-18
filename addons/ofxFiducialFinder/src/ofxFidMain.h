/*
 *  ofxFidMain.h
 *  openFrameworks
 *
 *  Created by Alain Ramos a.k.a. ding
 *  Copyright 2008 Alain Ramos.
 *
 *
 For Free you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 */
//	----------------------------------------------------------------------------------------------------

#ifndef OF_X_FIDMAIN_H
#define OF_X_FIDMAIN_H

//the fiducial class
#include "ofxFiducial.h"

//the finger class
#include "ofxFinger.h"

//simple fiducial finder using a vector
//resets every frame and doesn't keep track of previous fiducials
//also doesnt get acceleration, speed, etc info
#include "ofxFiducialFinder.h"

//more complex and advanced fiducial tracker using a list
//this is the one I will be focused on for all the cool features
//This Is The Good One
#include "ofxFiducialTracker.h"

#endif

