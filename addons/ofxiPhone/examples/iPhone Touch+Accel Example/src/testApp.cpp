
#include "testApp.h"


#define NUM_POINTS				10
#define BOUNCE_FACTOR			0.5
#define ACCELEROMETER_FORCE		0.2


class Thing {
public:
	ofPoint pos;
	ofPoint vel;
	ofColor col;
	
	void init() {
		pos.set(ofRandomWidth(), ofRandomHeight(), 0);
		vel.set(ofRandomf(), ofRandomf(), 0);
		
		col.r = ofRandom(0, 255);
		col.g = ofRandom(0, 255);
		col.b = ofRandom(0, 255);
		col.a = ofRandom(0, 255);
	}
	
	void update() {
		vel.x += ACCELEROMETER_FORCE * ofxAccelerometer.getForce().x * ofRandomuf();
		vel.y += -ACCELEROMETER_FORCE * ofxAccelerometer.getForce().y * ofRandomuf();		// this one is subtracted cos world Y is opposite to opengl Y
		
		// add vel to pos
		pos += vel;
		
		// check boundaries
		if(pos.x < 0) {
			pos.x = 0;
			vel.x *= -BOUNCE_FACTOR;
		} else if(pos.x >= ofGetWidth()) {
			pos.x = ofGetWidth()-BOUNCE_FACTOR;
			vel.x *= -BOUNCE_FACTOR;	
		}
		
		if(pos.y < 0) {
			pos.y = 0;
			vel.y *= -BOUNCE_FACTOR;
		} else if(pos.y >= ofGetHeight()) {
			pos.y = ofGetHeight()-BOUNCE_FACTOR;
			vel.y *= -BOUNCE_FACTOR;	
		}
	}
	
	void draw() {
		ofSetColor(col.r, col.g, col.b, col.a);
		ofCircle(pos.x, pos.y, 30);
	}
	
	void moveTo(int x, int y) {
		ofPoint oldPos = pos;
		pos.set(x, y, 0);
		vel.set(0, 0, 0);
	}
};


Thing things[NUM_POINTS];

//--------------------------------------------------------------
void testApp::setup(){	
	printf("setup()\n");
	
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(true);
	ofSetFrameRate(60);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();

	// touch events will be sent to this class (testApp)
	ofxMultiTouch.addListener(this);
	
	for(int i=0; i<NUM_POINTS; i++) things[i].init();
}


//--------------------------------------------------------------
void testApp::update(){
//	printf("update()\n");
	for(int i=0; i<NUM_POINTS; i++) things[i].update();
}

//--------------------------------------------------------------
void testApp::draw(){
//	printf("draw()\n");
	for(int i=0; i<NUM_POINTS; i++) things[i].draw();
}

void testApp::exit() {
	printf("exit()\n");
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	printf("mouseMoved: %i, %i\n", x, y);	// this will never get called 
	
}

// mouse functions are there for backwards compatibility
// they are simply the first finger to touch the screen
// you can omit the mouse functions and just use touch functions
// or omit touch functions and just use mouse functions if you don't need multitouch
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	printf("mouseDragged: %i, %i %i\n", x, y, button);
	things[0].moveTo(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	printf("mousePressed: %i, %i %i\n", x, y, button);
	things[0].moveTo(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	//	printf("mouseReleased\n");
	printf("frameRate: %.3f, frameNum: %i\n", ofGetFrameRate(), ofGetFrameNum());
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	printf("mouseReleased: %i, %i %i\n", x, y, button);
	//	ofSetFrameRate(1);
}


//--------------------------------------------------------------
void testApp::touchDown(int x, int y, int touchId, ofxMultiTouchCustomData *data) {
	printf("touchDown: %i, %i %i\n", x, y, touchId);
	things[touchId].moveTo(x, y);
}


void testApp::touchMoved(int x, int y, int touchId, ofxMultiTouchCustomData *data) {
	printf("touchMoved: %i, %i %i\n", x, y, touchId);
	things[touchId].moveTo(x, y);
}


void testApp::touchUp(int x, int y, int touchId, ofxMultiTouchCustomData *data) {
	printf("touchUp: %i, %i %i\n", x, y, touchId);
}

void testApp::touchDoubleTap(int x, int y, int touchId, ofxMultiTouchCustomData *data) {
	printf("touchDoubleTap: %i, %i %i\n", x, y, touchId);
	ofToggleFullscreen();
}

