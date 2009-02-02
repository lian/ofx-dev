#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofEnableAlphaBlending();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	ofBackground(0,0,0);

	drawCounter = 0;
	
	fireworkInterval = 2500;
	lastFireworkLaunched = 0;
	
	seedFirework();
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < fireworks.size(); i++){
		if(fireworks[i].exploded == true){
			fireworks[i].addForce(ofRandom(-.01,.01),0,ofRandom(-.01,.01));
		}else{
			fireworks[i].addForce(ofRandom(-.01,.01),.002,ofRandom(-.01,.01));
		}
		fireworks[i].addDampingForce();
		fireworks[i].update();
	}
	
	if((ofGetElapsedTimeMillis() - lastFireworkLaunched) >= fireworkInterval){
		seedFirework();
		lastFireworkLaunched = ofGetElapsedTimeMillis();
	}

}

//--------------------------------------------------------------
void testApp::seedFirework(){
	// cout << "firework launched" << endl;
	bool fireworkLaunched = false;
	for (int i = 0; i < fireworks.size(); i++){
		if(fireworks[i].isFinished() == true){
			fireworks[i].seed();
			fireworkLaunched = true;
		}
	}
	if(fireworks.size() < 5){
		if(fireworkLaunched == false){
			firework myFirework;
			myFirework.seed();
			fireworks.push_back(myFirework);
			fireworkLaunched = true;
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255,255,255);
	for (int i = 0; i < fireworks.size(); i++){
		fireworks[i].draw();
	}
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
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
