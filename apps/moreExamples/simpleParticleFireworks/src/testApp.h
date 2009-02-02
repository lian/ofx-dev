#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "particle.h"
#include "firework.h"

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
	
	void seedFirework();
	
	vector <firework> fireworks;
	
	int drawCounter;
	
	int fireworkInterval;
	int lastFireworkLaunched;
	
	
	
};

#endif
