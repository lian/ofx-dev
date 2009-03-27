#include "particle.h"


//------------------------------------------------------------
particle::particle(){
	damping = 0.01f;
	
	red = 0;
	green = 0;
	blue = 0;
	glow = 0;
	
	finalRed = 0;
	finalGreen = 0;
	finalBlue = 0;
	
	exploded = false;
	
	lifeSpan = ofRandom(1000,2000);
	finished = false;
	
	pos.set(0,0,0);
	vel.set(0,0,0);
	frc.set(0,0,0);
	
	opacity = 255.0f;
	
	image.loadImage("glow.png");
}

//------------------------------------------------------------
void particle::resetForce(){
    frc.set(0,0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y, float z){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
	frc.z = frc.z + z;
}

//------------------------------------------------------------
void particle::addDampingForce(){	
    vel.x = vel.x * .99;
    vel.y = vel.y * .99;
	vel.z = vel.z * .99;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float pz, float vx, float vy, float vz, int f_red, int f_green, int f_blue){
    pos.set(0,0,0);
	vel.set(0,0,0);
	frc.set(0,0,0);
	
	finished = false;
	exploded = false;
	
	finalRed = f_red;
	finalGreen = f_green;
	finalBlue = f_blue;
	
	red = 240;
	green = ofRandom(175,255);
	blue = ofRandom(0,50);
}

//------------------------------------------------------------
void particle::update(){	
	vel = vel + frc;
	pos = pos + vel;
	glow += ofRandom(-10,10);
	if(exploded == true){
		opacity = 255 - ((((float)ofGetElapsedTimeMillis() - (float)timeExploded) / (float)lifeSpan) * 255.0f);
		// cout << opacity << endl;
	}
	if(exploded == true && ofGetElapsedTimeMillis() - timeExploded >= lifeSpan){
		finished = true;
	}
}

//------------------------------------------------------------
void particle::explode(float vx, float vy, float vz){
	timeExploded = ofGetElapsedTimeMillis();
	exploded = true;
	vel.set(vx,vy,vz);
}

void particle::addTrailPoint(int x, int y, int z){
	ofxVec3f myPoint = ofxVec3f(x,y,z);
	trail.push_back(myPoint);
	if(trail.size() > 15){
		trail.erase(trail.begin());
	}
}



//------------------------------------------------------------
void particle::draw(){
	if(finished == false){
		if(exploded == true){
			//float opacity = (lifeSpan / (ofGetElapsedTimeMillis() - timeExploded))*255;
			ofSetColor(finalRed, finalGreen, finalBlue);
		} else {
			ofSetColor(red,green,blue,opacity);
		}
		glPushMatrix();
			glTranslatef(pos.x, pos.y,pos.z);
		image.draw(0,0,4,4);
		glPopMatrix();
	}
}

//------------------------------------------------------------
void particle::drawTrails(){
	if(exploded == true){
		//float opacity = (lifeSpan / (ofGetElapsedTimeMillis() - timeExploded))*255;
		ofSetColor(finalRed, finalGreen, finalBlue);
	} else {
		ofSetColor(red,green,blue,opacity);
	}
	for(int i = 0; i < trail.size(); i++){
		if(trail[i].x != 0 && trail[i].y != 0 && trail[i].z != 0){
			glPushMatrix();
				glTranslatef(trail[i].x,trail[i].y,trail[i].z);
			int size = 0;
			if(i > 5){
				size = 5;
			} else {
				size = i;
			}
			image.draw(0,0,size,size);
			glPopMatrix();
		}
	}
}