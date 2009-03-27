

#include "ofxSimplex.h"
#include "ofxSimplexTables.h"

#define OFX_SIMPLEX_SQRT3 1.73205080756888
#define OFX_SIMPLEX_SQRT5 2.23606797749979

#define OFX_SIMPLEX_F2 0.36602540378444
#define OFX_SIMPLEX_G2 0.211325
#define OFX_SIMPLEX_G22 -0.57735

#define OFX_SIMPLEX_F3 0.33333333333333
#define OFX_SIMPLEX_G3 0.16666666666667

#define OFX_SIMPLEX_F4 0.309017
#define OFX_SIMPLEX_G4 0.138197
#define OFX_SIMPLEX_G42 0.276393
#define OFX_SIMPLEX_G43 0.41459
#define OFX_SIMPLEX_G44 -0.447214

ofxSimplex::ofxSimplex(){
	perm = new int[0x200];
	for(int i=0; i<0x200; i++){
		perm[i] = p[i & 0xff];
	}
}

ofxSimplex::~ofxSimplex(){
	delete[] perm;
}



//the following was directly ported from Karsten Schmidt's class, including all the coments.
//i just changed all the doubles to floats.
float ofxSimplex::noise(float x, float y){
	float n0 = 0, n1 = 0, n2 = 0; // Noise contributions from the three
	// corners
	// Skew the input space to determine which simplex cell we're in
	float s = (x + y) * OFX_SIMPLEX_F2; // Hairy factor for 2D
	int i = fastfloor(x + s);
	int j = fastfloor(y + s);
	float t = (i + j) * OFX_SIMPLEX_G2;
	float x0 = x - (i - t); // The x,y distances from the cell origin
	float y0 = y - (j - t);
	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j)
	if (x0 > y0) {
		i1 = 1;
		j1 = 0;
	} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else {
		i1 = 0;
		j1 = 1;
	} // upper triangle, YX order: (0,0)->(0,1)->(1,1)
	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6
	float x1 = x0 - i1 + OFX_SIMPLEX_G2; // Offsets for middle corner in (x,y) unskewed
	float y1 = y0 - j1 + OFX_SIMPLEX_G2;
	float x2 = x0 + OFX_SIMPLEX_G22; // Offsets for last corner in (x,y) unskewed
	float y2 = y0 + OFX_SIMPLEX_G22;
	// Work out the hashed gradient indices of the three simplex corners
	int ii = i & 0xff;
	int jj = j & 0xff;
	// Calculate the contribution from the three corners
	float t0 = 0.5 - x0 * x0 - y0 * y0;
	if (t0 > 0) {
		t0 *= t0;
		int gi0 = perm[ii + perm[jj]] % 12;
		n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for
		// 2D gradient
	}
	float t1 = 0.5 - x1 * x1 - y1 * y1;
	if (t1 > 0) {
		t1 *= t1;
		int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
		n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}
	float t2 = 0.5 - x2 * x2 - y2 * y2;
	if (t2 > 0) {
		t2 *= t2;
		int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;
		n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}
	return 70.0f * (n0 + n1 + n2);
}

float ofxSimplex::noise(float x, float y, float z){
	float n0 = 0, n1 = 0, n2 = 0, n3 = 0;
	// Noise contributions from the
	// four corners
	// Skew the input space to determine which simplex cell we're in
	// final double F3 = 1.0 / 3.0;
	float s = (x + y + z) * OFX_SIMPLEX_F3; // Very nice and simple skew factor
	// for 3D
	int i = fastfloor(x + s);
	int j = fastfloor(y + s);
	int k = fastfloor(z + s);
	// final double G3 = 1.0 / 6.0; // Very nice and simple unskew factor,
	// too
	float t = (i + j + k) * OFX_SIMPLEX_G3;
	float x0 = x - (i - t); // The x,y,z distances from the cell origin
	float y0 = y - (j - t);
	float z0 = z - (k - t);
	// For the 3D case, the simplex shape is a slightly irregular
	// tetrahedron.
	// Determine which simplex we are in.
	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k)
	// coords
	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
	if (x0 >= y0) {
		if (y0 >= z0) {
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		} // X Y Z order
		else if (x0 >= z0) {
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		} // X Z Y order
		else {
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		} // Z X Y order
	} else { // x0<y0
		if (y0 < z0) {
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		} // Z Y X order
		else if (x0 < z0) {
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		} // Y Z X order
		else {
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		} // Y X Z order
	}
	// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z),
	// and
	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z),
	// where
	// c = 1/6.
	float x1 = x0 - i1 + OFX_SIMPLEX_G3; // Offsets for second corner in (x,y,z) coords
	float y1 = y0 - j1 + OFX_SIMPLEX_G3;
	float z1 = z0 - k1 + OFX_SIMPLEX_G3;
	
	float x2 = x0 - i2 + OFX_SIMPLEX_F3; // Offsets for third corner in (x,y,z)
	float y2 = y0 - j2 + OFX_SIMPLEX_F3;
	float z2 = z0 - k2 + OFX_SIMPLEX_F3;
	
	float x3 = x0 - 0.5; // Offsets for last corner in (x,y,z)
	float y3 = y0 - 0.5;
	float z3 = z0 - 0.5;
	// Work out the hashed gradient indices of the four simplex corners
	int ii = i & 0xff;
	int jj = j & 0xff;
	int kk = k & 0xff;
	
	// Calculate the contribution from the four corners
	float t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0;
	if (t0 > 0) {
		t0 *= t0;
		int gi0 = perm[ii + perm[jj + perm[kk]]] % 12;
		n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
	}
	double t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1;
	if (t1 > 0) {
		t1 *= t1;
		int gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]] % 12;
		n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
	}
	float t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2;
	if (t2 > 0) {
		t2 *= t2;
		int gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]] % 12;
		n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
	}
	float t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3;
	if (t3 > 0) {
		t3 *= t3;
		int gi3 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]] % 12;
		n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
	}
	// Add contributions from each corner to get the final noise value.
	// The result is scaled to stay just inside [-1,1]
	return 32.0f * (n0 + n1 + n2 + n3);
}

float ofxSimplex::noise(float x, float y, float z, float w){
	// The skewing and unskewing factors are hairy again for the 4D case
	float n0 = 0, n1 = 0, n2 = 0, n3 = 0, n4 = 0; // Noise contributions
	// from the five corners
	// Skew the (x,y,z,w) space to determine which cell of 24 simplices
	float s = (x + y + z + w) * OFX_SIMPLEX_F4; // Factor for 4D skewing
	int i = fastfloor(x + s);
	int j = fastfloor(y + s);
	int k = fastfloor(z + s);
	int l = fastfloor(w + s);
	float t = (i + j + k + l) * OFX_SIMPLEX_G4; // Factor for 4D unskewing
	float x0 = x - (i - t); // The x,y,z,w distances from the cell origin
	float y0 = y - (j - t);
	float z0 = z - (k - t);
	float w0 = w - (l - t);
	// For the 4D case, the simplex is a 4D shape I won't even try to
	// describe.
	// To find out which of the 24 possible simplices we're in, we need to
	// determine the magnitude ordering of x0, y0, z0 and w0.
	// The method below is a good way of finding the ordering of x,y,z,w and
	// then find the correct traversal order for the simplex were in.
	// First, six pair-wise comparisons are performed between each possible
	// pair of the four coordinates, and the results are used to add up
	// binary bits for an integer index.
	int c = 0;
	if (x0 > y0) {
		c = 0x20;
	}
	if (x0 > z0) {
		c |= 0x10;
	}
	if (y0 > z0) {
		c |= 0x08;
	}
	if (x0 > w0) {
		c |= 0x04;
	}
	if (y0 > w0) {
		c |= 0x02;
	}
	if (z0 > w0) {
		c |= 0x01;
	}
	int i1, j1, k1, l1; // The integer offsets for the second simplex corner
	int i2, j2, k2, l2; // The integer offsets for the third simplex corner
	int i3, j3, k3, l3; // The integer offsets for the fourth simplex corner
	// simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some
	// order. Many values of c will never occur, since e.g. x>y>z>w makes
	// x<z, y<w and x<w impossible. Only the 24 indices which have non-zero
	// entries make any sense. We use a thresholding to set the coordinates
	// in turn from the largest magnitude. The number 3 in the "simplex"
	// array is at the position of the largest coordinate.
	int *sc = simplex[c];
	i1 = sc[0] >= 3 ? 1 : 0;
	j1 = sc[1] >= 3 ? 1 : 0;
	k1 = sc[2] >= 3 ? 1 : 0;
	l1 = sc[3] >= 3 ? 1 : 0;
	// The number 2 in the "simplex" array is at the second largest
	// coordinate.
	i2 = sc[0] >= 2 ? 1 : 0;
	j2 = sc[1] >= 2 ? 1 : 0;
	k2 = sc[2] >= 2 ? 1 : 0;
	l2 = sc[3] >= 2 ? 1 : 0;
	// The number 1 in the "simplex" array is at the second smallest
	// coordinate.
	i3 = sc[0] >= 1 ? 1 : 0;
	j3 = sc[1] >= 1 ? 1 : 0;
	k3 = sc[2] >= 1 ? 1 : 0;
	l3 = sc[3] >= 1 ? 1 : 0;
	// The fifth corner has all coordinate offsets = 1, so no need to look
	// that up.
	float x1 = x0 - i1 + OFX_SIMPLEX_G4; // Offsets for second corner in (x,y,z,w)
	float y1 = y0 - j1 + OFX_SIMPLEX_G4;
	float z1 = z0 - k1 + OFX_SIMPLEX_G4;
	float w1 = w0 - l1 + OFX_SIMPLEX_G4;
	
	float x2 = x0 - i2 + OFX_SIMPLEX_G42; // Offsets for third corner in (x,y,z,w)
	float y2 = y0 - j2 + OFX_SIMPLEX_G42;
	float z2 = z0 - k2 + OFX_SIMPLEX_G42;
	float w2 = w0 - l2 + OFX_SIMPLEX_G42;
	
	float x3 = x0 - i3 + OFX_SIMPLEX_G43; // Offsets for fourth corner in (x,y,z,w)
	float y3 = y0 - j3 + OFX_SIMPLEX_G43;
	float z3 = z0 - k3 + OFX_SIMPLEX_G43;
	float w3 = w0 - l3 + OFX_SIMPLEX_G43;
	
	float x4 = x0 + OFX_SIMPLEX_G44; // Offsets for last corner in (x,y,z,w)
	float y4 = y0 + OFX_SIMPLEX_G44;
	float z4 = z0 + OFX_SIMPLEX_G44;
	float w4 = w0 + OFX_SIMPLEX_G44;
	
	// Work out the hashed gradient indices of the five simplex corners
	int ii = i & 0xff;
	int jj = j & 0xff;
	int kk = k & 0xff;
	int ll = l & 0xff;
	
	// Calculate the contribution from the five corners
	float t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
	if (t0 > 0) {
		t0 *= t0;
		int gi0 = perm[ii + perm[jj + perm[kk + perm[ll]]]] % 32;
		n0 = t0 * t0 * dot(grad4[gi0], x0, y0, z0, w0);
	}
	float t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
	if (t1 > 0) {
		t1 *= t1;
		int gi1 = perm[ii + i1
					   + perm[jj + j1 + perm[kk + k1 + perm[ll + l1]]]] % 32;
		n1 = t1 * t1 * dot(grad4[gi1], x1, y1, z1, w1);
	}
	float t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
	if (t2 > 0) {
		t2 *= t2;
		int gi2 = perm[ii + i2
					   + perm[jj + j2 + perm[kk + k2 + perm[ll + l2]]]] % 32;
		n2 = t2 * t2 * dot(grad4[gi2], x2, y2, z2, w2);
	}
	float t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
	if (t3 > 0) {
		t3 *= t3;
		int gi3 = perm[ii + i3
					   + perm[jj + j3 + perm[kk + k3 + perm[ll + l3]]]] % 32;
		n3 = t3 * t3 * dot(grad4[gi3], x3, y3, z3, w3);
	}
	float t4 = 0.6 - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
	if (t4 > 0) {
		t4 *= t4;
		int gi4 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1 + perm[ll + 1]]]] % 32;
		n4 = t4 * t4 * dot(grad4[gi4], x4, y4, z4, w4);
	}
	// Sum up and scale the result to cover the range [-1,1]
	return 27.0f * (n0 + n1 + n2 + n3 + n4);
}

float ofxSimplex::noiseuf(float x, float y){
	float res = noise(x, y);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

float ofxSimplex::noiseuf(float x, float y, float z){
	float res = noise(x, y, z);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

float ofxSimplex::noiseuf(float x, float y, float z, float w){
	float res = noise(x, y, z, w);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

float ofxSimplex::dot(int *g, float x, float y){
	return g[0] * x + g[1] * y;
}

float ofxSimplex::dot(int *g, float x, float y, float z){
	return g[0] * x + g[1] * y + g[2] * z;
}

float ofxSimplex::dot(int *g, float x, float y, float z, float w){
	return g[0] * x + g[1] * y + g[2] * z;
}

int ofxSimplex::fastfloor(float x){
	return x > 0 ? (int)x : (int)x-1;
}

