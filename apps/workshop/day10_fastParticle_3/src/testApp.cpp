#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(0,0,0);
	
	ofSetCircleResolution(5);
	
	
	for (int i = 0; i < 400; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
	mouseX=ofGetWidth()/2;
	mouseY=ofGetHeight()/2;
	
	useBinning = true;
	s=0;
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	

		//im sorting the particles into bins based on their x position so i dont have to compare as many = speed increase
			
		for(int i=0; i<numBins; i++) // first clear all the bins from last time
		{
			bin[i].clear();
		}
		
		for(int i=0; i<particles.size(); i++) // go through all of the particles and put references to them in the correct bins
		{
			if(particles[i].pos.x>0 && particles[i].pos.x < ofGetWidth() )
			{
				bin[int(particles[i].pos.x / binWidth)].push_back(&particles[i]); //put each particle in a bin relative to its x position.
			}
			else if(particles[i].pos.x<0) // if they're off the screen on either side, put them in the last bin on that side
			{
				bin[0].push_back(&particles[i]); // the & symbol pushes back a pointer to the particle
			}
			else
			{
				bin[numBins-1].push_back(&particles[i]);
			}
		}
		
	s+=0.1f;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	goThroughBins();
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
		particles[i].update();
	}
	
	
	ofSetColor(255,255,255,125);
	glLineWidth(3);
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	

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

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	
	useBinning = !useBinning; // press any key to turn off binning and see the speed difference
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	particles.erase(particles.begin());
	particle myParticle;
	myParticle.setInitialCondition(x,y,0,0);
	particles.push_back(myParticle);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}

void testApp::goThroughBins()
{
	for(int b=0; b<numBins; b++) // go through all the bins
	{
		for(int i = 0; i < bin[b].size(); i++) //comapre each particle in a bin to all the other particles in the bin
		{
			bin[b][i]->addAttractionForce(mouseX, mouseY, 1000, 0.8f);
			
			for (int j = 0; j < i; j++){
				particleToParticle(bin[b][i], bin[b][j]);			
			}
			
			if(b>0) // check for close nodes in prev bin to avoid lines of particles on the edges of bins
			{
				for (int j = 0; j < bin[b-1].size(); j++){
					particleToParticle(bin[b][i], bin[b-1][j]);
					 // basically you want whatever to happen when compare two nodes to go here
				}
			}
			
			if(b<numBins-1) // check for close nodes in next bin to avoid lines of particles on the edges of bins
			{
				for (int j = 0; j < bin[b+1].size(); j++){
					particleToParticle(bin[b][i], bin[b+1][j]);
				}
			}
			
		}
	}
}

void testApp::particleToParticle(particle * p1, particle * p2)
{
	float yDist = ABS(p1->pos.y-p2->pos.y);
	float xDist = float(ABS(p1->pos.x-p2->pos.x))/300;
	if(yDist<16)
	{
		glLineWidth(10);
		yDist/=16;
		xDist*=yDist;
		ofSetColor((xDist*255)-(255-xDist*255),255-xDist*255,xDist*255,xDist*100);
		ofLine(p1->pos.x,p1->pos.y, p2->pos.x, p2->pos.y);
	}
	
	p1->addRepulsionForce(p2, binWidth, 0.2);
}
