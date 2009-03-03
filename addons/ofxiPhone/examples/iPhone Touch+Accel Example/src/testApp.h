#pragma once

#include "ofMain.h"
#include "ofxMultiTouch.h"
#include "ofxAccelerometer.h"

class testApp : public ofSimpleApp, public ofxMultiTouchListener  {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key) {}
	void keyReleased(int key)  {}
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void mouseReleased(int x, int y, int button );
	
	void touchDown(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchMoved(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchUp(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchDoubleTap(int x, int y, int touchId, ofxMultiTouchCustomData *data = NULL);
	
};

