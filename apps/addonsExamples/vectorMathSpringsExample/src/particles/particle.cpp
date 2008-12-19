#include "particle.h"


particle::particle(){
	pos.x = 0;
	pos.y = 0;
	vel.x = 0;
	vel.y = 0;
	bAlive = false;
	bFixed = false;
}



void particle::setPropertiesAndTurnOn(float x,float y,float x_v,float y_v){
	pos.x = x;
	pos.y = y;
	vel.x = x_v;
	vel.y = y_v;
	bAlive = true;

}

void particle::update(){

}

void particle::draw(){
		
	if (bAlive == true){	
		glColor3f(1,1,1);
		ofCircle(pos.x-2,pos.y-2,4);
	}
}