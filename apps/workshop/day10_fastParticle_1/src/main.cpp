#include "ofMain.h"
#include "testApp.h"

// day_3_01: particle repulsion
// zach lieberman - thesystemis.com / zlieb@parsons.edu
// ported by artem titoulenko / owlhuntr92@gmail.com
//========================================================================
// now, we will add some new force functions into the particle class

int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new testApp());

}
