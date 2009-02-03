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

#include "Particles.h"
#include "App.h"

/********************* Particle ***********************/

Particle::Particle(float initX, float initY, float initVelX, float initVelY, float initSize) {
	targetSize = initSize;
	size = 0;
	radius	= size * 0.5f;	
	
	pos.set( initX, initY ); 
	vel.set( initVelX, initVelY ); 
	
	age         = 1.0f;
	setLifeSpan(0.0f);
	
	bIsDead = false;
}


void Particle::setLifeSpan(float seconds) {
	if(seconds) decay = 1.0f / (30.0f * seconds);		// if given a life span, calculate amount of decay
	else decay = 0.0f;									// otherwise set decay to zero
}

void Particle::setLifeSpan(float secondsMin, float secondsMax) {
	setLifeSpan( ofRandom( secondsMin, secondsMax) );
}



void Particle::setManager(ParticleManager *_manager) {	
	manager			= _manager;
	
	maxSpeed		=  manager->maxSpeed;
	fluidVelMult	=  manager->fluidVelMult;
	coreSizeMult	=  manager->coreSizeMult;
	fluid			=  manager->fluid;
}


void Particle::update() {
	// update size
	if(size < targetSize * 0.98f) {
		size			+= (targetSize - size) * 0.1f;
		radius			= size * 0.5f;
		core_radius		= radius * manager->coreSizeMult;
	}
	
	// add velocity drag and speed if it exists
	if(fluidVelMult) {
		fluid->getInfo(pos.x * INV_WIDTH, pos.y  * INV_HEIGHT, fluidInfo);
		density =  fluidInfo[FLUID_INFO_DENSITY];

		speed2 = vel.lengthSquared();

		drag = 0.99f - density * BALL_DRAG_AMOUNT * speed2;
		
		vel.x += fluidInfo[FLUID_INFO_U] * WIDTH * density * fluidVelMult / speed2 * ofRandom(0, 1);
		vel.y += fluidInfo[FLUID_INFO_V] * HEIGHT * density * fluidVelMult / speed2 * ofRandom(0, 1);;
	} else {
		drag = 1.0f;
	}
	
	if(maxSpeed > 0) vel.limit(maxSpeed);
	
	pos += vel;
	
	
    if(pos.x < -radius) {
		drag = 1.0f;
		pos.x = WIDTH + radius;
		oldPos.x = pos.x - vel.x;
    } else if(pos.x > WIDTH + radius) {
		drag = 1.0f;
		pos.x = -radius;
		oldPos.x = pos.x - vel.x;
    }

	vel *= drag;
	
	
	oldPos = pos;
	
	if(decay) {
		age -= decay;
		if(age <= 0) bIsDead = true;
	}

}

void Particle::render() {
	manager->image.draw(pos.x - radius, pos.y - radius, size, size);
}


/********************* Particle Manager ***********************/
void ParticleManager::init(float _maxSpeed, float _fluidVelMult, float _coreSizeMult,  FluidTexture *_fluid, int _maxCount, char* imageURL) { 
	maxSpeed		= _maxSpeed;
	fluidVelMult	= _fluidVelMult;
	coreSizeMult	= _coreSizeMult;
	fluid			= _fluid;
	
	maxCount		= _maxCount;
	image.loadImage(imageURL);
}

ParticleManager::~ParticleManager() {
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle* particle = *it;
		it = particles.erase(it);
		if(particle) delete particle;
	}
}



void ParticleManager::addToList(Particle* particle) {
	particles.push_back(particle);
	particle->setManager(this);
	
	if(particles.size() > maxCount) {					// if we reached maximum number of particles
		Particle *firstParticle = particles.front();		// get pointer to first particle in list
		if(firstParticle) {									// if its not null (it exists)
			particles.pop_front();								// remove from list
			delete firstParticle;								// and delete it from memory
		}
	}
	
	//printf("ParticleManager::addToList now with %i particles \n", particles.size());
}


void ParticleManager::update() {
	//	printf("ParticleManager::update() with %i particles \n", particles.size());
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle* particle = *it;
		if(particle->bIsDead) {
			it = particles.erase(it);
			delete particle;
//			printf("deleting particle of old age\n");
		} else {
			particle->update();
		}
	}
}

void ParticleManager::render() {
	//	printf("ParticleManager::render() with %i particles \n\n", particles.size());
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle* particle = *it;
		particle->render();
		//		printf(" %.4f \n", particle->radius);	
	}
}