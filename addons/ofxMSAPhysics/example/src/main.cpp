#include "ofMain.h"
#include "testApp.h"


//========================================================================
int main( ){
	ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW);			// <-------- setup the GL context
	
	ofRunApp(new testApp());
	
}
