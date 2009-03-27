#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled
	centerX = ofGetWidth()/2;
	centerY = ofGetHeight()/2;
	centerZ = 0;
	
	rotX = 0;
	rotY = 0;
	bSmoothLight = true;
	
	//reflexions!!
	ofxMaterialSpecular(120, 120, 120); //how much specular light will be reflect by the surface
	ofxMaterialShininess(50); //how concentrated the reflexion will be (between 0 and 128
	
	//each light will emit white reflexions
	light1.specular(255, 255, 255);
	light2.specular(255, 255, 255);
	light3.specular(255, 255, 255);

	camera.position(centerX, centerY, 10000); //initialize the camera at a far position from the sphere
	
}

//--------------------------------------------------------------
void testApp::update(){
	rotX += 1;
	rotY += 2;
	
	//light1
	float L1DirectionX = 1;
	float L1DirectionY = 0;
	float L1DirectionZ = 0;
	
	light1.directionalLight(255, 0, 0, L1DirectionX, L1DirectionY, L1DirectionZ);
	
	//light2
	float L2ConeAngle = 50;
	float L2Concentration = 60;
	float L2PosX = mouseX;
	float L2PosY = mouseY;
	float L2PosZ = 500;
	float L2DirectionX = 0;
	float L2DirectionY = 0;
	float L2DirectionZ = -1;
	
	light2.spotLight(0, 255, 0, 
					 L2PosX, L2PosY, L2PosZ, 
					 L2DirectionX, L2DirectionY, L2DirectionZ,
					 L2ConeAngle,
					 L2Concentration);
	
	//light3
	float L3PosX = ofGetWidth();
	float L3PosY = mouseY;
	float L3PosZ = 500;
	light3.pointLight(0, 0, 255, L3PosX, L3PosY, L3PosZ);
	
	camera.lerpPosition(centerX, centerY, 600, 0.02); //interpolate the camera into a closer position

}

//--------------------------------------------------------------
void testApp::draw(){
	
	camera.place();//this MUST be inside the draw function, and actually places the camera in position
	
	ofxLightsOn(); //turn lights on
	ofSetColor(255, 255, 255);
	
	ofxSphere(centerX - 150, centerY - 150, 0, 50, 100, 100, rotX, rotY, 0);
	
	ofxBox(centerX + 150, centerY - 150, 0, 100, 200, 20, rotX, rotY, 0);
	
	ofxCone(centerX - 150, centerY + 150, 0, 50, 100, 50, rotX, rotY, 0);
	
	ofxCapsule(centerX + 150, centerY + 150, 0, 100, 100, 50, rotX, rotY, 0);
	
	ofxLightsOff(); //turn lights off to draw text
	string info = "PRESSING MOUSE WILL TURN SMOOTH LIGHTS OFF";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(info, 20, 20);


}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxSetSmoothLight(false);
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	ofxSetSmoothLight(true);
}
