#include "testApp.h"
using namespace std;

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0, 0, 0);
	ofSetFrameRate(32);
	
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	// center.x = ofGetWidth()/2;
	// center.y = ofGetHeight()/2;
	// center.z = 0;
	
	noise = new Perlin(4, 4, 1, time(NULL));
	for(int i=0; i<NumEmitters; i++){
		emitters[i].rotX = ofRandom(0, 360);
		emitters[i].rotY = ofRandom(0, 360);
		emitters[i].band = NumEmitters%NumBands;
	}
	counter = 0;

	pause = false;
	mode = 0;
	doTail = true;
	
	// cam.pos.x = 0;
	// cam.pos.y = center.y;
	// cam.pos.z = 9000;
	// cam.center = &center;
	// cam.lookAt(center);
	
	bFullScreen = false;
	
	// ofInitLights();

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
	
	camera.position(centerX, centerY, 1000); //initialize the camera at a far position from the sphere
	
	
	music.loadSound("music.mp3");
	music.play();
	music.setVolume(1);
	
}

//--------------------------------------------------------------
void testApp::update(){
	counter++;
	
	float *fftList = ofSoundGetSpectrum(NumBands);
	
	float totalFFT = 0;
	for(int i=0; i<NumBands; i++){
		totalFFT += fftList[i]*50;
	}
	averFFT = totalFFT / NumBands;
	

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

	//emitters
	updateEmitters();	
	
	//particles
	updateParticles();
}

//--------------------------------------------------------------
void testApp::draw(){
	camera.place(); //this MUST be inside the draw function, and actually places the camera in position
	if (mode != 0)	ofxLightsOn();
	
	ofSetColor(255, 255, 255);
	glPushMatrix();
	glTranslatef(centerX, centerY, centerZ);
		glRotatef(rotX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		for(int i=0; i<p.size(); i++){
			p[i].render();
		}
	glPopMatrix();
	
	camera.remove();
	if (mode != 0)	ofxLightsOff();
	
	ofSetColor(255,255,255);
	ofDrawBitmapString("frameRate: " + ofToString( ofGetFrameRate() ) + " | drawTrails: " + ofToString( doTail ) + " (t) | mode: " + ofToString( mode ) + " (SPACE)", 3,13);	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key == 'i' or key == 'I') cout << ofGetFrameRate() << endl;
	if(key == 'p' or key == 'P') {
		pause = !pause;
		music.setPaused(pause);
	}
	
	if (key == ' ') {
			if (mode >= 2)	mode=0;
			else			mode++;
	}
	
	if (key == 't') {
		doTail = !doTail;
	}
	
	if(key == 'f' or key == 'F') {
		bFullScreen = !bFullScreen;
		ofSetFullscreen(bFullScreen);
		if(bFullScreen) ofHideCursor();
		else ofShowCursor();
	}
	
	if (key == 'o') {
		rotX = rotX+2;
	}
	if (key == 'i') {
		rotX = rotX-2;
	}
	if (key == 'l') {
		rotY = rotY+2;
	}
	if (key == 'k') {
		rotY = rotY-2;
	}
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  }

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}

void testApp::updateEmitters(){
	float *fftList = ofSoundGetSpectrum(NumBands);
	for(int i=0; i<NumEmitters; i++){
		float div = 3000;
		float fftVal = fftList[emitters[i].band] * 50; 
		float targetRadius = averFFT*300+fftVal*10;
		emitters[i].updateRadius(targetRadius);
		ofxVec3f rot = ofxVec3f(0, 0, emitters[i].radius);
		float radRotX = noise->Get(emitters[i].pos.y/div, (emitters[i].pos.z+counter*10)/div)*TWO_PI;
		float radRotY = noise->Get(emitters[i].pos.x/div, (emitters[i].pos.y+counter*10)/div)*TWO_PI;
		int step = 3;
		emitters[i].rotX += cos(radRotX)*(averFFT*50)+ofRandom(-step, step);
		emitters[i].rotY -= sin(radRotY)*(averFFT*50)+ofRandom(-step, step);
		rot.rotate(emitters[i].rotX, emitters[i].rotY, 0);
		ofxVec3f pos = center + rot;
		emitters[i].move(pos);
	}	
}

void testApp::updateParticles(){
	int toAdd =  abs((int)(averFFT*AddMult));
	
	for(int i=0; i<toAdd; i++){
		int whichEmitter = (int)ofRandom(0, NumEmitters);
		ofxVec3f iniPos = emitters[whichEmitter].pos;
		ofxVec3f iniVel = emitters[whichEmitter].vel*7;
		p.push_back(Particles(iniPos, iniVel, noise, mode));
		if (doTail==true) p[p.size()-1].doTail = true;
	}

	for(int i=0; i<p.size(); i++){
		if(p[i].life<=0) p.erase(p.begin()+i);
		else{
			p[i].move();
		}
	}
}
