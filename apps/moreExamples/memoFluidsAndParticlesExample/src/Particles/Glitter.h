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

#pragma once

#include "Particles.h"


class Glitter : public Particle {
	friend class GlitterManager;
	
protected:	
	/******* temp vars used in update *******/
	float forceAngle;
	ofxVec2f force;
	ofxVec2f pos1;
    ofxVec2f pos2;
	ofxVec2f diff;
	ofxVec2f perp;
    float xOff, yOff, per;	
	
	
	/****** main *******/

	int			trailLength;
	int			curPosIndex;						// index of where we are at currently in the array
	ofxVec2f	*positions;

	void update();
	void render();
		
public:
	Glitter(float initX, float initY, float initVelX, float initVelY, float initSize);
	~Glitter();
	
};


class GlitterManager : public ParticleManager {

	ofImage noiseMap;
	unsigned char* noisePixels;
	
public:
	GlitterManager();
	
	void add(float initX, float initY, float initVelX, float initVelY);
	float getNoiseAt(float x, float y);	// gets noise value at screen coordinates x, y. returns -1 to 1
};

