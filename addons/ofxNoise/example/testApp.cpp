#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(0,0,0);
	
	noise = new ofxPerlin();
	simplex = new ofxSimplex();
	

}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 127);
	ofLine(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);
	
	
	//3d perlin noise
	float div = 100; 
	ofBeginShape();
	ofVertex(0, ofGetHeight());
	for(int i=0; i<ofGetScreenWidth(); i+=2){
		float posY = noise->noise((float)i/div, (float)mouseX/div, (float)ofGetFrameNum()/div);
		posY *= 200;
		posY += ofGetHeight()/2;
		ofVertex(i, posY);
	}
	ofVertex(ofGetWidth(), ofGetHeight());
	ofEndShape();
	
	ofSetColor(255, 0, 255, 127);
	//4d simplex noise
	ofBeginShape();
	ofVertex(0, ofGetHeight());
	for(int i=0; i<ofGetScreenWidth(); i+=2){
		float posY = simplex->noise((float)i/div, (float)mouseX/div, (float)ofGetFrameNum()/div, (float)ofGetFrameNum()/200);
		posY *= 200;
		posY += ofGetHeight()/2;
		ofVertex(i, posY);
	}
	ofVertex(ofGetWidth(), ofGetHeight());
	ofEndShape();
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
