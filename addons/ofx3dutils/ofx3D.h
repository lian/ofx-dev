#ifndef _OFX_3D_
#define _OFX_3D_

#include "ofConstants.h"
#include "ofGraphics.h"
#include <GLUT/glut.h>

	static int OF_POLY_MODE;
	static GLfloat light_position[] = { 0.0, 3.0, 2.0, 0.0 };


	//------------------------------------------------------------------- 3D
	void ofCube(float d, float x, float y);
	void ofSphere(float _r, float _x, float _y);
	void ofSphere(float _r, float _x, float _y, float _res);
	void ofTeaPot(float d, float x, float y);
	
	//------------------------------------------------------------------- Nurb
	void ofNurb();
	void ofInitNurb();
	void ofNurbCtrlPoints();
	
	//------------------------------------------------------------------- Lights
	void ofInitLights();
	void ofLightsOn();
	void ofLightsOff();
	void ofPositionLight(float x, float y, float z);
	void ofPositionLight();
	
	void ofFog();
	//------------------------------------------------------------------- 3D Modes
	void ofSet3DMode(int mode);
	
#endif
