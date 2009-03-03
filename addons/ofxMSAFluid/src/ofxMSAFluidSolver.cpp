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

#include "ofxMSAFluidSolver.h"

#define FLUID_CONDENSED_LOOPS				// doing a lot of the iterations in the same loop is quite faster...

//#define __DO_vorticityConfinement	// I think the fluid looks better without this (at least for optical flow), so disable this to not do it

#ifdef FLUID_CONDENSED_LOOPS
#define ADD_SOURCE_UV		addSourceUV();
#define ADD_SOURCE_RGB		addSourceRGB();
#define DIFFUSE_RGB			diffuseRGB(0, 0);
#define ADVECT_RGB			advectRGB(0, _u, _v);
#define DIFFUSE_UV			diffuseUV(0, _visc);
#else	
#define ADD_SOURCE_UV		addSource(_u, _uOld);	addSource(_v, _vOld);
#define ADD_SOURCE_RGB		addSource(_r, _rOld);	addSource(_g, _gOld);	addSource(_b, _bOld);
#define DIFFUSE_RGB			diffuse(0, _r, _rOld, 0);	diffuse(0, _g, _gOld, 0);	diffuse(0, _b, _bOld, 0);    
#define ADVECT_RGB			advect(0, _r, _rOld, _u, _v);	advect(0, _g, _gOld, _u, _v);	advect(0, _b, _bOld, _u, _v);
#define DIFFUSE_UV			diffuse(0, _u, _uOld, _visc);	diffuse(0, _v, _vOld, _visc);

#endif

ofxMSAFluidSolver::ofxMSAFluidSolver() {
	printf("ofxMSAFluidSolver::ofxMSAFluidSolver()\n");	
	
	_r    = 0;
	_rOld = 0;
	
	_g    = 0;
	_gOld = 0;
	
	_b    = 0;
	_bOld = 0;
	
	_u    = 0;
	_uOld = 0;
	_v    = 0;
	_vOld = 0;
	_curl = 0;
	
	_isInited = false;
}


ofxMSAFluidSolver& ofxMSAFluidSolver::setup(int NX, int NY) {
	printf("ofxMSAFluidSolver::init(%i, %i)\n", NX, NY);
	
	setDeltaT();
	setFadeSpeed();
	setSolverIterations();
	
    _NX = NX;
	_NY = NY;
	_numCells = (_NX + 2) * (_NY + 2);
	_invNumCells = 1.0f/ _numCells;
	//    reset();
	
	_invNX = 1.0f / _NX;
	_invNY = 1.0f / _NY;
	
	width		= getWidth();
	height		= getHeight();
	invWidth	= 1.0f/width;
	invHeight	= 1.0f/height;
	
	reset();
	enableRGB(false);
	return *this;
}

ofxMSAFluidSolver&  ofxMSAFluidSolver::setDeltaT(float dt) {
	_dt = dt;
	return *this;	
}

ofxMSAFluidSolver&  ofxMSAFluidSolver::setFadeSpeed(float fadeSpeed) {
	_fadeSpeed = fadeSpeed;
	return *this;	
}

ofxMSAFluidSolver&  ofxMSAFluidSolver::setSolverIterations(int solverIterations) {
	_solverIterations = solverIterations;
	return *this;	
}


// whether fluid is RGB or monochrome (if only pressure / velocity is needed no need to update 3 channels)
ofxMSAFluidSolver&  ofxMSAFluidSolver::enableRGB(bool isRGB) {
	_isRGB = isRGB;
	return *this;
}


bool ofxMSAFluidSolver::isInited() {
	return _isInited;
}

ofxMSAFluidSolver::~ofxMSAFluidSolver() {
	printf("ofxMSAFluidSolver::~ofxMSAFluidSolver()\n");
	destroy();
}

void ofxMSAFluidSolver::destroy() {
	printf("ofxMSAFluidSolver::destroy()\n");
	_isInited = false;
	
	if(_r)		delete []_r;
	if(_rOld)	delete []_rOld;
	
	if(_g)		delete []_g;
	if(_gOld)	delete []_gOld;
	
	if(_b)		delete []_b;
	if(_bOld)	delete []_bOld;
	
	if(_u)		delete []_u;
	if(_uOld)	delete []_uOld;
	if(_v)		delete []_v;
	if(_vOld)	delete []_vOld;
	if(_curl)	delete []_curl;
}


void ofxMSAFluidSolver::reset() {
	printf("ofxMSAFluidSolver::reset()\n");	
	destroy();
	_isInited = true;
	
	_r    = new float[_numCells];
	_rOld = new float[_numCells];
	
	_g    = new float[_numCells];
	_gOld = new float[_numCells];
	
	_b    = new float[_numCells];
	_bOld = new float[_numCells];
	
	_u    = new float[_numCells];
	_uOld = new float[_numCells];
	_v    = new float[_numCells];
	_vOld = new float[_numCells];
	_curl = new float[_numCells];
	
	for (int i = 0; i < _numCells; i++) {
		_u[i] = _uOld[i] = _v[i] = _vOld[i] = 0.0f;
		_curl[i] = 0.0f;
		_r[i] = _rOld[i] = _g[i] = _gOld[i] = _b[i] = _bOld[i] = 0;
	}
}

// return total number of cells (_NX+2) * (_NY+2)
int ofxMSAFluidSolver::getNumCells() {
	return _numCells;
}

int ofxMSAFluidSolver::getWidth() {
	return _NX + 2;
}

int ofxMSAFluidSolver::getHeight() {
	return _NY + 2;
}


ofxMSAFluidSolver& ofxMSAFluidSolver::setVisc(float newVisc, float lerpSpeed) {
	_targetVisc = newVisc;
	_viscLerpSpeed = lerpSpeed;
	return *this;
}

// returns current viscocity
float ofxMSAFluidSolver::getVisc() {
	return _visc;
}

// returns average density of fluid 
float ofxMSAFluidSolver::getAvgDensity() {
	return _avgDensity;
}

// returns average uniformity
float ofxMSAFluidSolver::getUniformity() {
	return _uniformity;
}

float ofxMSAFluidSolver::getAvgSpeed() {
	return _avgSpeed;
}

float ofxMSAFluidSolver::calcCurl(int i, int j) {
	float du_dy = (_u[FLUID_IX(i, j + 1)] - _u[FLUID_IX(i, j - 1)]) * 0.5f;
	float dv_dx = (_v[FLUID_IX(i + 1, j)] - _v[FLUID_IX(i - 1, j)]) * 0.5f;
	
	return du_dy - dv_dx;
}

#ifdef __DO_vorticityConfinement

void ofxMSAFluidSolver::vorticityConfinement(float* Fvc_x, float* Fvc_y) {
	float dw_dx, dw_dy;
	float length;
	float _v;
	
	// Calculate magnitude of calcCurl(_u,_v) for each cell. (|w|)
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			_curl[FLUID_IX(i, j)] = fabs(calcCurl(i, j));
		}
	}
	
	for (int i = 2; i < _NX; i++) {
		for (int j = 2; j < _NY; j++) {
			
			// Find derivative of the magnitude (_N = del |w|)
			dw_dx = (_curl[FLUID_IX(i + 1, j)] - _curl[FLUID_IX(i - 1, j)]) * 0.5f;
			dw_dy = (_curl[FLUID_IX(i, j + 1)] - _curl[FLUID_IX(i, j - 1)]) * 0.5f;
			
			// Calculate vector length. (|_N|)
			// Add small factor to prevent divide by zeros.
			length = (float) sqrt(dw_dx * dw_dx + dw_dy * dw_dy) + 0.000001f;
			
			// N = ( _N/|_N| )
			dw_dx /= length;
			dw_dy /= length;
			
			_v = calcCurl(i, j);
			
			// N x w
			Fvc_x[FLUID_IX(i, j)] = dw_dy * -_v;
			Fvc_y[FLUID_IX(i, j)] = dw_dx *  _v;
		}
	}
}
#endif

void ofxMSAFluidSolver::update() {
	_visc += (_targetVisc - _visc) * _viscLerpSpeed;
	
	ADD_SOURCE_UV
	
#ifdef __DO_vorticityConfinement
	vorticityConfinement(_uOld, _vOld);
	ADD_SOURCE_UV
#endif
	
	swapU();
	swapV();
	
	DIFFUSE_UV(0, _visc);
	
	project(_u, _v, _uOld, _vOld);
	
	swapU(); 
	swapV();
	
	advect(1, _u, _uOld, _uOld, _vOld);
	advect(2, _v, _vOld, _uOld, _vOld);
	
	project(_u, _v, _uOld, _vOld);
	
	if(_isRGB) {
		ADD_SOURCE_RGB
		swapRGB();
		
		DIFFUSE_RGB
		swapRGB();
		
		ADVECT_RGB
		
		fadeRGB();
	} else {
		addSource(_r, _rOld);
		swapR();
		
		diffuse(0, _r, _rOld, 0);
		swapRGB();
		
		advect(0, _r, _rOld, _u, _v);	
		fadeR();
	}
}

void ofxMSAFluidSolver::fadeR() {
	// I want the fluid to gradually fade out so the screen doesn't fill. the amount it fades out depends on how full it is, and how uniform (i.e. boring) the fluid is...
	float holdAmount = 1 - _avgDensity * _avgDensity * _fadeSpeed;	// this is how fast the density will decay depending on how full the screen currently is
	
	_avgDensity = 0;
	_avgSpeed = 0;
	
	float totalDeviations = 0;
	float currentDeviation;
	//	float uniformityMult = _uniformity * 0.05f;
	
	_avgSpeed = 0;
	for (int i = 0; i < _numCells; i++) {
		// clear old values
		_uOld[i] = _vOld[i] = 0; 
		_rOld[i] = 0;
		//		_gOld[i] = _bOld[i] = 0;
		
		// calc avg speed
		_avgSpeed += _u[i] * _u[i] + _v[i] * _v[i];
		
		// calc avg density
		_r[i] = MIN(1.0f, _r[i]);
		//		_g[i] = MIN(1.0f, _g[i]);
		//		_b[i] = MIN(1.0f, _b[i]);
		//		float density = MAX(_r[i], MAX(_g[i], _b[i]));
		float density = _r[i];
		_avgDensity += density;	// add it up
		
		// calc deviation (for uniformity)
		currentDeviation = density - _avgDensity;
		totalDeviations += currentDeviation * currentDeviation;
		
		// fade out old
		_r[i] *= holdAmount;
//		_r[i] *= _fadeSpeed;
	}
	_avgDensity *= _invNumCells;
	//	_avgSpeed *= _invNumCells;
	
	//	printf("%.3f\n", _avgSpeed);
	_uniformity = 1.0f / (1 + totalDeviations * _invNumCells);		// 0: very wide distribution, 1: very uniform
}


void ofxMSAFluidSolver::fadeRGB() {
	// I want the fluid to gradually fade out so the screen doesn't fill. the amount it fades out depends on how full it is, and how uniform (i.e. boring) the fluid is...
	float holdAmount = 1 - _avgDensity * _avgDensity * _fadeSpeed;	// this is how fast the density will decay depending on how full the screen currently is
	
	_avgDensity = 0;
	_avgSpeed = 0;
	
	float totalDeviations = 0;
	float currentDeviation;
	//	float uniformityMult = _uniformity * 0.05f;
	
	_avgSpeed = 0;
	for (int i = 0; i < _numCells; i++) {
		// clear old values
		_uOld[i] = _vOld[i] = 0; 
		_rOld[i] = 0;
		_gOld[i] = _bOld[i] = 0;
		
		// calc avg speed
		_avgSpeed += _u[i] * _u[i] + _v[i] * _v[i];
		
		// calc avg density
		_r[i] = MIN(1.0f, _r[i]);
		_g[i] = MIN(1.0f, _g[i]);
		_b[i] = MIN(1.0f, _b[i]);
		float density = MAX(_r[i], MAX(_g[i], _b[i]));
		//float density = _r[i];
		_avgDensity += density;	// add it up
		
		// calc deviation (for uniformity)
		currentDeviation = density - _avgDensity;
		totalDeviations += currentDeviation * currentDeviation;
		
		// fade out old
		_r[i] *= holdAmount;
		_g[i] *= holdAmount;
		_b[i] *= holdAmount;

	}
	_avgDensity *= _invNumCells;
	_avgSpeed *= _invNumCells;
	
	//printf("%.3f\n", _avgDensity);
	_uniformity = 1.0f / (1 + totalDeviations * _invNumCells);		// 0: very wide distribution, 1: very uniform
}


void ofxMSAFluidSolver::addSourceUV() {
	for (int i = 0; i < _numCells; i++) {
		_u[i] += _dt * _uOld[i];
		_v[i] += _dt * _vOld[i];
	}
}

void ofxMSAFluidSolver::addSourceRGB() {
	for (int i = 0; i < _numCells; i++) {
		_r[i] += _dt * _rOld[i];
		_g[i] += _dt * _gOld[i];
		_b[i] += _dt * _bOld[i];		
	}
}



void ofxMSAFluidSolver::addSource(float* x, float* x0) {
	for (int i = 0; i < _numCells; i++) {
		x[i] += _dt * x0[i];
	}
}


void ofxMSAFluidSolver::advect(int _b, float* _d, float* d0, float* du, float* dv) {
	int i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;
	
	dt0 = _dt * _NX;
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x = i - dt0 * du[FLUID_IX(i, j)];
			y = j - dt0 * dv[FLUID_IX(i, j)];
			
			if (x > _NX + 0.5) x = _NX + 0.5f;
			if (x < 0.5)     x = 0.5f;
			
			i0 = (int) x;
			i1 = i0 + 1;
			
			if (y > _NY + 0.5) y = _NY + 0.5f;
			if (y < 0.5)     y = 0.5f;
			
			j0 = (int) y;
			j1 = j0 + 1;
			
			s1 = x - i0;
			s0 = 1 - s1;
			t1 = y - j0;
			t0 = 1 - t1;
			
			_d[FLUID_IX(i, j)] = s0 * (t0 * d0[FLUID_IX(i0, j0)] + t1 * d0[FLUID_IX(i0, j1)])
			+ s1 * (t0 * d0[FLUID_IX(i1, j0)] + t1 * d0[FLUID_IX(i1, j1)]);
			
		}
	}
	setBoundry(_b, _d);
}

void ofxMSAFluidSolver::advectRGB(int _bound, float* du, float* dv) {
	int i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;
	
	dt0 = _dt * _NX;
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x = i - dt0 * du[FLUID_IX(i, j)];
			y = j - dt0 * dv[FLUID_IX(i, j)];
			
			if (x > _NX + 0.5) x = _NX + 0.5f;
			if (x < 0.5)     x = 0.5f;
			
			i0 = (int) x;
			i1 = i0 + 1;
			
			if (y > _NY + 0.5) y = _NY + 0.5f;
			if (y < 0.5)     y = 0.5f;
			
			j0 = (int) y;
			j1 = j0 + 1;
			
			s1 = x - i0;
			s0 = 1 - s1;
			t1 = y - j0;
			t0 = 1 - t1;
			
			_r[FLUID_IX(i, j)] = s0 * (t0 * _rOld[FLUID_IX(i0, j0)] + t1 * _rOld[FLUID_IX(i0, j1)])	+ s1 * (t0 * _rOld[FLUID_IX(i1, j0)] + t1 * _rOld[FLUID_IX(i1, j1)]);
			_g[FLUID_IX(i, j)] = s0 * (t0 * _gOld[FLUID_IX(i0, j0)] + t1 * _gOld[FLUID_IX(i0, j1)])	+ s1 * (t0 * _gOld[FLUID_IX(i1, j0)] + t1 * _gOld[FLUID_IX(i1, j1)]);			
			_b[FLUID_IX(i, j)] = s0 * (t0 * _bOld[FLUID_IX(i0, j0)] + t1 * _bOld[FLUID_IX(i0, j1)])	+ s1 * (t0 * _bOld[FLUID_IX(i1, j0)] + t1 * _bOld[FLUID_IX(i1, j1)]);				
		}
	}
	setBoundryRGB(_bound);
}



void ofxMSAFluidSolver::diffuse(int _b, float* c, float* c0, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolver(_b, c, c0, a, 1.0 + 4 * a);
}

void ofxMSAFluidSolver::diffuseRGB(int _b, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolverRGB(_b, a, 1.0 + 4 * a);
}

void ofxMSAFluidSolver::diffuseUV(int _b, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolverUV(_b, a, 1.0 + 4 * a);
}


void ofxMSAFluidSolver::project(float* x, float* y, float* p, float* div)  {
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			div[FLUID_IX(i, j)] = (x[FLUID_IX(i+1, j)] - x[FLUID_IX(i-1, j)] + y[FLUID_IX(i, j+1)] - y[FLUID_IX(i, j-1)])
			* - 0.5f / _NX;
			p[FLUID_IX(i, j)] = 0;
		}
	}
	
	setBoundry(0, div);
	setBoundry(0, p);
	
	linearSolver(0, p, div, 1, 4);
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x[FLUID_IX(i, j)] -= 0.5f * _NX * (p[FLUID_IX(i+1, j)] - p[FLUID_IX(i-1, j)]);
			y[FLUID_IX(i, j)] -= 0.5f * _NX * (p[FLUID_IX(i, j+1)] - p[FLUID_IX(i, j-1)]);
		}
	}
	
	setBoundry(1, x);
	setBoundry(2, y);
}



void ofxMSAFluidSolver::linearSolver(int _b, float* x, float* x0, float a, float c) {
	for (int k = 0; k < _solverIterations; k++) {
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				x[FLUID_IX(i, j)] = (a * ( x[FLUID_IX(i-1, j)] + x[FLUID_IX(i+1, j)]  +   x[FLUID_IX(i, j-1)] + x[FLUID_IX(i, j+1)])  +  x0[FLUID_IX(i, j)]) / c;
			}
		}
		setBoundry(_b, x);
	}
}

//#define LINEAR_SOLVE_EQ	(x, x0)			(a * ( x[] + x[]  +  x[] + x[])  +  x0[]) / c;

void ofxMSAFluidSolver::linearSolverRGB(int _bound, float a, float c) {
	int index1, index2, index3, index4, index5;
	for (int k = 0; k < _solverIterations; k++) {		// MEMO
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				index5 = FLUID_IX(i, j);
				index1 = index5 - 1;//FLUID_IX(i-1, j);
				index2 = index5 + 1;//FLUID_IX(i+1, j);
				index3 = index5 - (_NX + 2);//FLUID_IX(i, j-1);
				index4 = index5 + (_NX + 2);//FLUID_IX(i, j+1);
				
				_r[index5] = (a * ( _r[index1] + _r[index2]  +  _r[index3] + _r[index4])  +  _rOld[index5]) / c;
				_g[index5] = (a * ( _g[index1] + _g[index2]  +  _g[index3] + _g[index4])  +  _gOld[index5]) / c;
				_b[index5] = (a * ( _b[index1] + _b[index2]  +  _b[index3] + _b[index4])  +  _bOld[index5]) / c;				
				//				x[FLUID_IX(i, j)] = (a * ( x[FLUID_IX(i-1, j)] + x[FLUID_IX(i+1, j)]  +  x[FLUID_IX(i, j-1)] + x[FLUID_IX(i, j+1)])  +  x0[FLUID_IX(i, j)]) / c;
			}
		}
		setBoundryRGB(_bound);
	}
}

void ofxMSAFluidSolver::linearSolverUV(int _bound, float a, float c) {
	int index1, index2, index3, index4, index5;
	for (int k = 0; k < _solverIterations; k++) {		// MEMO
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				index5 = FLUID_IX(i, j);
				index1 = index5 - 1;//FLUID_IX(i-1, j);
				index2 = index5 + 1;//FLUID_IX(i+1, j);
				index3 = index5 - (_NX + 2);//FLUID_IX(i, j-1);
				index4 = index5 + (_NX + 2);//FLUID_IX(i, j+1);
				
				_u[index5] = (a * ( _u[index1] + _u[index2]  +  _u[index3] + _u[index4])  +  _uOld[index5]) / c;
				_v[index5] = (a * ( _v[index1] + _v[index2]  +  _v[index3] + _v[index4])  +  _vOld[index5]) / c;
				//				x[FLUID_IX(i, j)] = (a * ( x[FLUID_IX(i-1, j)] + x[FLUID_IX(i+1, j)]  +  x[FLUID_IX(i, j-1)] + x[FLUID_IX(i, j+1)])  +  x0[FLUID_IX(i, j)]) / c;
			}
		}
		setBoundryRGB(_bound);
	}
}



// specifies simple boundry conditions.
void ofxMSAFluidSolver::setBoundry(int _b, float* x) {
	//return;
	for (int i = 1; i <= _NX; i++) {
		if(i<= _NY) {
			x[FLUID_IX(  0, i  )] = _b == 1 ? -x[FLUID_IX(_NX, i)] : x[FLUID_IX(_NX, i)];
			x[FLUID_IX(_NX+1, i  )] = _b == 1 ? -x[FLUID_IX(1, i)] : x[FLUID_IX(1, i)];
		}
		
		x[FLUID_IX(  i, 0  )] = _b == 2 ? -x[FLUID_IX(i, 1)] : x[FLUID_IX(i, 1)];
		x[FLUID_IX(  i, _NY+1)] = _b == 2 ? -x[FLUID_IX(i, _NY)] : x[FLUID_IX(i, _NY)];
	}
	
	x[FLUID_IX(  0,   0)] = 0.5f * (x[FLUID_IX(1, 0  )] + x[FLUID_IX(  0, 1)]);
	x[FLUID_IX(  0, _NY+1)] = 0.5f * (x[FLUID_IX(1, _NY+1)] + x[FLUID_IX(  0, _NY)]);
	x[FLUID_IX(_NX+1,   0)] = 0.5f * (x[FLUID_IX(_NX, 0  )] + x[FLUID_IX(_NX+1, 1)]);
	x[FLUID_IX(_NX+1, _NY+1)] = 0.5f * (x[FLUID_IX(_NX, _NY+1)] + x[FLUID_IX(_NX+1, _NY)]);
}

// specifies simple boundry conditions.
void ofxMSAFluidSolver::setBoundryRGB(int _bound) {
	int index1, index2;
	for (int i = 1; i <= _NX; i++) {
		if(i<= _NY) {
			index1 = FLUID_IX(0, i);
			index2 = FLUID_IX(_NX, i);
			_r[index1] = _bound == 1 ? -_r[index2] : _r[index2];
			_g[index1] = _bound == 1 ? -_g[index2] : _g[index2];
			_b[index1] = _bound == 1 ? -_b[index2] : _b[index2];
			
			index1 = FLUID_IX(_NX+1, i );
			index2 = FLUID_IX(1, i);
			_r[index1] = _bound == 1 ? -_r[index2] : _r[index2];
			_g[index1] = _bound == 1 ? -_g[index2] : _g[index2];
			_b[index1] = _bound == 1 ? -_b[index2] : _b[index2];
		}
		
		index1 = FLUID_IX(i, 0);
		index2 = FLUID_IX(i, 1);
		_r[index1] = _bound == 2 ? -_r[index2] : _r[index2];
		_g[index1] = _bound == 2 ? -_g[index2] : _g[index2];
		_b[index1] = _bound == 2 ? -_b[index2] : _b[index2];
		
		index1 = FLUID_IX(i, _NY+1);
		index2 = FLUID_IX(i, _NY);
		_r[index1] = _bound == 2 ? -_r[index2] : _r[index2];
		_g[index1] = _bound == 2 ? -_g[index2] : _g[index2];
		_b[index1] = _bound == 2 ? -_b[index2] : _b[index2];
		
	}
	
	//	x[FLUID_IX(  0,   0)] = 0.5f * (x[FLUID_IX(1, 0  )] + x[FLUID_IX(  0, 1)]);
	//	x[FLUID_IX(  0, _NY+1)] = 0.5f * (x[FLUID_IX(1, _NY+1)] + x[FLUID_IX(  0, _NY)]);
	//	x[FLUID_IX(_NX+1,   0)] = 0.5f * (x[FLUID_IX(_NX, 0  )] + x[FLUID_IX(_NX+1, 1)]);
	//	x[FLUID_IX(_NX+1, _NY+1)] = 0.5f * (x[FLUID_IX(_NX, _NY+1)] + x[FLUID_IX(_NX+1, _NY)]);
	
}


void ofxMSAFluidSolver::swapU() { 
	_tmp = _u; 
	_u = _uOld; 
	_uOld = _tmp; 
}
void ofxMSAFluidSolver::swapV(){ 
	_tmp = _v; 
	_v = _vOld; 
	_vOld = _tmp; 
}
void ofxMSAFluidSolver::swapR(){ 
	_tmp = _r;
	_r = _rOld;
	_rOld = _tmp;
}

void ofxMSAFluidSolver::swapRGB(){ 
	_tmp = _r;
	_r = _rOld;
	_rOld = _tmp;
	
	_tmp = _g;
	_g = _gOld;
	_gOld = _tmp;
	
	_tmp = _b;
	_b = _bOld;
	_bOld = _tmp;
}


// get index for normalized position
int ofxMSAFluidSolver::fluidIndex(float x, float y) {
	return 0;
	// TODO
}



void ofxMSAFluidSolver::getInfoAtPos(float x, float y, ofPoint *vel, ofPoint *color) {
	int i= (int)(x * (_NX+2));
	int j= (int)(y * (_NY+2));
	getInfoAtCell(i, j, vel, color);
}

void ofxMSAFluidSolver::getInfoAtCell(int i, int j,  ofPoint *vel, ofPoint *color) {
	if(i<0) i = 0; else if(i > _NX+1) i = _NX+1;
	if(j<0) j = 0; else if(j > _NY+1) j = _NY+1;
	getInfoAtCell(FLUID_IX(i, j), vel, color);
}


void ofxMSAFluidSolver::getInfoAtCell(int i,  ofPoint *vel, ofPoint *color) {
	//	if(safeToRun()){
	if(vel) vel->set(_u[i] * _invNX, _v[i] * _invNY);
	if(color) {
		if(_isRGB) color->set(_r[i], _g[i], _b[i]);
		else color->set(_r[i], _r[i], _r[i]);
	}
	//		unlock();
	//	}
}



void ofxMSAFluidSolver::addForceAtPos(float x, float y, float vx, float vy) {
	int i = (int) (x * _NX + 1);
	int j = (int) (y * _NY + 1);
	if(i<0 || i>_NX+1 || j<0 || j>_NY+1) return;
	addForceAtCell(i, j, vx, vy);
}

void ofxMSAFluidSolver::addForceAtCell(int i, int j, float vx, float vy) {
	//	if(safeToRun()){
	int index = FLUID_IX(i, j);
	_uOld[index] += vx * _NX;
	_vOld[index] += vy * _NY;
	//		unlock();
	//	}
}


void ofxMSAFluidSolver::addColorAtPos(float x, float y, float r, float g, float b) {
	int i = (int) (x * _NX + 1);
	int j = (int) (y * _NY + 1);
	if(i<0 || i>_NX+1 || j<0 || j>_NY+1) return;
	addColorAtCell(i, j, r, g, b);	
}

void ofxMSAFluidSolver::addColorAtCell(int i, int j, float r, float g, float b) {
	//	if(safeToRun()){
	int index = FLUID_IX(i, j);
	_rOld[index] += r;
	if(_isRGB) {
		_gOld[index] += g;
		_bOld[index] += b;
	}
	//		unlock();
	//	}
}


void ofxMSAFluidSolver::randomizeColor() {
	for(int i=0; i< getWidth(); i++) {
		for(int j=0; j< getHeight(); j++) {
			int index = FLUID_IX(i, j);
			_r[index] = _rOld[index] = ofRandom(0, 1);
			if(_isRGB) {
				_g[index] = _gOld[index] = ofRandom(0, 1);
				_b[index] = _bOld[index] = ofRandom(0, 1);
			}
		} 
	}
}

/*
 // add force to normalized x, y,  coordinates
 void ofxMSAFluidSolver::addAtCell(float x, float y, float dx, float dy, float generateMult, float r, float g, float b, float speed2) {
 int i = (int) (x * _NX + 1);
 int j = (int) (y * _NY + 1);
 
 if(i<0 || i>_NX+1 || j<0 || j>_NY+1) return;		
 addAtCell(i, j, dx, dy, generateMult, velocityMult, r, g, b, speed2);
 }
 
 
 // add force to x, y fluid coordinates
 void ofxMSAFluidSolver::addAtCell(int i, int j, float dx, float dy, float generateMult, float r, float g, float b, float speed2) {
 if(speed2 < 0) speed2 = dx * dx + dy * dy;
 if(speed2 > 0.0f) {
 int index = FLUID_IX(i, j);
 
 if(generateMult > 0) {
 float speedMult = 1.0f/255.0f * speed2 * speed2 * generateMult;
 _rOld[index] += speedMult * r;
 _gOld[index] += speedMult * g;
 _bOld[index] += speedMult * b;
 }
 _uOld[index] += dx * velocityMult;
 _vOld[index] += dy * velocityMult;
 
 }
 }
 
 */




