#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	// reset the random seed since we'll need random later when we generate thingy sizes
	ofSeedRandom();
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::update(){
	// go through all the thingies
	for (int i=0; i < thingies.size(); i++) {
		thingies[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	// go through all the thingies
	for (int i=0; i < thingies.size(); i++) {
		thingies[i].draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){ 
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
	
	// get an "iterator" from our dynamic Thingy vector
	// this will allow us to go through all the objects
	vector<Thingy>::iterator this_thingy;
	// go through all the thingies
	for(this_thingy = thingies.begin(); this_thingy != thingies.end(); this_thingy++) {
		// go into this thingy, check to see if we're clicking on it
		if ( this_thingy->mousePressed(x,y) ) {
			// remove this thingy;
			thingies.erase(this_thingy);
			// exit from the mousePressed method
			return;
		}
	}
	
	// if we're this far, well none were found under the mouse, so add a thingy
	thingies.push_back( Thingy(x,y) );
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
