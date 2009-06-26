#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Camera.h"
#include "ofShader.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);

		ofShader shaderA;
		ofShader shaderB;
		bool shaderA_IsActive;
		bool shaderB_IsActive;

		float timer;

		ofxVec3f center;
		Camera cam;
		bool cam_IsActive;
		
		ofTexture tex;
		bool useTex;
		
};

#endif
	
