#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofAddons.h"
#include "ofxCamera.h"
#include "ofxLight.h"

#include "perlin.h"
#include "Constants.h"
#include "Emitter.h"

#include "Particles.h"


class testApp : public ofBaseApp {
	
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
		
		bool bFullScreen;
		bool doTail;
		int mode;
		
		Perlin *noise;
		int div;
		
		ofxVec3f center;
		int dist;
		int distSQ;
		
		Emitter emitters[NumEmitters];
		float counter;
		
	
		
		vector <Particles> p;
		
		float averFFT;
			
		bool showInfo;
		bool pause;
		
		ofSoundPlayer music;
		
		#ifdef GRAB_FRAME_SEQUENCE
		SnapShooter *snapShooter;
		float totalFrames;
		#endif
		
		void updateEmitters();
		void updateParticles();
		
		
		//
		
		ofxCamera camera;
		
		ofxLight light1; //this will be a directional light
		ofxLight light2; //this one a spot light
		ofxLight light3; //and this one a point light
		
		float centerX, centerY, centerZ;
		float rotX, rotY;
		
		bool bSmoothLight;
		float camX, camY, camZ;
		
		
};

#endif
	
