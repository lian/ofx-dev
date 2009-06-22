#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	
	/*for (int i = 0; i < 200; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}*/
	
	bRepel		= true;
	radius		= 140;
	strength	= 1.5f; 
	count = 0;
	
	ofBackground(0,0,0);//, <#int g#>, <#int b#>)
	ofSetCircleResolution(5);
	
	ofEnableSmoothing();
	mouseDown=false;
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	if(!mouseDown && count < 500)
	{
		for (int i = 0; i < particles.size(); i++){
			particles[i].resetForce();
		}
		
		for (int i = 0; i < particles.size(); i++){
			for (int j = 0; j < i; j++){
				if (bRepel){
					if(ofRandom(0,20)<2)
					{
						particles[i].addRepulsionForce(particles[j], radius, strength);
					}
				} else {
					particles[i].addAttractionForce(particles[j], radius, strength);
				}
			}
		}
		
		for (int i = 0; i < particles.size(); i++){
			particles[i].addDampingForce();
			particles[i].update();
		}
		count++;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	ofSetColor(0,130,130, 200);
	
	ofSetColor(0x000000);
	ofSetColor(255,255,100,150);
	//if(mouseDown)
	{
		ofBeginShape();
	//ofNoFill();
	
		for (int i = 0; i < particles.size(); i++){
			//particles[i].draw();
			//if(i>0)
			//{
			//	ofLine(particles[i].pos.x,particles[i].pos.y,particles[i-1].pos.x,particles[i-1].pos.y);
			//}
			ofCurveVertex(particles[i].pos.x,particles[i].pos.y);
		}
		
		ofNoFill();
		ofEndShape(false);
	}
		
	ofSetColor(255,255,255,25);
	if(particles.size()>0)
	{
		for (int i = 1; i < particles.size()-1; i++){
			particles[i].draw();
		}
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
	
	//particles.erase(particles.begin());
	particle myParticle;
	myParticle.setInitialCondition(x,y,0,0);
	particles.push_back(myParticle);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	mouseDown=true;
	count=0;
	particles.clear();
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	mouseDown=false;
}
