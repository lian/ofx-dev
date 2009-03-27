#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "Thingy.h"

class testApp : public ofBaseApp {
	
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
		
	// this will be the dynamic container of our Thingy objects
	vector<Thingy> thingies;
	
};

#endif
	
