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
 
#include "FluidTexture.h"
#include <list>
#include "ofxVectorMath.h"


class ParticleManager;

class Particle {
	friend class ParticleManager;
	
protected:

	/******* temp vars used in update *******/
	float fluidInfo[4];			// stores the 4 variables from fluid 
	float speed2;
	float drag;
	float density;
	
	
	/****** main *******/

	ofxVec2f pos;
	ofxVec2f vel;
	ofxVec2f oldPos;

	float decay;
	float age;
	bool bIsDead;

	float targetSize;
	float size;	
	float radius;	
	float core_radius;			// current radius of ball core (solid area)	
	
	virtual void update();
	virtual void render();
	
	ParticleManager *manager;
	
	float maxSpeed;
	float fluidVelMult;
	float coreSizeMult;			// cache these locally
	FluidTexture *fluid;	
	
	void setLifeSpan(float seconds);
	void setLifeSpan(float secondsMin, float secondsMax);
	
public:	
	Particle(float initX, float initY, float initVelX, float initVelY, float initSize);

	void setManager(ParticleManager *_manager);
};




class ParticleManager {
	friend class Particle;

protected:
	float		maxSpeed;
	float		fluidVelMult;
	float		coreSizeMult;		// multiplier for how much of the visible radius is actually for the solid core
	FluidTexture *fluid;

	int			maxCount;
	ofImage		image;
	
public:
	list<Particle*> particles;

	~ParticleManager();
	
	void init(float _maxSpeed, float _fluidVelMult, float _coreSizeMult,  FluidTexture *_fluid, int _maxCount, char* imageURL);
	void addToList(Particle* particle);
	virtual void update();
	virtual void render();
};

