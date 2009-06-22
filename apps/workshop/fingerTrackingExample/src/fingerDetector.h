#ifndef _VIDEO_HAND_FINGER_FINDER_
#define _VIDEO_HAND_FINGER_FINDER_

#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxVectorMath.h"



//-----------------------------------------------|
class fingerDetector{
	
	public:
	
	fingerDetector();
	
	bool findFingers(ofxCvBlob blob);
	bool findHands(ofxCvBlob smblob);
	void draw(float x, float y);
	void drawhands(float x, float y);
	
	float dlh,max;
	
	int handspos[2];
	
	vector  <ofxPoint2f>		ppico;
	vector  <ofxPoint2f>		smppico;
	
	vector	<float>				kpointcurv;
	vector	<float>				smkpointcurv;
	
	vector	<bool>				bfingerRuns;
	
	vector  <ofxPoint2f>		lhand;
	vector  <ofxPoint2f>		rhand;
	
	ofxVec2f	v1,v2,aux1;
	 
	ofxVec3f	v1D,vxv;
	ofxVec3f	v2D;
	 
	int k,smk;
	
	ofPoint hcentroid;
	
	 float teta,lhd;

};
//-----------------------------------------------|


#endif	
