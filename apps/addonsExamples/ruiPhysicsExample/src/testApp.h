#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxPhysics2d.h"
#define MAX_PARTICLES 200

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	
	ofxPhysics2d*physics;
	ofxParticle* mouseParticle;
	ofxSpring*mouseSpring;
	ofxParticle* newParticle;
	bool bCreateParticles;
	float newParticleIncrement;
	
	bool bCreateParticleString;
	ofxParticle* beginParticleString;
	ofxParticle* endParticleString;
	vector<ofxParticle*>particles;
	void createParticleString(ofxParticle*begin, ofxParticle*end, int numParticles);
};

#endif
