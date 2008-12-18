#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	ofSetFrameRate(60);
	tuio.start(3333);	
}

//--------------------------------------------------------------
void testApp::update(){
	tuio.getMessage();
}


//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	tuio.drawCursors();
	tuio.drawObjects();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
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
