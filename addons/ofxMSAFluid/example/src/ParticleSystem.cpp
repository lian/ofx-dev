/*
 *  ParticleSystem.cpp
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "testApp.h"
#include "ParticleSystem.h"



ParticleSystem::ParticleSystem() {
	curIndex = 0;
}


void ParticleSystem::updateAndDraw(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);       
	
	if(myApp->renderUsingVA) {
		for(int i=0; i<MAX_PARTICLES; i++) {
			if(particles[i].alpha > 0) {
				particles[i].update();
				particles[i].updateVertexArrays(i, posArray, colArray);
			}
		}    
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, posArray);
		
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colArray);
		
		glDrawArrays(GL_LINES, 0, MAX_PARTICLES * 2);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	} else {
		glBegin(GL_LINES);               // start drawing points
		for(int i=0; i<MAX_PARTICLES; i++) {
			if(particles[i].alpha > 0) {
				particles[i].update();
				particles[i].drawOldSchool();    // use oldschool renderng
			}
		}
		glEnd();
	}
	
	glDisable(GL_BLEND);
}


void ParticleSystem::addParticles(float x, float y, int count ){
	for(int i=0; i<count; i++) addParticle(x + ofRandom(-15, 15), y + ofRandom(-15, 15));
}


void ParticleSystem::addParticle(float x, float y) {
	particles[curIndex].init(x, y);
	curIndex++;
	if(curIndex >= MAX_PARTICLES) curIndex = 0;
}





