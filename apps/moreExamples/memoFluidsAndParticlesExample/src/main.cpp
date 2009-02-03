#include "ofMain.h"
#include "App.h"

//========================================================================
int main( ){

	// can be OF_WINDOW or OF_FULLSCREEN
#ifdef __WINDOWED__	
	ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW);			// <-------- setup the GL context
#else
	ofSetupOpenGL(WIDTH, HEIGHT, OF_FULLSCREEN);			// <-------- setup the GL context
#endif
	
	// this kicks off the running of my app
	ofRunApp(new App);
}
