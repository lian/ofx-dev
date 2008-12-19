#include "particle.h"
#include "simulationManager.h"
#include "ofxVec3f.h"


//------------------------------------
simulationManager::simulationManager(){
		
		for (int i = 0; i < NUM_SPRINGS; i++){
		
			springs[i] 			= new spring();
			springs[i]->pta 	= (ofRandomuf() > 0.9f) ? 40	: 0;
			springs[i]->ptb 	= i+1;
			
			springs[i]->dist 	= 80.50f;
			if (i == 39) springs[i]->dist = 400;
			springs[i]->kspr 	= 5.05f;
		
		}
		
		


		

		for (int i = 0; i < NUM_PARTICLES; i++){
			
			DIVStemp[i] = new derivative();
			PTStemp[i] = new particle();
		
		}
		
		
}


//------------------------------------
void simulationManager::draw(  ){
	
	
	glColor3f(0.3,0.3,0.3);
	
	
	for (int i = 0; i < NUM_SPRINGS; i++){
	
		int pta 	= springs[i]->pta;
		int ptb 	= springs[i]->ptb;
		
		float pxa = PM->PTS[pta]->pos.x;
		float pya = PM->PTS[pta]->pos.y;
		float pxb = PM->PTS[ptb]->pos.x;
		float pyb = PM->PTS[ptb]->pos.y;
		

		ofLine(pxa, pya, pxb, pyb);
	}
	
}



//------------------------------------
void simulationManager::idle(  float dt ){
	
	

	for (int i = 0; i < NUM_PARTICLES; i++){
		memcpy(PTStemp[i],PM->PTS[i],sizeof(particle));
		PTStemp[i]->frc = 0;
	}
	
	
	
	// simulate the copy using different types of simulations
	int simulation = 1;
	switch (simulation){
	
	
		case 0:
			
			calculateForces();
      	calculateDerivatives();
      	addDerivativesToReal(dt);
      	
			break;
	
		case 1:
			
	
			calculateForces();
			calculateDerivatives();
			addDerivativesToTemp(0.5f,dt);
			
			// reset the forces!
			for (int i = 0; i < NUM_PARTICLES; i++){
				PTStemp[i]->frc = 0;
			}
			
			calculateForces();
			calculateDerivatives();
			addDerivativesToReal(dt);
			
			break;
	} 
}


//------------------------------------
void simulationManager::addDerivativesToReal(float dt){
  
   for (int i = 0; i < NUM_PARTICLES; i++){
   	
   	//printf("%f \n",  DIVStemp[i]->dp * dt);
   	
      PM->PTS[i]->pos += DIVStemp[i]->dp * dt;
      PM->PTS[i]->vel += DIVStemp[i]->dv * dt;
   
   }
   
}

//------------------------------------
void simulationManager::addDerivativesToTemp(float scale, float dt){
  
   for (int i = 0; i < NUM_PARTICLES; i++){
   	
      PTStemp[i]->pos += DIVStemp[i]->dp * scale * dt;
      PTStemp[i]->vel += DIVStemp[i]->dv * scale * dt;
   
   }
   
}


//------------------------------------
void simulationManager::calculateDerivatives(){
  
   for (int i = 0; i < NUM_PARTICLES; i++){
   
      DIVStemp[i]->dp = PTStemp[i]->vel;
      DIVStemp[i]->dv = PTStemp[i]->frc;
      
      
   	
   }
   
}



//------------------------------------
void simulationManager::calculateForces(){

	
	ofxVec3f diff;
	ofxVec3f velDiff;
	ofxVec3f unitDiff;
	float   dist;
	ofxVec3f spring_force;
	
	float k, d;
	
	bool bAFixed;
	bool bBFixed;
	
	
	for (int i = 0; i < NUM_SPRINGS; i++){
		
		int pta 	= springs[i]->pta;
		int ptb 	= springs[i]->ptb;
		bAFixed	= PTStemp[pta]->bFixed;
		bBFixed	= PTStemp[ptb]->bFixed;
		
		diff 		= PTStemp[ptb]->pos - PTStemp[pta]->pos;
		//velDiff 	= PTStemp[ptb]->vel - PTStemp[pta]->vel;
		dist 		= diff.length();
		unitDiff = diff.normalize();
		k 			= springs[i]->kspr;
		d 			= springs[i]->dist;
		
		// f = -kx  hookes law
		
	
		spring_force = (k * (d - dist)) * unitDiff;
		
		if (!bAFixed) PTStemp[pta]->frc -= spring_force; 
		if (!bBFixed) PTStemp[ptb]->frc += spring_force; 
		
	}
	
	
	// ------------------ gravity and drag -----------------
	bool bFixed;
	for (int i=0;i<NUM_PARTICLES;i++) {
		
		
		bFixed = PTStemp[i]->bFixed;
		if (!bFixed){
			//PTStemp[i]->frc += ofVec3f(0,-2.0f, 0);
		}
		
		if (!bFixed){
			PTStemp[i]->frc -= 0.2f * PTStemp[i]->vel;
		}
	}
	
	
	
	
	// ------------------ repel from!! -----------------
	ofxVec3f 	posDif;	
	ofxVec3f 	unit;
	float   	length;
	float 	force = 0;

	
	for (int i = 0; i < NUM_PARTICLES; i++){
		for (int j = 0; j < i; j++){
					
					// first calculate the vector that is the line between the two particles
					
					posDif 	= PTStemp[i]->pos - PTStemp[j]->pos;
					length 	= posDif.length();
					unit		= posDif.normalize();
					
					// use length to calc a force
					if (length > 0){
						force = (1000.0f / (length * length)); 
					} 
					
					
					// cap force for really close objects...
					if (force > 10.0f) force = 10.0f;
					
					if (!PTStemp[i]->bFixed) PTStemp[i]->frc += force * unit;
					if (!PTStemp[j]->bFixed) PTStemp[j]->frc += force * -unit;

			
		
		}	
		
	}
	
	
	
	
	
}