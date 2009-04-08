

#include "ofxPerlin.h"

ofxPerlin::ofxPerlin(){
	perlin_octaves = 4;
	perlin_amp_falloff = 0.5f;
	perlin = new float[PERLIN_SIZE+1];
	for(int i=0; i<PERLIN_SIZE + 1; i++){
		perlin[i] = ofRandomf();
	}
	perlin_cosTable = sinCosLUT.cosLUT;
	perlin_TWO_PI = perlin_PI = sinCosLUT.SC_PERIOD;
	perlin_PI >>= 1;
}

ofxPerlin::~ofxPerlin(){
	delete[] perlin;
}

float ofxPerlin::noise(float x){
	if(x < 0) x = -x;
	
	int xi = (int)x;
	float xf = (float)(x - xi);
	float rxf;
	
	float r = 0;
	float ampl = 0.5f;
	
	float n1;
	
	for(int i=0; i<perlin_octaves; i++){
		int of = xi;
		rxf = noise_fsc(xf);
		
		n1 = perlin[of & PERLIN_SIZE];
		n1 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n1);
		
		of += PERLIN_ZWRAP;
		
		r += n1 * ampl;
		ampl *= perlin_amp_falloff;
		
		if (ampl<PERLIN_MIN_AMPLITUDE) break;
		
		xi <<= 1;
		xf *= 2;
		
		if (xf >= 1.0f) {
			xi++;
			xf--;
		}
	}
	return r;
}

float ofxPerlin::noise(float x, float y){
	if(x < 0) x = -x;
	if(y < 0) y = -y;
	
	int xi = (int)x, yi =(int)y;
	float xf = (float)(x - xi);
	float yf = (float)(y - yi);
	float rxf, ryf;
	
	float r = 0;
	float ampl = 0.5f;
	
	float n1, n2, n3;
	
	for(int i=0; i<perlin_octaves; i++){
		int of = xi + (yi << PERLIN_YWRAPB);
		
		rxf = noise_fsc(xf);
		ryf = noise_fsc(yf);
		
		n1 = perlin[of & PERLIN_SIZE];
		n1 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n1);
		n2 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n2);
		n1 += ryf * (n2 - n1);
		
		of += PERLIN_ZWRAP;
		n2 = perlin[of & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n2);
		n3 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n3 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n3);
		n2 += ryf * (n3 - n2);
		
		r += n1 * ampl;
		ampl *= perlin_amp_falloff;
		
		if (ampl<PERLIN_MIN_AMPLITUDE) break;
		
		xi <<= 1;
		xf *= 2;
		yi <<= 1;
		yf *= 2;
		
		if (xf >= 1.0f) {
			xi++;
			xf--;
		}
		if (yf >= 1.0f) {
			yi++;
			yf--;
		}
	}
	return r;
	
}

float ofxPerlin::noise(float x, float y, float z){
	perlin_cosTable = sinCosLUT.cosLUT;
	perlin_TWO_PI = perlin_PI = sinCosLUT.SC_PERIOD;
	perlin_PI >>= 1;
	
	if(x < 0) x = -x;
	if(y < 0) y = -y;
	if(z < 0) z = -z;
	
	int xi = (int)x, yi =(int)y, zi = (int)z;
	float xf = (float)(x - xi);
	float yf = (float)(y - yi);
	float zf = (float)(z - zi);
	float rxf, ryf;
	
	float r = 0;
	float ampl = 0.5f;
	
	float n1, n2, n3;
	
	for(int i=0; i<perlin_octaves; i++){
		int of = xi + (yi << PERLIN_YWRAPB) + (zi << PERLIN_ZWRAPB);
		
		
		rxf = noise_fsc(xf);
		ryf = noise_fsc(yf);
		
		n1 = perlin[of & PERLIN_SIZE];
		n1 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n1);
		n2 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n2);
		n1 += ryf * (n2 - n1);
		
		of += PERLIN_ZWRAP;
		n2 = perlin[of & PERLIN_SIZE];
		n2 += rxf * (perlin[(of + 1) & PERLIN_SIZE] - n2);
		n3 = perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
		n3 += rxf * (perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n3);
		n2 += ryf * (n3 - n2);
		
		n1 += noise_fsc(zf) * (n2 - n1);
		
		r += n1 * ampl;
		ampl *= perlin_amp_falloff;
		
		if (ampl<PERLIN_MIN_AMPLITUDE) break;
		
		xi <<= 1;
		xf *= 2;
		yi <<= 1;
		yf *= 2;
		zi <<= 1;
		zf *= 2;
		
		if (xf >= 1.0f) {
			xi++;
			xf--;
		}
		if (yf >= 1.0f) {
			yi++;
			yf--;
		}
		if (zf >= 1.0f) {
			zi++;
			zf--;
		}
	}
	return r;
}

float ofxPerlin::noiseuf(float x){
	float res = noise(x);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

float ofxPerlin::noiseuf(float x, float y){
	float res = noise(x, y);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

float ofxPerlin::noiseuf(float x, float y, float z){
	float res = noise(x, y, z);
	res *= 0.5f;
	res += 0.5f;
	return res;
}

void ofxPerlin::noiseDetail(int lod){
	if(lod > 0){
		perlin_octaves = lod;
	}
}

void ofxPerlin::noiseDetail(int lod, float falloff){
	if(lod > 0){
		perlin_octaves = lod;
	}
	if(falloff > 0){
		perlin_amp_falloff = falloff;
	}
}

void ofxPerlin::noiseSeed(long what){
	srand(what);
	for(int i=0; i<PERLIN_SIZE + 1; i++){
		perlin[i] = ofRandomuf();
	}
}

float ofxPerlin::noise_fsc(float i){
	return 0.5f * (1.0f - perlin_cosTable[(int)(i * perlin_PI) % perlin_TWO_PI]);
}














