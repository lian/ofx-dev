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

#include "FluidSolver.h"

#define __CONDENSED__				// doing a lot of the iterations in the same loop is quite faster...

//#define __DO_vorticityConfinement	// i think I think the fluid looks better without this (at least for optical flow), so disable this to not do it


#ifdef __CONDENSED__
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

FluidSolver::FluidSolver() {
	_d    = 0;
	
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
}


void FluidSolver::init(int NX, int NY, float dt, float visc, float fadeSpeed) {
	_targetVisc = _visc = visc;
	_fadeSpeed = fadeSpeed;
	
    _NX = NX;
	_NY = NY;
    _dt = dt;
	_size = (_NX + 2) * (_NY + 2);
    _reset();
	
	_invNX = 1.0f / _NX;
	_invNY = 1.0f / _NY;
}

FluidSolver::~FluidSolver() {
	destroy();
}

void FluidSolver::destroy() {
	if(_d)		delete _d;
	
	if(_r)		delete _r;
	if(_rOld)	delete _rOld;
	
	if(_g)		delete _g;
	if(_gOld)	delete _gOld;
	
	if(_b)		delete _b;
	if(_bOld)	delete _bOld;
	
	if(_u)		delete _u;
	if(_uOld)	delete _uOld;
	if(_v)		delete _v;
	if(_vOld)	delete _vOld;
	if(_curl)	delete _curl;
}


void FluidSolver::_reset() {
	destroy();
	
	_d    = new float[_size];
	
	_r    = new float[_size];
	_rOld = new float[_size];
	
	_g    = new float[_size];
	_gOld = new float[_size];
	
	_b    = new float[_size];
	_bOld = new float[_size];
	
	_u    = new float[_size];
	_uOld = new float[_size];
	_v    = new float[_size];
	_vOld = new float[_size];
	_curl = new float[_size];
	
	for (int i = 0; i < _size; i++) {
		_u[i] = _uOld[i] = _v[i] = _vOld[i] = 0.0f;
		_curl[i] = 0.0f;
		_d[i] = _r[i] = _rOld[i] = _g[i] = _gOld[i] = _b[i] = _bOld[i] = 0;
	}
}



void FluidSolver::setVisc(float newVisc, float lerpSpeed) {
	_targetVisc = newVisc;
	_viscLerpSpeed = lerpSpeed;
}

// returns current viscocity
float FluidSolver::getVisc() {
	return _visc;
}

// returns average density of fluid 
float FluidSolver::getAvgDensity() {
	return _avgDensity;
}

// returns average uniformity
float FluidSolver::getUniformity() {
	return _uniformity;
}


float FluidSolver::calcCurl(int i, int j) {
	float du_dy = (_u[IX(i, j + 1)] - _u[IX(i, j - 1)]) * 0.5f;
	float dv_dx = (_v[IX(i + 1, j)] - _v[IX(i - 1, j)]) * 0.5f;
	
	return du_dy - dv_dx;
}

#ifdef __DO_vorticityConfinement

void FluidSolver::vorticityConfinement(float* Fvc_x, float* Fvc_y) {
	float dw_dx, dw_dy;
	float length;
	float _v;
	
	// Calculate magnitude of calcCurl(_u,_v) for each cell. (|w|)
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			_curl[IX(i, j)] = fabs(calcCurl(i, j));
		}
	}
	
	for (int i = 2; i < _NX; i++) {
		for (int j = 2; j < _NY; j++) {
			
			// Find derivative of the magnitude (_N = del |w|)
			dw_dx = (_curl[IX(i + 1, j)] - _curl[IX(i - 1, j)]) * 0.5f;
			dw_dy = (_curl[IX(i, j + 1)] - _curl[IX(i, j - 1)]) * 0.5f;
			
			// Calculate vector length. (|_N|)
			// Add small factor to prevent divide by zeros.
			length = (float) sqrt(dw_dx * dw_dx + dw_dy * dw_dy) + 0.000001f;
			
			// N = ( _N/|_N| )
			dw_dx /= length;
			dw_dy /= length;
			
			_v = calcCurl(i, j);
			
			// N x w
			Fvc_x[IX(i, j)] = dw_dy * -_v;
			Fvc_y[IX(i, j)] = dw_dx *  _v;
		}
	}
}
#endif

void FluidSolver::solve() {

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
	
	ADD_SOURCE_RGB
	swapRGB();

	DIFFUSE_RGB
	swapRGB();

	ADVECT_RGB

	
	// I want the fluid to gradually fade out so the screen doesn't fill. the amount it fades out depends on how full it is, and how uniform (i.e. boring) the fluid is...
	
	float holdAmount = 1 - _avgDensity * _avgDensity * _fadeSpeed;	// this is how fast the density will decay depending on how full the screen currently is
	
	float totalColor = 0;
	float totalDeviations = 0;
	float currentDeviation;
	float uniformityMult = _uniformity * 0.05f;
	
	for (int i = 0; i < _size; i++) {
		_uOld[i] = _vOld[i] = 0; 
		_rOld[i] = _gOld[i] = _bOld[i] = 0;
		
		_r[i] = MIN(1.0f, _r[i]);
		_g[i] = MIN(1.0f, _g[i]);
		_b[i] = MIN(1.0f, _b[i]);
		
		_d[i] = MAX(_r[i], MAX(_g[i], _b[i]));
		totalColor += _d[i];	// add it up

		currentDeviation =  _d[i] - _avgDensity;
		totalDeviations += currentDeviation * currentDeviation;

		
		_r[i] *= holdAmount * ofRandom(1 - uniformityMult, 1.0f);
		_g[i] *= holdAmount * ofRandom(1 - uniformityMult, 1.0f);
		_b[i] *= holdAmount * ofRandom(1 - uniformityMult, 1.0f);
	}
	_avgDensity = totalColor / _size;
	_uniformity = 1.0f / (1 + totalDeviations / _size);		// 0: very wide distribution, 1: very uniform
}


void FluidSolver::addSourceUV() {
	for (int i = 0; i < _size; i++) {
		_u[i] += _dt * _uOld[i];
		_v[i] += _dt * _vOld[i];
	}
}

void FluidSolver::addSourceRGB() {
	for (int i = 0; i < _size; i++) {
		_r[i] += _dt * _rOld[i];
		_g[i] += _dt * _gOld[i];
		_b[i] += _dt * _bOld[i];		
	}
}



void FluidSolver::addSource(float* x, float* x0) {
	for (int i = 0; i < _size; i++) {
		x[i] += _dt * x0[i];
	}
}


void FluidSolver::advect(int _b, float* _d, float* d0, float* du, float* dv) {
	int i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;
	
	dt0 = _dt * _NX;
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x = i - dt0 * du[IX(i, j)];
			y = j - dt0 * dv[IX(i, j)];

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
			
			_d[IX(i, j)] = s0 * (t0 * d0[IX(i0, j0)] + t1 * d0[IX(i0, j1)])
			+ s1 * (t0 * d0[IX(i1, j0)] + t1 * d0[IX(i1, j1)]);
			
		}
	}
	setBoundry(_b, _d);
}

void FluidSolver::advectRGB(int _bound, float* du, float* dv) {
	int i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;
	
	dt0 = _dt * _NX;
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x = i - dt0 * du[IX(i, j)];
			y = j - dt0 * dv[IX(i, j)];
			
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
			
			_r[IX(i, j)] = s0 * (t0 * _rOld[IX(i0, j0)] + t1 * _rOld[IX(i0, j1)])	+ s1 * (t0 * _rOld[IX(i1, j0)] + t1 * _rOld[IX(i1, j1)]);
			_g[IX(i, j)] = s0 * (t0 * _gOld[IX(i0, j0)] + t1 * _gOld[IX(i0, j1)])	+ s1 * (t0 * _gOld[IX(i1, j0)] + t1 * _gOld[IX(i1, j1)]);			
			_b[IX(i, j)] = s0 * (t0 * _bOld[IX(i0, j0)] + t1 * _bOld[IX(i0, j1)])	+ s1 * (t0 * _bOld[IX(i1, j0)] + t1 * _bOld[IX(i1, j1)]);				
		}
	}
	setBoundryRGB(_bound);
}



void FluidSolver::diffuse(int _b, float* c, float* c0, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolver(_b, c, c0, a, 1.0 + 4 * a);
}

void FluidSolver::diffuseRGB(int _b, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolverRGB(_b, a, 1.0 + 4 * a);
}

void FluidSolver::diffuseUV(int _b, float _diff) {
	float a = _dt * _diff * _NX * _NY;
	linearSolverUV(_b, a, 1.0 + 4 * a);
}


void FluidSolver::project(float* x, float* y, float* p, float* div)  {
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			div[IX(i, j)] = (x[IX(i+1, j)] - x[IX(i-1, j)]
							+ y[IX(i, j+1)] - y[IX(i, j-1)])
			* - 0.5f / _NX;
			p[IX(i, j)] = 0;
		}
	}
	
	setBoundry(0, div);
	setBoundry(0, p);
	
	linearSolver(0, p, div, 1, 4);
	
	for (int i = 1; i <= _NX; i++) {
		for (int j = 1; j <= _NY; j++) {
			x[IX(i, j)] -= 0.5f * _NX * (p[IX(i+1, j)] - p[IX(i-1, j)]);
			y[IX(i, j)] -= 0.5f * _NX * (p[IX(i, j+1)] - p[IX(i, j-1)]);
		}
	}
	
	setBoundry(1, x);
	setBoundry(2, y);
}



void FluidSolver::linearSolver(int _b, float* x, float* x0, float a, float c) {
	for (int k = 0; k < 30; k++) {
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				x[IX(i, j)] = (a * ( x[IX(i-1, j)] + x[IX(i+1, j)]  +   x[IX(i, j-1)] + x[IX(i, j+1)])  +  x0[IX(i, j)]) / c;
			}
		}
		setBoundry(_b, x);
	}
}

//#define LINEAR_SOLVE_EQ	(x, x0)			(a * ( x[] + x[]  +  x[] + x[])  +  x0[]) / c;

void FluidSolver::linearSolverRGB(int _bound, float a, float c) {
	int index1, index2, index3, index4, index5;
	for (int k = 0; k < 1; k++) {
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				index5 = IX(i, j);
				index1 = index5 - 1;//IX(i-1, j);
				index2 = index5 + 1;//IX(i+1, j);
				index3 = index5 - (_NX + 2);//IX(i, j-1);
				index4 = index5 + (_NX + 2);//IX(i, j+1);

				_r[index5] = (a * ( _r[index1] + _r[index2]  +  _r[index3] + _r[index4])  +  _rOld[index5]) / c;
				_g[index5] = (a * ( _g[index1] + _g[index2]  +  _g[index3] + _g[index4])  +  _gOld[index5]) / c;
				_b[index5] = (a * ( _b[index1] + _b[index2]  +  _b[index3] + _b[index4])  +  _bOld[index5]) / c;				
//				x[IX(i, j)] = (a * ( x[IX(i-1, j)] + x[IX(i+1, j)]  +  x[IX(i, j-1)] + x[IX(i, j+1)])  +  x0[IX(i, j)]) / c;
			}
		}
		setBoundryRGB(_bound);
	}
}

void FluidSolver::linearSolverUV(int _bound, float a, float c) {
	int index1, index2, index3, index4, index5;
	for (int k = 0; k < 20; k++) {
		for (int i = 1; i <= _NX; i++) {
			for (int j = 1; j <= _NY; j++) {
				index5 = IX(i, j);
				index1 = index5 - 1;//IX(i-1, j);
				index2 = index5 + 1;//IX(i+1, j);
				index3 = index5 - (_NX + 2);//IX(i, j-1);
				index4 = index5 + (_NX + 2);//IX(i, j+1);

				_u[index5] = (a * ( _u[index1] + _u[index2]  +  _u[index3] + _u[index4])  +  _uOld[index5]) / c;
				_v[index5] = (a * ( _v[index1] + _v[index2]  +  _v[index3] + _v[index4])  +  _vOld[index5]) / c;
//				x[IX(i, j)] = (a * ( x[IX(i-1, j)] + x[IX(i+1, j)]  +  x[IX(i, j-1)] + x[IX(i, j+1)])  +  x0[IX(i, j)]) / c;
			}
		}
		setBoundryRGB(_bound);
	}
}



// specifies simple boundry conditions.
void FluidSolver::setBoundry(int _b, float* x) {
//return;
	for (int i = 1; i <= _NX; i++) {
		if(i<= _NY) {
			x[IX(  0, i  )] = /*_b == 1 ? -x[IX(_NX, i)] : */x[IX(_NX, i)];
			x[IX(_NX+1, i  )] =/* _b == 1 ? -x[IX(1, i)] :*/ x[IX(1, i)];
		}

		x[IX(  i, 0  )] = _b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
		x[IX(  i, _NY+1)] = _b == 2 ? -x[IX(i, _NY)] : x[IX(i, _NY)];
	}
	
	x[IX(  0,   0)] = 0.5f * (x[IX(1, 0  )] + x[IX(  0, 1)]);
	x[IX(  0, _NY+1)] = 0.5f * (x[IX(1, _NY+1)] + x[IX(  0, _NY)]);
	x[IX(_NX+1,   0)] = 0.5f * (x[IX(_NX, 0  )] + x[IX(_NX+1, 1)]);
	x[IX(_NX+1, _NY+1)] = 0.5f * (x[IX(_NX, _NY+1)] + x[IX(_NX+1, _NY)]);
}

// specifies simple boundry conditions.
void FluidSolver::setBoundryRGB(int _bound) {
	int index1, index2, index3;
	for (int i = 1; i <= _NX; i++) {
		if(i<= _NY) {
			index1 = IX(0, i);
			index2 = IX(_NX, i);
			_r[index1] = _bound == 1 ? -_r[index2] : _r[index2];
			_g[index1] = _bound == 1 ? -_g[index2] : _g[index2];
			_b[index1] = _bound == 1 ? -_b[index2] : _b[index2];
			
			index1 = IX(_NX+1, i );
			index2 = IX(1, i);
			_r[index1] = _bound == 1 ? -_r[index2] : _r[index2];
			_g[index1] = _bound == 1 ? -_g[index2] : _g[index2];
			_b[index1] = _bound == 1 ? -_b[index2] : _b[index2];
		}
		
		index1 = IX(i, 0);
		index2 = IX(i, 1);
		_r[index1] = _bound == 2 ? -_r[index2] : _r[index2];
		_g[index1] = _bound == 2 ? -_g[index2] : _g[index2];
		_b[index1] = _bound == 2 ? -_b[index2] : _b[index2];

		index1 = IX(i, _NY+1);
		index2 = IX(i, _NY);
		_r[index1] = _bound == 2 ? -_r[index2] : _r[index2];
		_g[index1] = _bound == 2 ? -_g[index2] : _g[index2];
		_b[index1] = _bound == 2 ? -_b[index2] : _b[index2];

	}
	
//	x[IX(  0,   0)] = 0.5f * (x[IX(1, 0  )] + x[IX(  0, 1)]);
//	x[IX(  0, _NY+1)] = 0.5f * (x[IX(1, _NY+1)] + x[IX(  0, _NY)]);
//	x[IX(_NX+1,   0)] = 0.5f * (x[IX(_NX, 0  )] + x[IX(_NX+1, 1)]);
//	x[IX(_NX+1, _NY+1)] = 0.5f * (x[IX(_NX, _NY+1)] + x[IX(_NX+1, _NY)]);
	
}


void FluidSolver::swapU() { 
	_tmp = _u; 
	_u = _uOld; 
	_uOld = _tmp; 
}
void FluidSolver::swapV(){ 
	_tmp = _v; 
	_v = _vOld; 
	_vOld = _tmp; 
}
void FluidSolver::swapRGB(){ 
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


// return velocity vector and density for normalized x,y coordinates
void FluidSolver::getInfo(float x, float y, float* info)  {
	int i= (int)(x * (_NX+2));
	int j= (int)(y * (_NY+2));
	
	if(i<0) i = 0; else if(i > _NX+1) i = _NX+1;
	if(j<0) j = 0; else if(j > _NY+1) j = _NY+1;
	
	int index = IX(i, j);
	
	info[FLUID_INFO_U]			= _u[index];
	info[FLUID_INFO_V]			= _v[index];
	info[FLUID_INFO_DENSITY]	= _d[index];
	info[FLUID_INFO_CURL]		= _curl[index];
}


// add force to normalized x, y,  coordinates
void FluidSolver::addAtNorm(float x, float y, float dx, float dy, float generateMult, float velocityMult, float r, float g, float b) {
	int i = (int) (x * _NX + 1);
	int j = (int) (y * _NY + 1);
	
	if(i<0 || i>_NX+1 || j<0 || j>_NY+1) return;		
	addAtPixel(i, j, dx, dy, generateMult, velocityMult, r, g, b);
}


// add force to x, y fluid coordinates
void FluidSolver::addAtPixel(int i, int j, float dx, float dy, float generateMult, float velocityMult, float r, float g, float b, float speed2) {
	if(speed2 < 0) speed2 = dx * dx + dy * dy;
	if(speed2 > 0.0f) {
		int index = IX(i, j);
		
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






