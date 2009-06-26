#include "testApp.h"
using namespace std;


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(220, 220,250);
	//ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);
		
	noise = new Perlin(4, 4, 1, time(NULL));

	averX = ofGetWidth()/2;
	averY = ofGetHeight()/2;
	averZ = 1000;
	
	
	for(int i=0; i<numBoids; i++){
		boid[i] = new Boid(noise, &particles);
	}
	
	camDist = 1500;
	frameCounter = 0;
	#ifdef SAVE_IMAGE_SEQUENCE
	full = false;
	takeSnapShot = true;
	#else
	full = true;
	ofHideCursor();
	ofSetFullscreen(true);
	#endif
	
}

//--------------------------------------------------------------
void testApp::update(){
#ifdef SAVE_IMAGE_SEQUENCE
	frameCounter++;
	if(frameCounter<MaxParticles/20)maxParticles =frameCounter*20;
#else 
	if(frameCounter<MaxParticles/20){
		frameCounter++;
		maxParticles = frameCounter*20;
	}
#endif
	
	for(int i=0; i<numBoids; i++){
		boid[i]->mover();
		if(particles.size()<maxParticles){
			float probability = ofRandom(0, 10);
			if(probability<1){
			particles.push_back(Particles());
			particles.back().partSetup(boid[i]->p[0]->x, boid[i]->p[0]->y, boid[i]->p[0]->z, noise);
			}
		}
	}	
	for(int i=0; i<particles.size(); i++){
	if(particles[i].life==0) particles.erase(particles.begin()+i);
		particles[i].move();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
cam.place();
	

	float totalX=0, totalY=0, totalZ = 0;
	for(int i=0; i<numBoids; i++){
		boid[i]->render();
		totalX += boid[i]->p[0]->x;
		totalY += boid[0]->p[0]->y;
		totalZ += boid[0]->p[0]->z;
	}
	
	averX = totalX/numBoids;
	averY = totalY/numBoids;
	averZ = totalZ/numBoids;
	cam.goTo(averX, averY, averZ+camDist);
	
	for(int i=0; i<numBoids; i++){
		boid[i]->constrainMovement(averX, averY, averZ);
	}
	
	for(int i=0; i<particles.size(); i++){
		particles[i].render();
	}
	
#ifdef SAVE_IMAGE_SEQUENCE
		img.grabScreen(0,0,ofGetWidth(), ofGetHeight());
		string file = "teste"+ofToString(frameCounter)+".png";
		img.saveImage(file);
		cout << frameCounter<< endl;
		if(frameCounter>MaxFrames) OF_EXIT_APP(0);
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 

	if(key == 'f' or key == 'F'){
		full = !full;
		if(full){
			ofSetFullscreen(true);
			ofHideCursor();
		} else {
		ofSetFullscreen(false);
		ofShowCursor();
		}
	}
	
	if(key == ' ') std::cout << ofGetFrameRate() << std::endl;	
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
