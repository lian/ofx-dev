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

#include "Balls.h"
#include "App.h"


/********************* BALL ***********************/

Ball::Ball(float initX, float initY, float initVelX, float initVelY, float initSize) : Particle(initX, initY, initVelX, initVelY, initSize) {
	lineX = lineY = 0;//lineAlpha = 0;
	bDrawLine = false;
	setLifeSpan(initSize * BALL_SIZE_LIFE_MULT);
}


void Ball::update() {
//	printf("Ball update  \n");
	
	vel.y += BALL_GRAVITY;
	Particle::update();
	
	if(pos.y < core_radius) {
		vel.y *= -1;
		pos.y = core_radius;
	} else if(pos.y > HEIGHT - core_radius) {
		vel.y *= -1;
		if(vel.y > -10) vel.y = -10;
		pos.y = HEIGHT - core_radius;
	}
	
	fluid->addAtNorm(pos.x * INV_WIDTH, pos.y * INV_HEIGHT, vel.x * INV_WIDTH, vel.y * INV_HEIGHT, BALL_FLUID_CREATE, BALL_FLUID_SPEED, ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1));
	
}


bool Ball::doGravityAndCollision(Ball* ball2) {
//	Ball* ball1 = this;		// can't be bothered to changet the function 
	
    float dx = ball2->pos.x - pos.x;
    float dy = ball2->pos.y - pos.y;
    float r2 = dx*dx + dy*dy;
	float minR = core_radius + ball2->core_radius;
	if(r2>minR * minR * 0.2) {		// if we are more than a tenth of the minimum radius apart
		float r = sqrt(r2);
		float force = BALL_BALL_ATTRACTION * core_radius * ball2->core_radius / r2;
		float ax = force * dx / r;
		float ay = force * dy / r;
		vel.x += ax / core_radius;
		vel.y += ay / core_radius;
		ball2->vel.x -= ax / ball2->core_radius;
		ball2->vel.y -= ay / ball2->core_radius;
		if(r2<BALL_LINE_THRESH) {
			bDrawLine = true;
			lineX = ball2->pos.x;
			lineY = ball2->pos.y;
		}
		return false;
	} else {
//		targetSize = MAX(targetSize, ball2->targetSize) + MIN(targetSize, ball2->targetSize) * 0.5f;
		//		targetSize += ball2->targetSize;
//		vel.x += ball2->vel.x;
//		vel.y += ball2->vel.y;
//		size = 0;
//		return true;
	}
	return false;
}



void Ball::render() {
	glColor4f(age, age, age, 1.0f);
	Particle::render();		// render particle
	
	if(bDrawLine) {			// and line
	    float dx = lineX - pos.x;
		float dy = lineY - pos.y;
		float r2 = dx*dx + dy*dy;
		if(r2<BALL_LINE_THRESH) {
			ofEnableSmoothing();	
			ofSetColor(255, 255, 255, (BALL_LINE_THRESH - r2)* 255.0f / BALL_LINE_THRESH);
			ofLine(pos.x, pos.y, lineX, lineY);
			ofDisableSmoothing();	
		} else {
			bDrawLine = false;
		}
	}
	
}

 
 
 /********************* BALL Manager ***********************/

void BallManager::add(float initX, float initY, float initVelX, float initVelY) {
	if(lastTriggerCounter > BALL_FRAMES_BEFORE_TRIGGER) {
		lastTriggerCounter = 0;
		addToList( new Ball(initX, initY, initVelX, initVelY, ofRandom(BALL_MIN_SIZE, BALL_MAX_SIZE)) );
	}
}



void BallManager::update() {
//	printf("BallManager::update() with %i particles \n", particles.size());
	lastTriggerCounter ++;
	ParticleManager::update();
	
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Ball* ball1 = (Ball*) *it;
		for (list<Particle*>::iterator it2 = it; it2 != particles.end(); it2++) {
			Ball* ball2 = (Ball*) *it2;
			if(ball1 != ball2) {
				bool bCollided = ball1->doGravityAndCollision(ball2);
//				if(bCollided) {
//					printf("ERASING BALL\n");
//					ball2->bIsDead = true;		// erase next frame
//				}
			}
		}
	}
}

