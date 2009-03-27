#pragma once


#include "ofMain.h"

#include "ofxVectorMath.h"
#include "ofx3DUtils.h"

#include "perlin.h"
#include "Disk.h"

class Worm{
public:
	
	vector<Disk> disk;
	int numDisks;
	
	ofxVec3f pos;
	ofxVec3f vel, accel; 
	float fat;
	
	Perlin *noise;
	
	float color[3];
	
	Worm(ofxVec3f iniPos, Perlin* _noise);
	
	void move();
	
	void render();
	void renderContours();
	void dontGoTooFar(ofxVec3f midPt);
	
	void renderNormals();
	
	
};
