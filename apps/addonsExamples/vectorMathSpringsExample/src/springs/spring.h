#ifndef SPRING
#define SPRING

#include "particleManager.h"

// based on hooke's law f = -kx where k is spring constant, x is distention


class spring{


	public :
		
		
		spring();
				
		// who am I connecting?
		int pta; 
		int ptb;
   	
   	// k spring constant and distance
   	float kspr;
   	float dist;

};



#endif