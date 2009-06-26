#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Boid.h"
//using a perlin noise class created by John Ratcliff which can be found here:
// http://www.flipcode.com/archives/Perlin_Noise_Class.shtml
#include "perlin.h"
#include "Camera.h"
#include "Particles.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		//
		
		Perlin *noise;
		Boid *boid[numBoids];
		
		vector <Particles> particles;
		GLint maxParticles;
		int frameCounter;
		
		Camera cam;
		GLint camDist;
		
		bool depthTest;
		
		float averX, averY, averZ;
		
		bool full;
		
		#ifdef SAVE_IMAGE_SEQUENCE
		ofImage img;
		bool takeSnapShot;
		#endif
};

#endif
	
