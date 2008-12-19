
#include "particleManager.h"



particleManager::particleManager(){
	
	
	for (int i = 0; i < NUM_PARTICLES; i++){
		PTS[i] = new particle();
		PTS[i]->bAlive = true;
		PTS[i]->pos.x = 500 + ofRandomuf() * 200;
		PTS[i]->pos.y = 500 + ofRandomuf() * 200;
	}
	
	PTS[0]->bFixed = true;
}


void particleManager::draw(){

	for (int i = 0; i < NUM_PARTICLES; i++){
		PTS[i]->draw();	
	}

}



