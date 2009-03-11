#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
testApp::testApp(){

}

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	fingerMovie.loadMovie("movies/fingers.mov");
	fingerMovie.play();
}

//--------------------------------------------------------------
void testApp::update(){
	fingerMovie.idleMovie();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);
	fingerMovie.draw(20,20);


	ofSetColor(0x000000);
	unsigned char * pixels = fingerMovie.getPixels();
	// let's move through the "RGB" char array
	// using the red pixel to control the size of a circle.
	for (int i = 4; i < 320; i+=8){
		for (int j = 4; j < 240; j+=8){
			unsigned char r = pixels[(j * 320 + i)*3];
			float val = 1 - ((float)r / 255.0f);
			ofCircle(400 + i,20+j,10*val);
		}
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	int width = ofGetWidth();
	float pct = (float)x / (float)width;
	float speed = (2 * pct - 1) * 5.0f;
	fingerMovie.setSpeed(speed);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	int width = ofGetWidth();
	float pct = (float)x / (float)width;
	fingerMovie.setPosition(pct);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	fingerMovie.setPaused(true);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	fingerMovie.setPaused(false);
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}
