#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(220,220,220);
	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights loo weird if depth test is not enabled
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
	
	camera.position(centerX, centerY, 5000); //initialize the camera at a far position from the sphere
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
	
//	camera.lerpPosition(centerX, centerY, 500, 0.1); //interpolate the camera into a closer position

}

//--------------------------------------------------------------
void testApp::draw(){
	camera.place();//this MUST be inside the draw function, and actually places the camera in position
	ofxLightsOn(); //turn lights on
	ofSetColor(255, 255, 255);
	glPushMatrix();
	glTranslatef(centerX, centerY, centerZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(200, 30, 30);
	glPopMatrix();
	
	camera.remove();
	ofxLightsOff(); //turn lights off to draw text
	string info = "PRESSING MOUSE WILL TURN SMOOTH LIGHTS OFF";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(info, 20, 20);
	//i guess cameras and text dont go very well ;)
//	camera.orbitAround(ofxVec3f(centerX,centerY,centerZ),ofxVec3f(0,1,0),1);
//	camera.rotate(ofxVec3f(0,1,0),1);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key == OF_KEY_LEFT){
		camera.moveGlobal(-3, 0, 0);
	} else if(key == OF_KEY_RIGHT){
		camera.moveGlobal(3, 0, 0);
	} else if(key == OF_KEY_UP){
		camera.moveGlobal(0, 3, 0);
	} else if(key == OF_KEY_DOWN){
		camera.moveGlobal(0, -3, 0);
	} else if(key == '+'){
		camera.moveGlobal(0, 0, -30);
	} else if(key == '-'){
		camera.moveGlobal(0, 0, 30);
	}	else if(key == 'w'){
		camera.moveLocal(0, 0, 30);
	} else if(key == 's'){
		camera.moveLocal(0, 0, -30);
	} else if(key == 'a'){
		camera.moveLocal(-3, 0, 0);
	} else if(key == 'd'){
		camera.moveLocal(3, 0, 0);
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	//if(mx-x != 0){
	//	camera.rotate(ofxVec3f(0,1,0), -(mx-x)*1);
	//}
	
	//mx = x;
	//my = y;
	mouseX = x;
	mouseY = y;
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
