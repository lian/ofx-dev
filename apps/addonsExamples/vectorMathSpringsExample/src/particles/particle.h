#ifndef PARTICLE_H
#define PARTICLE_H


#include "ofMain.h"
#include "ofxVec3f.h"

class particle{


	public :
		
		particle();
		void setPropertiesAndTurnOn(float x,float y,float x_v,float y_v);
		void update();
		void draw();
		

		ofxVec3f 	pos;
		ofxVec3f 	vel;
		ofxVec3f	acc;
		ofxVec3f 	frc;
		
		bool	bFixed;
		bool	bAlive;

};


#endif