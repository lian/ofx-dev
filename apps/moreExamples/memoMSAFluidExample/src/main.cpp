
#include "testApp.h"

testApp *myApp;
int main( ){
	ofSetupOpenGL(1280, 720, OF_WINDOW);			// <-------- setup the GL context
	myApp = new testApp;
	ofRunApp(myApp);
}
