/***********************************************************************
 
 This class solves a fluid system based on the classic Jos Stam paper I'm sure you've heard about :P
 http://www.dgp.toronto.edu/people/stam/reality/Research/pdf/GDC03.pdf
 
 also had help from this site (though its in 3D, so simplied it a bit)
 http://www.mikeash.com/?page=pyblog/fluid-simulation-for-dummies.html
 
 
 In addition to the features in the Jos Stam paper, this class allows you to add colored dye and force at (x,y) coordinates using the addAt....() functions
 Also use the getInfoAtCell() function to read velocity and density at any coordinates in the fluid so you can feed it to a particle system or something
 
 
 /***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
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


// do not change these values, you can override them using the solver methods
#define		FLUID_DEFAULT_NX					100
#define		FLUID_DEFAULT_NY					100
#define		FLUID_DEFAULT_DT					1.0f
#define		FLUID_DEFAULT_VISC					0.0001f
#define		FLUID_DEFAULT_FADESPEED				0
#define		FLUID_DEFAULT_SOLVER_ITERATIONS		10


#define		FLUID_IX(i, j)		((i) + (_NX + 2)  *(j))


class ofxMSAFluidSolver : public ofBaseUpdates {
public:	
	
	ofxMSAFluidSolver();
	virtual ~ofxMSAFluidSolver();
	
	ofxMSAFluidSolver& setup(int NX = FLUID_DEFAULT_NX, int NY = FLUID_DEFAULT_NY);
	
	// solve one step of the fluid solver
	void update();
	
	// clear all forces in fluid and reset
	void reset();	
	
	// get index for normalized position
	int fluidIndex(float x, float y);
	
	// get color and/vel at any point in the fluid.
	// pass pointers to ofPoint (for velocity) and ofPoint (for color) and they get filled with the info
	// leave any pointer NULL if you don't want that info
	
	// get info at normalized (x, y) coordinates. range :(0..1), (0..1)
	void getInfoAtPos(float x, float y, ofPoint *vel, ofPoint *color = NULL);
	
	// get info at fluid cell pixels (i, j) if you know it. range: (0..NX-1), (0..NY-1)
	void getInfoAtCell(int i, int j,  ofPoint *vel, ofPoint *color = NULL);
	
	// get info at fluid cell index if you know it. range: (0..numCells)
	void getInfoAtCell(int index,  ofPoint *vel, ofPoint *color = NULL);
	
	
	// add force at normalized (x, y) coordinates
	// vx: horizontal velocity
	// vy: vertical velocity
	void addForceAtPos(float x, float y, float vx, float vy);
	
	// add force at (i, j) fluid cell coordinates
	// vx: horizontal velocity
	// vy: vertical velocity
	void addForceAtCell(int i, int j, float vx, float vy);

	// add color at normalized (x, y) coordinates
	// r, g, b: normalized R, G, B components of color to inject
	// for monochrome, g & b are ignore, only r is used
	void addColorAtPos(float x, float y, float r, float g=0, float b=0);
	
	// add color and force at (i, j) fluid cell coordinates
	// r, g, b: normalized R, G, B components of color to inject
	// for monochrome, g & b are ignore, only r is used
	void addColorAtCell(int i, int j, float r, float g=0, float b=0);
	
	// fill with random color at every cell
	void randomizeColor();
	
	
	// return number of cells and dimensions
	int getNumCells();
	int getWidth();
	int getHeight();
	
	bool isInited();
	
	// accessors for  viscocity, it will lerp to the target at lerpspeed
	ofxMSAFluidSolver& setVisc(float newVisc, float lerpSpeed = 0.05); 
	float getVisc();

	ofxMSAFluidSolver& enableRGB(bool isRGB);
	ofxMSAFluidSolver& setDeltaT(float dt = FLUID_DEFAULT_DT);
	ofxMSAFluidSolver& setFadeSpeed(float fadeSpeed = FLUID_DEFAULT_FADESPEED);
	ofxMSAFluidSolver& setSolverIterations(int solverIterations = FLUID_DEFAULT_SOLVER_ITERATIONS);
	
	// returns average density of fluid 
	float getAvgDensity();
	
	// returns average uniformity
	float getUniformity();
	
	// returns average speed of fluid
	float getAvgSpeed();	
	
	
	
	
	// allocate an array large enough to hold information for u, v, r, g, OR b
	float* alloc()	{ return new float[_numCells];	}
	
//	void copyU(float *p)	{ if(lock()) { memcpy(p, _u, sizeof(float) * _numCells); unlock(); }}
//	void copyV(float *p)	{ if(lock()) { memcpy(p, _v, sizeof(float) * _numCells); unlock(); }}
//	void copyR(float *p)	{ if(lock()) { memcpy(p, _r, sizeof(float) * _numCells); unlock(); }}
//	void copyG(float *p)	{ if(lock()) { memcpy(p, _g, sizeof(float) * _numCells); unlock(); }}
//	void copyB(float *p)	{ if(lock()) { memcpy(p, _b, sizeof(float) * _numCells); unlock(); }}
	
	float* getU()			{ return _u; }
	float* getV()			{ return _v; }
	float* getR()			{ return _r; }
	float* getG()			{ return _g; }
	float* getB()			{ return _b; }
	
	float width;
	float height;
	float invWidth;
	float invHeight;
	
protected:
	
	int		_NX, _NY, _numCells;
	float	_invNX, _invNY, _invNumCells;
	float	_dt;
	bool	_isInited;
	bool	_isRGB;				// for monochrome, only update _r
	int		_solverIterations;

	float	_visc, _viscLerpSpeed, _targetVisc;
	float	_fadeSpeed;
	
	float	*_tmp;

	float	*_r, *_rOld;
	float	*_g, *_gOld;
	float	*_b, *_bOld;

	float	*_u, *_uOld;
	float	*_v, *_vOld;
	float	*_curl;

	float	_avgDensity;			// this will hold the average color of the last frame (how full it is)
	float	_uniformity;			// this will hold the uniformity of the last frame (how uniform the color is);
	float	_avgSpeed;

	void	destroy();

	float	calcCurl(int i, int j);
	void	vorticityConfinement(float *Fvc_x, float *Fvc_y);

	void	addSource(float *x, float *x0);
	void	addSourceUV();		// does both U and V in one go
	void	addSourceRGB();	// does R, G, and B in one go
	
	void	advect(int b, float *d, float *d0, float *du, float *dv);
	void	advectRGB(int b, float *du, float *dv);
	
	void	diffuse(int b, float *c, float *c0, float diff);
	void	diffuseRGB(int b, float diff);
	void	diffuseUV(int b, float diff);

	void	project(float *x, float *y, float *p, float *div);
	void	linearSolver(int b, float *x, float *x0, float a, float c);
	void	linearSolverRGB(int b, float a, float c);
	void	linearSolverUV(int b, float a, float c);

	void	setBoundry(int b, float *x);
	void	setBoundryRGB(int b);
	
	void	swapU(); 
	void	swapV(); 
	void	swapR();
	void	swapRGB();
	
	void	fadeR();
	void	fadeRGB();
/*	
	bool lock() {
		return true;
	}
	
	void unlock() {
	}
	
	bool safeToRun() {
		return true;
	}
 */
};

