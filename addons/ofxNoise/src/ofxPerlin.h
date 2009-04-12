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
one change that i made is that now the noise function returns values in the range -1..1
if you want to get values between 0..1 use the noiseuf(..) functions.
 another thing is that it now uses floats instead of doubles
if you have any questions about this port please contact me: ruibmx at gmail dot com
if you have any questions regarding the original classes please contact Karsten Schmidt.
*/


#pragma once

#include "ofMain.h"
#include "ofxSinCosLUT.h"

class ofxPerlin{
//protected:
public:
	ofxSinCosLUT sinCosLUT;
	static const int PERLIN_YWRAPB = 4;
	static const int PERLIN_YWRAP = 1 << PERLIN_YWRAPB;
	static const int PERLIN_ZWRAPB = 8;
	static const int PERLIN_ZWRAP = 1 << PERLIN_ZWRAPB;
	static const int PERLIN_SIZE = 4095;
	static const int PERLIN_MIN_AMPLITUDE = 0.001f;
	int perlin_octaves; // = 4;
	float perlin_amp_falloff; // = 0.5f;
	
	int perlin_PI, perlin_TWO_PI;
	float *perlin_cosTable;
	float *perlin; //perlin table for float value;

	float noise_fsc(float i);
public:
	
	ofxPerlin();
	~ofxPerlin();
	
	//the following return results in the range -1..1
	float noise(float x);
	float noise(float x, float y); 
	float noise(float x, float y, float z);  
	
	//the follwing return results in the range 0..1
	float noiseuf(float x); 
	float noiseuf(float x, float y);
	float noiseuf(float x, float y, float z);
	
	void noiseDetail(int lod);
	void noiseDetail(int lod, float falloff);
	void noiseSeed(long what);
};


