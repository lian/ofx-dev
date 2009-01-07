#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	// test world has a default constructor in testApp.h
}

//--------------------------------------------------------------
void testApp::update(){
	world.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	world.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	// any key will change the gravity
	world.reverseGravity();
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
