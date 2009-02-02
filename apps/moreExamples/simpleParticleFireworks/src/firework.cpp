#include "firework.h"

firework::firework(){
	damping = 0.01f;
	exploded = false;
	finished = false;
	finishedCounter = 0;
	pos = ofxVec3f(0,0,0);
	vel = ofxVec3f(0,0,0);
	frc = ofxVec3f(0,0,0);
}

void firework::seed(){
	float x = ofRandom(50,ofGetWidth()-50);
	float y = ofGetHeight();
	float z = ofRandom(-10,10);
	finished = false;
	exploded = false;
	pos.set(x,y,z);
	vel.set(0,0,0);
	frc.set(0,0,0);
	float colorSeed = ofRandom(0,3);
	particles.clear();
	for (int i = 0; i < 150; i++){
		particle myParticle;
		int color = 0xFF0000;
		float innerSeed = ofRandom(0,1)*255;
		int _red = 0;
		int _green = 0;
		int _blue = 0;
		if(colorSeed > 0 && colorSeed < 1){
			_red = 255;
			_green = innerSeed;
			_blue = innerSeed;
		} else if (colorSeed > 1 && colorSeed < 2){
			_red = innerSeed;
			_green = 255;
			_blue = innerSeed;
		} else if (colorSeed > 2 && colorSeed < 3){
			_red = innerSeed;
			_green = innerSeed;
			_blue = 255;
		}
		myParticle.setInitialCondition(0,0,0,0,0,0,_red,_green,_blue);
		particles.push_back(myParticle);
	}
	launch();
}
			
void firework::launch(){
	vel.set(0, ofRandom(-14,-11),0);
}

void firework::resetForce(){
    frc.set(0,0,0);
}

void firework::addForce(float x, float y, float z){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
	frc.x = frc.z + z;
}

void firework::addDampingForce(){
	vel.x = vel.x * (1-damping);
    vel.y = vel.y * (1-damping);
	vel.z = vel.z * (1-damping);
}

void firework::update(){
		vel = vel + frc;
		pos = pos + vel;
		if(vel.y >= .5){
			if(exploded == false){
				explode();
			}
		}
		finishedCounter = 0;
		for (int i = 0; i < particles.size(); i++){
			particles[i].resetForce();
			particles[i].addDampingForce();
			if(exploded == true){
				particles[i].addForce(ofRandom(-.01,.01),.0025,ofRandom(-.01,.01));
			}
			particles[i].update();
			int t_x = pos.x + particles[i].pos.x;
			int t_y = pos.y + particles[i].pos.y;
			int t_z = pos.z + particles[i].pos.z;
			particles[i].addTrailPoint(t_x, t_y, t_z);
			
			if(particles[i].finished == true){
				finishedCounter++;
			}
		}
		if(particles.size() > 1 && finishedCounter >= particles.size()){
			finished = true;
		}
}

void firework::explode(){
	frc.y *= .25;
	vel.y = 0;
	for (int i = 0; i < particles.size(); i++){
		float vx = cos(i/float(particles.size())*360/180.0*PI)*ofRandom(-2,2);
		float vy = sin(i/float(particles.size())*360/180.0*PI)*ofRandom(-2,2);
		float vz = ofRandom(-2,2);
		particles[i].explode(vx, vy, vz);
	}
	exploded = true;
}

bool firework::isFinished(){
	if(finished){
		return true;
	} else {
		return false;
	}
}

void firework::draw(){
	glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
	ofSetColor(0,0,0);
	ofCircle(0,0,3);
		for (int i = 0; i < particles.size(); i++){
			particles[i].draw();
		}
	glPopMatrix();
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].drawTrails();
	}
}