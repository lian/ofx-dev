#ifndef 	PARTICLE_MANAGER
#define	PARTICLE_MANAGER

#include "ofMain.h"
#include "particle.h"


#define NUM_PARTICLES 	50



class particleManager{


	public :
		
		particleManager();
		void idle();
		void draw();
		void startParticle(float x, float y, float vx, float vy);
		
		void repelFromEdges();		

		particle * PTS[NUM_PARTICLES];
		int ptCounter;

};

#endif