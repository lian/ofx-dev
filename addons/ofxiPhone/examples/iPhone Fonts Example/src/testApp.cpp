
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
	
	// this load font loads the non-full character set
	// (ie ASCII 33-128), at size "32"
	
	char buf[1024];
	printf("cwd: %s\n", getcwd( buf, 1024 ) );
	
	printf("loading Franklin Book..\n");
	
	franklinBook.loadFont(ofToDataPath("frabk.ttf"),32);
	
	// now load another font, but with extended parameters:
	// font name, size, anti-aliased, full character set
	printf("loading Verdana..\n");
	verdana.loadFont(ofToDataPath("verdana.ttf"),8, false, true);
	verdana.setLineHeight(20.0f);
	
	counter = 0;
}


//--------------------------------------------------------------
void testApp::update(){
	counter += 1.0f;
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0x00FF00);
	franklinBook.drawString("hello, this is franklin book calling\nanyone home?", 10,40);
	
	ofSetColor(0x000000);
	verdana.drawString("hello, I am aliased verdana -- full character set,\nsee: \344 ! ", 10,100);
	
	ofSetColor(0x00FF00);
	franklinBook.drawString("I can't make an\n (\344) like you", 10,150);
	
	ofSetColor(0x000000);
	verdana.drawString("yeah, but I'm not exactly pretty\nthe problem is with freeType library...\napple has a patent on TTF font hints\nso our aliased type via freeType isn't super looking", 10,210);
	
	ofSetColor(0x00FF00);
	franklinBook.drawString("you look ok !\n don't worry", 10,300);
	
	
	//------------------- bounding rectangle : 
	char tempString[255];
	sprintf(tempString,"%f", ofGetElapsedTimef());
	// ok first job to rotate around the center, is to get the bounding box:
	ofRectangle rect = franklinBook.getStringBoundingBox(tempString, 0,0);
	// this is the actual midpt (x + w/2, y + h/2);
	float centerx = rect.x + rect.width / 2;
	float centery = rect.y + rect.height / 2;
	
	glPushMatrix();
	glTranslatef(50,400,0);
	glRotatef(counter, 0,0,1);
	// draw type & rect centered around 0,0 (subtract midpt from both):
	ofSetColor(0xcccccc);
	ofRect(rect.x - centerx, rect.y - centery, rect.width, rect.height);
	ofSetColor(0xff3399);
	franklinBook.drawString(tempString, -centerx,-centery);
	glPopMatrix();
	
	// -------------------------------------
	
	glPushMatrix();
	
	glTranslatef(50,400,0);
	glScalef(5,5,1);
	ofSetColor(0x333333);
	verdana.drawString("scale 5x!",0, 0);
	glPopMatrix();
	
	float size = 2 + 1.5*sin(ofGetElapsedTimef());
	glPushMatrix();
	glTranslatef(100,400,0);
	glScalef(size,size,1);
	ofSetColor(0x00FF00);
	franklinBook.drawString("$k@!%",0, 0);
	glPopMatrix();
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


