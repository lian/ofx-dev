
#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(50, 50, 50);
	ofSetBackgroundAuto(true);
	
	glEnableClientState( GL_VERTEX_ARRAY );  // this should be in OF somewhere.  
	glPointSize(60);
	glEnable(GL_POINT_SMOOTH);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	// touch events will be sent to myTouchListener
	ofxMultiTouch.addListener(this);
	
	bikers.loadImage("images/bikers.jpg");
	printf("bikers h %i w %i\n", bikers.width, bikers.height );
	bikers.resize( bikers.width/3, bikers.height/3);
	gears.loadImage("images/gears.gif");
	gears.resize( gears.width/2, gears.height/2);
	tdf.loadImage("images/tdf_1972_poster.jpg");
	//	tdf.setImageType(OF_IMAGE_GRAYSCALE);
	tdfSmall.loadImage("images/tdf_1972_poster.jpg");
	tdfSmall.resize(tdf.width / 4, tdf.height / 4);
	tdfSmall.setImageType(OF_IMAGE_GRAYSCALE);
	transparency.loadImage("images/transparency.png");
	bikeIcon.loadImage("images/bike_icon.png");
	bikeIcon.setImageType(OF_IMAGE_GRAYSCALE);
}


//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);
	
	bikers.draw(10,10);
	gears.draw(200,0);
	tdf.draw(100,300);
	
	ofSetColor(0xDD3333);
	tdfSmall.draw(50,300);
	
	ofSetColor(0xFFFFFF);
	ofEnableAlphaBlending();
	transparency.draw(sin(ofGetElapsedTimeMillis()/1000.0f) * 100 + 50,20);
	ofDisableAlphaBlending();
	
	
	ofSetColor(0x000000);
	
	// getting the pixels out of an image, 
	// and then use the values to draw circles
	unsigned char * pixels = bikeIcon.getPixels();
	int w = bikeIcon.width;
	int h = bikeIcon.height;
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			int value = pixels[j * w + i];
			float pct = 1 - (value / 255.0f);
			ofCircle(i*10,10 + j*10,1 + 5*pct);		
		}
	}
	
	ofSetColor(0xFFFFFF);
	bikeIcon.draw(100,200, 20,20);
}

void testApp::exit() {
	printf("exit()\n");
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	// this will never get called 
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
//	printf("mouseReleased\n");
	printf("frameRate: %.3f, frameNum: %i\n", ofGetFrameRate(), ofGetFrameNum());
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::touchDown(int x, int y, int touchId, ofxMultiTouchCustomData *data){
	printf("touch %i down at (%i,%i)\n", touchId, x,y);
}
//--------------------------------------------------------------
void testApp::touchMoved(int x, int y, int touchId, ofxMultiTouchCustomData *data){
	printf("touch %i moved at (%i,%i)\n", touchId, x,y);
}
//--------------------------------------------------------------
void testApp::touchUp(int x, int y, int touchId, ofxMultiTouchCustomData *data){
	printf("touch %i up at (%i,%i)\n", touchId, x,y);
}
//--------------------------------------------------------------
void testApp::touchDoubleTap(int x, int y, int touchId, ofxMultiTouchCustomData *data){
	printf("touch %i double tap at (%i,%i)\n", touchId, x,y);
}


