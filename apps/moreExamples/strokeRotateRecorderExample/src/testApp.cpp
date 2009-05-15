#include "testApp.h"

static float storeTime;

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	recording = false;
	playPos   = 0.0;	//this is our playback head
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(recording){
		//we are going to be smart!
		//we don't want to record a point unless it is at least 2 pixels away from our previous point!
		ofxVec2f mousePt(mouseX, mouseY);
		
		//find the distance between our mouse and our previous point
		ofxVec2f dist = mousePt - prevPoint;
		
		if( dist.length() > 2 ){
			//add the point in.
			ptsList.push_back( mousePt );
			//lets store the current position 
			prevPoint.set(mousePt);
		}
	}else{
		//if we are not recording we are playing back 
		//playPos goes from 0.0 - 1.0
		//when we draw we scale up that number by the number of pts in the list 
		//so it will draw from point 0 up to a certain percentage of the total points. 
		playPos += 0.01;
		if(playPos > 2.0){
			playPos = 0;
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	

	ofSetPolyMode(OF_POLY_WINDING_ODD);

	//if we are smoothing the pts - might as well draw the line smooth too :)
	ofEnableSmoothing();
	
	//if we are recording we just draw all points as a red line
	if(recording){	
		ofSetColor(255, 50, 50);

		ofNoFill();
		ofBeginShape();
		
		for( unsigned int i = 0; i < ptsList.size(); i++){
			ofVertex(ptsList[i].x, ptsList[i].y);
		}
		
		ofEndShape(false);
	
	}else{

		ofSetColor(255, 255, 255);

		float max = MIN(1, playPos);
		int drawTo = max * (float)ptsList.size();


//      Drawing with GL triangle strips
//
//		glBegin(GL_TRIANGLE_STRIP);
//		for(int i = 0; i < drawTo; i++){
//			ofxVec2f pt1;
//			pt1 = ptsList[i] + leftNormals[i] * speedList[i] * 2; 
//
//			ofxVec2f pt2;
//			pt2 = ptsList[i] + rightNormals[i] * speedList[i] * 2; 
//			
//			glVertex2f(pt1.x, pt1.y);
//			glVertex2f(pt2.x, pt2.y);
//		}
//		glEnd();


		//For Evan Roth Style Rotating Stroke

		glTranslated(ofGetWidth()/2, ofGetHeight()/2, 0);
		glRotatef( -20 * ( ofGetElapsedTimef()-storeTime), 0, 1, 0);
	
		float midX = ofGetWidth()/2;
		float midY = ofGetHeight()/2;
		
		//float speed = 2;
		
		
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofFill();
		ofBeginShape();
			for(int i = 0; i < drawTo; i++){
			
				ofxVec2f pt;
				pt = ptsList[i] + leftNormals[i] * speedList[i]; 
				ofVertex(pt.x-midX, pt.y-midY);
			}
		
			for(int i = drawTo-1; i >= 0; i--){			

				ofxVec2f pt;
				pt = ptsList[i] + rightNormals[i] * speedList[i]; 
				ofVertex(pt.x-midX, pt.y-midY);
			}
		ofEndShape(false);
		
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
	//when we press the mouse button for the first time 
	//we clear all the points and begin recording

	//clear our recorded points
	ptsList.clear();
	speedList.clear();
	leftNormals.clear();
	rightNormals.clear();
	
	recording = true;

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	//when we release - we set recording to be false and we set our playhead to 0.0 again
	recording	= false;
	playPos		= 0.0;
	storeTime = ofGetElapsedTimef();
	
	//lets smooth those points!!
	//simple low pass smooth
	//go through the points list and make each point 70% of the previous point and 30% of itself
	
	//you can play with the 0.7 and 0.3 ratio bellow - as long as the total adds up to 1.0
	
	//NOTE: that we start at 1 as point 0 has no previous point :(
	
	speedList.push_back(0);
	leftNormals.push_back( 0 );
	rightNormals.push_back(0 );
			
	for(unsigned int i = 1; i < ptsList.size(); i++){
		ptsList[i] = 0.3 * ptsList[i] + 0.7 * ptsList[i-1];
		
		ofxVec2f distVec = ptsList[i] - ptsList[i-1];
		float speed = distVec.length();
		
		distVec.normalize();
		
		speed = 0.2*speed + speedList[i-1]*0.8;
		
		speedList.push_back(speed);
		leftNormals.push_back( ofxVec2f(-distVec.y, distVec.x) );
		rightNormals.push_back( ofxVec2f(distVec.y, -distVec.x) );
	}
	
}
















