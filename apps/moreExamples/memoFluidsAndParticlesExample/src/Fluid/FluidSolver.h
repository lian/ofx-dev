/***********************************************************************
 
 This class solves a fluid system based on the classic Jos Stam paper I'm sure you've heard about :P
 http://www.dgp.toronto.edu/people/stam/reality/Research/pdf/GDC03.pdf
 
 also had help from this site (though its in 3D, so simplied it a bit)
 http://www.mikeash.com/?page=pyblog/fluid-simulation-for-dummies.html
 
 
 In addition to the features in the Jos Stam paper, this class allows you to add colored dye and force at (x,y) coordinates using the addAt....() functions
 Also use the getInfo() function to read velocity and density at any coordinates in the fluid so you can feed it to a particle system or something
 
 
 -----------------------------------
 
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


#pragma once

#include "ofMain.h"


#define		IX(i, j)		((i) + (_NX + 2)  *(j))
#define		FLUID_INFO_U		0
#define		FLUID_INFO_V		1
#define		FLUID_INFO_DENSITY	2
#define		FLUID_INFO_CURL		3

class FluidSolver {

public:	
	
	// pass this a pre-allocated pointer of 4 floats and it fills it with the info above (FLUID_INFO_U, FLUID_INFO_V, FLUID_INFO_DENSITY, FLUID_INFO_CURL)
	void getInfo(float x, float y, float* info);
	
	// add color and force at normalized (x, y) coordinates
	// dx: horizontal velocity
	// dy: vertical velocity
	// generateMult: multiplier for creating fluid (if 0, not fluid is created)
	// velocityMult: multipler for transferring velocity to fluid (if 0, no force is applied)
	// r, g, b: normalized R, G, B components of color to inject
	void addAtNorm(float x, float y, float dx, float dy, float generateMult, float velocityMult, float r, float g, float b);
	
	// add color and force at (x, y) fluid cell coordinates
	// dx: horizontal velocity
	// dy: vertical velocity
	// generateMult: multiplier for creating fluid (if 0, not fluid is created)
	// velocityMult: multipler for transferring velocity to fluid (if 0, no force is applied)
	// r, g, b: normalized R, G, B components of color to inject
	// speed2: square of speed (dx*dx + dy*dy) if you already know it then pass it in to save having it calculated again. leave blank to have it calculated in the function
	void addAtPixel(int i, int j, float dx, float dy, float generateMult, float velocityMult, float r, float g, float b, float speed2 = -1);

	// set viscocity, it will lerp to the target at lerpspeed
	void setVisc(float newVisc, float lerpSpeed = 0.05); 
	
	// returns current viscocity
	float getVisc();
	
	// returns average density of fluid 
	float getAvgDensity();
	
	// returns average uniformity
	float getUniformity();
		
protected:
	
	int _NX, _NY, _size;
	float _invNX, _invNY;
	float _dt;

	float _visc, _viscLerpSpeed, _targetVisc;
	float _fadeSpeed;
	
	float *_tmp;

	float *_r, *_rOld;
	float *_g, *_gOld;
	float *_b, *_bOld;
	float *_d;				// density is simply maximum of r, g and b

	float *_u, *_uOld;
	float *_v, *_vOld;
	float *_curl;

	float _avgDensity;			// this will hold the average color of the last frame (how full it is)
	float _uniformity;			// this will hold the uniformity of the last frame (how uniform the color is);
		
	FluidSolver();
	~FluidSolver();
	
	void init(int NX, int NY, float dt, float visc, float fadeSpeed);
	void _reset();
	void destroy();

	float calcCurl(int i, int j);
	void vorticityConfinement(float *Fvc_x, float *Fvc_y);
	void solve();
	void addSource(float *x, float *x0);
	void addSourceUV();		// does both U and V in one go
	void addSourceRGB();	// does R, G, and B in one go
	
	void advect(int b, float *d, float *d0, float *du, float *dv);
	void advectRGB(int b, float *du, float *dv);
	
	void diffuse(int b, float *c, float *c0, float diff);
	void diffuseRGB(int b, float diff);
	void diffuseUV(int b, float diff);

	void project(float *x, float *y, float *p, float *div);
	void linearSolver(int b, float *x, float *x0, float a, float c);
	void linearSolverRGB(int b, float a, float c);
	void linearSolverUV(int b, float a, float c);

	void setBoundry(int b, float *x);
	void setBoundryRGB(int b);
	
	void swapU(); 
	void swapV(); 
	void swapRGB();
};

