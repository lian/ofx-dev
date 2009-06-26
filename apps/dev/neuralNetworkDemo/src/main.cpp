#include "ofMain.h"
#include "testApp.h"

int main( ){
	ofSetupOpenGL(width, height, OF_WINDOW);
	ofRunApp(new testApp);
}
