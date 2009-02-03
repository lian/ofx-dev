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


class Ball : public Particle {
	friend class BallManager;

protected:	
	bool bDrawLine;							// if true...
	float lineX, lineY;//, lineAlpha;			//  draw a line to lineX, lineY with alpha
	
	bool doGravityAndCollision(Ball* ball2);
	
	void update();
	void render();
		
public:
	Ball(float initX, float initY, float initVelX, float initVelY, float initSize);
};


class BallManager : public ParticleManager {
	uint lastTriggerCounter;
	
public:
	void update();
	void add(float initX, float initY, float initVelX, float initVelY);
};

