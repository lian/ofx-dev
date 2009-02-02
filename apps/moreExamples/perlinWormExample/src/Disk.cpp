
#include "Disk.h"

Disk::Disk(ofxVec3f iniPos, float _radius ){
	center = iniPos;
	radius = _radius;
	for(int i=0; i<NUMP; i++){
		float angle = (float)i/(NUMP-1)*TWO_PI;
		float x = center.x;
		float y = center.y + sin(angle)*radius;
		float z = center.z + cos(angle)*radius;
		p[i].set(x, y, z);
		contourP[i].set(x, y, z);
	}
	
	accel = 0;
	vel = 0;
}

void Disk::move(ofxVec3f target, float rotX, float rotY){
	float k = 0.8;
	float damp = 0.4;
	
	accel = (target - center) * k;
	vel += accel;
	vel *= damp;
	center += vel;
	
	
	rotX *= RAD_TO_DEG;
	rotY *= RAD_TO_DEG;
	
	for(int i=0; i<NUMP; i++){
		float angle = (float)i/(NUMP-1)*TWO_PI;
		float x = 0;
		float y = sin(angle)*radius;
		float z = cos(angle)*radius;
		p[i].set(x, y, z);
		p[i].rotate(rotX, rotY, 0.0f);
		p[i] += center;
		
		float strokeGap = 0.2f;
		y = sin(angle)*(radius+strokeGap);
		z = cos(angle)*(radius+strokeGap);
		contourP[i].set(x, y, z);
		contourP[i].rotate(rotX, rotY, 0.0f);
		contourP[i] += center;

	}
}

