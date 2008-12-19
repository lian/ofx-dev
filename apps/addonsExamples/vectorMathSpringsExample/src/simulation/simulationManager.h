
#include "ofMain.h"
#include "particleManager.h"
#include "spring.h"

#define 	NUM_SPRINGS			(NUM_PARTICLES-1)


typedef struct{

	ofxVec3f 	dp;
	ofxVec3f		dv;

} derivative;



class simulationManager{


	public :
		
		simulationManager();
		
		void idle();
		
		particleManager * PM;
		
		// for simulation!
		particle 		 * PTStemp[NUM_PARTICLES];
		derivative		 * DIVStemp[NUM_PARTICLES];
		
		
		void 			idle(float dt);	
		void 			addDerivativesToReal(float dt);
		void 			addDerivativesToTemp(float scale, float dt);
		void 			calculateDerivatives();
		void 			calculateForces();
		
		
		spring			 * springs[NUM_SPRINGS];
		
		void 			draw();

};


