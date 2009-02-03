/***********************************************************************
 -----------------------------------
 
 Copyright (c) 2008, Memo Akten, www.memo.tv
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

#include "Glitter.h"
#include "App.h"


/********************* Glitter ***********************/
Glitter::Glitter(float initX, float initY, float initVelX, float initVelY, float initSize) : Particle(initX, initY, 0, 0, initSize) {
	setLifeSpan( ofRandom(GLITTER_LIFE_MIN, GLITTER_LIFE_MAX) );
	
	trailLength = GLITTER_TRAIL_LENGTH * initSize + 4;
	positions = new ofxVec2f[trailLength];
	for(int i=0; i<trailLength; i++) positions[i].set(initX, initY);
	curPosIndex = 0;
}


Glitter::~Glitter() {
	if(positions) delete positions;
}

void Glitter::update() {
	forceAngle = ((GlitterManager*)manager)->getNoiseAt(pos.x, pos.y);
	force.set(GLITTER_WIGGLE_FORCE * cos(forceAngle), GLITTER_WIGGLE_FORCE * sin(forceAngle));
	vel += force;
	
	Particle::update();
	
	if(pos.y < core_radius || pos.y > HEIGHT - core_radius) bIsDead = true;
	
    curPosIndex =  (curPosIndex + trailLength - 1) % trailLength;  // calculate new index, going backwards
	positions[curPosIndex] = pos;
}

void Glitter::render() {
	glColor4f(age, age, ofRandom(0.7f, 1.0f) * age, age);
	
	Particle::render();
	
	// RENDER TRAILS
	
    glBegin( GL_QUAD_STRIP );
	
	float fact = radius * age * GLITTER_TRAIL_RADIUS;
	
    for ( int i=0; i<trailLength - 2; i++ ) {
		pos1 = positions[((curPosIndex + i) % trailLength)];
		pos2 = positions[((curPosIndex + i + 1) % trailLength)];
		if(fabs(pos1.x - pos2.x) < (WIDTH/2)) {		// check x distance for wraparound
			
			per = (1 - (float)i/(float)(trailLength-1) );
			perp = pos1 - pos2;
			perp.perpendicular();
			
			xOff        = perp.x * per * fact;
			yOff        = perp.y * per * fact;
			
			per *= GLITTER_TRAIL_OPACITY;
			
			glColor4f( per, per, ofRandom(0.0f, per), per);
			glVertex3f( pos1.x - xOff, pos1.y - yOff, 0);
			glVertex3f( pos1.x + xOff, pos1.y + yOff, 0 );
		} else {
		    glEnd();
		    glBegin( GL_QUAD_STRIP );
		}
			
		
	}
    glEnd();
}



/********************* Glitter Manager ***********************/
GlitterManager::GlitterManager() : ParticleManager() {
	noiseMap.setUseTexture(false);
	noiseMap.loadImage("noisemap.png");	
	noisePixels = noiseMap.getPixels();
}


void GlitterManager::add(float initX, float initY, float initVelX, float initVelY) {
	addToList( new Glitter(initX, initY, initVelX, initVelY, ofRandom(GLITTER_MIN_SIZE, GLITTER_MAX_SIZE)) );
}


float GlitterManager::getNoiseAt(float scrX, float scrY) {	// gets noise value at screen coordinates x, y
	int x = ((int)(scrX * GLITTER_NOISE_SIZE)) % noiseMap.width;
	int y = ((int)(scrY * GLITTER_NOISE_SIZE)) % noiseMap.height;
	
	
	float ret = noisePixels[y * noiseMap.width + x];
	return (ret - 127.5) / 255.0 * 360 * DEG_TO_RAD * 2;
}
