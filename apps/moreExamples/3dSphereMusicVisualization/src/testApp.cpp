#include "testApp.h"
using namespace std;


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(3, 2, 2);
	#ifndef GRAB_FRAME_SEQUENCE
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	#endif
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	center.x = ofGetWidth()/2;
	center.y = ofGetHeight()/2;
	center.z = 0;
	
	noise = new Perlin(4, 4, 1, time(NULL));
	for(int i=0; i<NumBoids; i++){
		boid[i].rotX = ofRandom(0, 360);
		boid[i].rotY = ofRandom(0, 360);
	}
	counter = 0;

	pause = false;
	
	music.loadSound("music.mp3");
	
	music.play();
	music.setVolume(1);
	
#ifdef GRAB_FRAME_SEQUENCE
	totalFrames = (float)music.length/music.internalFreq*30;
	snapShooter = new SnapShooter("teste", totalFrames, true);
#endif
	
	sphere.camPos = &cam.pos;
	
	for(int i=0; i<NumBoids; i++){
		boid[i].partPtr = &p;
	}
	cam.pos.x = 0;
	cam.pos.y = center.y;
	cam.pos.z = 9000;
	cam.center = &center;
	for(int i=0; i<NumBoids; i++){
		boid[i].camPos = &cam.pos;
	}		
}

//--------------------------------------------------------------
void testApp::update(){
#ifdef GRAB_FRAME_SEQUENCE
	float playHeadPos = counter/totalFrames;
	music.setPosition(playHeadPos);
#endif


	counter++;
	
	float *fftList = ofSoundGetSpectrum(NumBands);
	
	float totalFFT = 0;
	for(int i=0; i<NumBands; i++){
		totalFFT += fftList[i]*50;
	}
	averFFT = totalFFT / NumBands;
	
	//boids
	for(int i=0; i<NumBoids; i++){
		float div = 3000;
		float fftVal = fftList[boid[i].band] * 50; 
		float targetRadius = averFFT*300+fftVal*10;
		boid[i].updateRadius(targetRadius);
		ofxVec3f rot = ofxVec3f(0, 0, boid[i].radius);
		float radRotX = noise->Get(boid[i].p[0].pos.y/div, (boid[i].p[0].pos.z+counter*10)/div)*TWO_PI;
		float radRotY = noise->Get(boid[i].p[0].pos.x/div, (boid[i].p[0].pos.y+counter*10)/div)*TWO_PI;
		int step = 3;
		boid[i].rotX += cos(radRotX)*(averFFT*50)+ofRandom(-step, step);
		boid[i].rotY -= sin(radRotY)*(averFFT*50)+ofRandom(-step, step);
		float alpha = fftVal*40;
		rot.rotate(boid[i].rotX, boid[i].rotY, 0);
		ofxVec3f pos = center + rot;
		boid[i].move(pos, alpha);
	}	
	
	
	//sphere
	
	for(int i=0; i<SphereNumRows; i++){
		for(int j=0; j<SphereNumRows; j++){
			float fftVal = fftList[sphere.p[i][j].band] * 50;
			float targetRadius = fftVal*200;
			float targetAlpha = fftVal*0.2;
			sphere.p[i][j].updateRadius(targetRadius);
			sphere.p[i][j].updateAlpha(targetAlpha);
		}
	}
	sphere.move(); 
	
	//particles
	if(averFFT >0.5){
		int toAdd =  abs((int)(averFFT*AddMult));
		
		for(int i=0; i<toAdd; i++){
			int whichBoid = (int)ofRandom(0, NumBoids);
			ofxVec3f iniPos = boid[whichBoid].p[0].pos;
			ofxVec3f iniVel = boid[whichBoid].p[0].vel*2;
			p.push_back(Particles(iniPos, iniVel, noise, &cam.pos));
		}
	}
	for(int i=0; i<p.size(); i++){
		if(p[i].life<=0) p.erase(p.begin()+i);
		else{
			p[i].move();
		}
	}
	cam.move();
}

//--------------------------------------------------------------
void testApp::draw(){

	cam.place();

	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glRotatef(sphere.rotX, 1, 0, 0);
	glRotatef(sphere.rotY, 0, 1, 0);
	sphere.render();
	glPopMatrix();
		

	for(int i=0; i<NumBoids; i++){
		boid[i].render();
	}
	
	for(int i=0; i<p.size(); i++){
		p[i].render();
	}
	
	#ifdef GRAB_FRAME_SEQUENCE
	snapShooter->grabFrame();	
	#endif
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
if(key == 'i' or key == 'I') cout << ofGetFrameRate() << endl;
if(key == 'p' or key == 'P') {
	pause = !pause;
	music.setPaused(pause);
}

    
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
