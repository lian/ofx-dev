#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(200,200, OF_WINDOW);
	
	ofRunApp(new testApp);
	
}
