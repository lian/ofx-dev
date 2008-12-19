#include "testApp.h"

/*
Original code by: Zachary Lieberman
URL to examples: http://a.parsons.edu/~algo/archives/code_examples/index.html
Ported to OF0.2 by SH101 - http://zombie.nu
*/

void testApp::setup(){
	
	ofSeedRandom();
	
	SM = new simulationManager();
	PM = new particleManager();
	SM->PM = PM;
	
}

void testApp::update(){

	ofSetColor(0.4f,0.6f, 0.2f, 0.0f);
	SM->idle(0.1f);
}

void testApp::draw(){
	
	ofSetupScreen();
	SM->draw();
	PM->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	

	PM->PTS[0]->pos.x = (float)x;
	PM->PTS[0]->pos.y = (float)y;

		dx = (float)x - lastx;
		dy = (float)y - lasty;
		lastx = (float)x;
		lasty = (float)y;		
		
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	lastx = (float)x;
	lasty = (float)y;
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}


