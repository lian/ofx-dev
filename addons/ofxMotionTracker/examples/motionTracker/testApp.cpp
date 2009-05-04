#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	motionTracker.init(640, 480, 1);
	motionTracker.setOpticalFlowResolution(320, 240);
	motionTracker.setMirrorVideo(true);
}

//--------------------------------------------------------------
void testApp::update(){
	motionTracker.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	motionTracker.drawDebugVideo(0, 480, 320, 240);
	motionTracker.drawColor(0, 0, 640, 480);
	motionTracker.drawOpticalFlowAverage(640, 0, 640, 480);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	motionTracker.keyPressed(key);
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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

