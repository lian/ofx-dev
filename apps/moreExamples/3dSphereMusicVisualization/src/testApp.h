#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxVectorMath.h"

#include "perlin.h"
#include "Ponto.h"
#include "Constants.h"
#include "Boid.h"
#ifdef GRAB_FRAME_SEQUENCE
#include "SnapShooter.h"
#endif
#include "Sphere.h"
#include "Camera.h"
#include "Particles.h"


class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		//

		Camera cam;
		
		Perlin *noise;
		int div;
		
		ofxVec3f center;
		int dist;
		int distSQ;
		
		Boid boid[NumBoids];
		float counter;
		
		Sphere sphere;
		
		vector <Particles> p;
		
		float averFFT;
			
		bool showInfo;
		bool pause;
		
		ofSoundPlayer music;
		
		#ifdef GRAB_FRAME_SEQUENCE
		SnapShooter *snapShooter;
		float totalFrames;
		#endif
		
};

#endif
