#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
#include "ofAddons.h"

#include "ofxMSASpline.h"



class testApp : public ofSimpleApp{
	
public:
	
	ofxMSASpline2D spline2D;
	ofxMSASpline3D splineMouse;
	
	float currentRot;
	bool rotateView;
	
	void setup();
	void draw();

	void mousePressed(int x, int y, int button);
	void keyPressed(int key);
};

#endif

