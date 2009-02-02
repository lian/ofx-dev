#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(32);
	ofEnableSmoothing();
	// ofEnableAlphaBlending();
	glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	
	music.loadSound("music.mp3",false);
	music.play();
	spectrum = new float[3];
	
	maxParticles = 150;
	mouseDown = false;
	
	for (int i = 0; i < 1; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	spectrum = ofSoundGetSpectrum(42);
	// spectrum = ofSoundGetSpectrum(40);
	//for(int i = 0; i < 32; i++){
	//	if(spectrum[i] < 0){
	//		spectrum[i] = spectrum[i]  * -1;
	//	}
	//}
	float total = spectrum[2] + spectrum[5] + spectrum[7];
	// cout << "total: " << total << endl;
	float radius = 100+(total/3)*1500;
	float random_x = radius/500*ofRandom(0,5); 
	float random_y = radius/350*ofRandom(0,5);
	float emitter_x = (ofGetWidth()/2) + (radius * sin(ofGetElapsedTimef()*5));
	float emitter_y = (ofGetHeight()/2) + (radius * cos(ofGetElapsedTimef()*5));
	addTrailPoint(emitter_x, emitter_y,0);
	emitParticlesColor(emitter_x, emitter_y, random_x, random_y, 255,255,255, .45);

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	for (int i = 0; i < particles.size(); i++){
		
	particles[i].addRepulsionForce(ofGetWidth()/2, ofGetHeight()/2, 1000, 0.75f);
		
		//this is for partcle particle, note the limited for loop
		for (int j = 0; j < i; j++){
			//particles[i].addRepulsionForce(particles[j], 100, 0.55f);
			particles[i].addAttractionForce(particles[j], 100, 0.45f);
		}
	}
	

	if(particles.size() > maxParticles){
		particles.erase(particles.begin());
	}
		
	for (int i = 0; i < particles.size(); i++){
		//particles[i].addForce(0,.1);
		//particles[i].addDampingForce();
		//particles[i].bounceOffWalls();
		particles[i].update();
	}
	
}

void testApp::addTrailPoint(int x, int y, int z){
	ofxVec3f myPoint = ofxVec3f(x,y,z);
	trail.push_back(myPoint);
	if(trail.size() > 250){
		trail.erase(trail.begin());
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	ofSetColor(255,255,255);
	ofBackground(0,0,0);

	ofDrawBitmapString("frameRate: " + ofToString(ofGetFrameRate()) + " | Particles: " + ofToString( (int)particles.size() ) + " | maxParticles: " + ofToString(maxParticles) + " (+/-)", 3,13);	

	/*
	ofSetColor(255,255,255,255);
	for(int i = 0; i < 32; i++){
		ofRect(i*10,0,10,spectrum[i]*2500);
		ofRect(ofGetWidth()-i*10,ofGetHeight()-spectrum[i]*2500,10,spectrum[i]*2500);
	}
	 */

	drawTrail();
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

}


void testApp::drawTrail(){
	ofSetColor(255,255,255,255);
	ofNoFill();
	ofBeginShape();
	for(int i = 0; i < trail.size(); i++){
		ofVertex(trail[i].x,trail[i].y);
	}
	ofEndShape();
	ofFill();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':
			// reposition everything: 
			for (int i = 0; i < particles.size(); i++){
				particles[i].setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}
			break;
	}
	
	
}

void testApp::emitParticles(int x, int y, int vel_x, int vel_y){
	if(particles.size() > maxParticles){
		particles.erase(particles.begin());
	}
	particle myParticle;
	myParticle.setInitialCondition(x,y,vel_x,vel_y);
	particles.push_back(myParticle);
}

void testApp::emitParticlesColor (int x, int y, int vel_x, int vel_y, int red, int green, int blue, float alpha){
	if(particles.size() > maxParticles){
		particles.erase(particles.begin());
	}
	particle myParticle;
	myParticle.setInitialCondition(x,y,vel_x,vel_y);
	myParticle.setColor(red,green,blue,alpha);
	particles.push_back(myParticle);
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	if (key == '+') {
		maxParticles++;
	}
	else if (key == '-') {
		maxParticles--; if (maxParticles <= 0)	maxParticles=0;
	}
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	float pct_x = x/ofGetWidth();
	float pct_y = y/ofGetHeight();
	int pixel_x = (int)(pct_x * 1024*3);
	int pixel_y = (int)(pct_y * 768);
	// emitParticlesColor(x, y, 0, 0, red,green,blue, 1);
	emitParticlesColor(x, y, 0, 0, 50,50,255, .45);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	mouseDown = false;
}
