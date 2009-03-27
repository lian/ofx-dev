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


/*
 this is a port of Karsten Schmidt's perlin noise class for java.
 the original can be found here: code.google.com/p/toxiclibs
 
 i changed a few things and optimized it a little.
 it now uses floats instead of doubles.
 if you have any questions about this port please contact me: ruibmx at gmail dot com
 if you have any questions regarding the original classes please contact Karsten Schmidt.
 */

#pragma once

#include "ofMain.h"

class ofxSimplex{
protected:
	int *perm;
	float dot(int *g, float x, float y);
	float dot(int *g, float x, float y, float z);
	float dot(int *g, float x, float y, float z, float w);
	int fastfloor(float x);
public:
	ofxSimplex();
	~ofxSimplex();
	
	float noise(float x, float y);
	float noise(float x, float y, float z);
	float noise(float x, float y, float z, float w);
	
	float noiseuf(float x, float y);
	float noiseuf(float x, float y, float z);
	float noiseuf(float x, float y, float z, float w);
	
	
};
















