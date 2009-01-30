#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

    vidWidth = 320;
    vidHeight = 240;

    ffGL_1 = true;
    ffGL_2 = true;
    ffGL_3 = true;

	ofBackground(255, 255, 255);

	//for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

    /// allocate data for the FFGL host
    ffHost.allocate(vidWidth, vidHeight, GL_RGBA);

    // load the FFGL plugins
#if _WIN32
    ffHost.loadPlugin("FFGLMirror.dll");
    ffHost.loadPlugin("FFGLHeat.dll");
    ffHost.loadPlugin("FFGLTile.dll");
	
#elif TARGET_OS_MAC
    ffHost.loadPlugin("FFGLMirror");
    ffHost.loadPlugin("FFGLHeat");
    ffHost.loadPlugin("FFGLTile");
	
#else
    ffHost.loadPlugin("FFGLMirror.so");
    ffHost.loadPlugin("FFGLHeat.so");
    ffHost.loadPlugin("FFGLTile.so");
#endif
    
    // turn on all the plugins
    // the first parameter is the plugin index
    ffHost.setPluginActive(0, ffGL_1);
    ffHost.setPluginActive(1, ffGL_2);
    ffHost.setPluginActive(2, ffGL_3);

#ifdef USE_LIVE_VIDEO    
	video.initGrabber(vidWidth, vidHeight);
#else
    video.loadMovie("fingers.mov");
	video.play();
#endif
    
    // set the horizontal mirror parameter switch to ON
    ffHost.setPluginFloatParameter(0, 0, 1.0);  // plugin 0, param 0, value 1

}

//--------------------------------------------------------------
void testApp::update() {

#ifdef USE_LIVE_VIDEO    
	video.grabFrame();
	if (video.isFrameNew()) {
#else
    video.idleMovie();
    if (true) {
#endif
        // load new pixel data into the FFGL host
		ffHost.loadData(video.getPixels(), vidWidth, vidHeight, GL_RGB);
        // apply all active plugins to the pixels
        ffHost.process();
    }

}

//--------------------------------------------------------------
void testApp::draw() {
    
	ofSetupScreen();

    ofSetColor(255,255,255);
    // draw the raw video
    video.draw(MARGIN, MARGIN, vidWidth, vidHeight);
    // draw the processed video
    ffHost.draw(vidWidth + MARGIN*2, MARGIN, vidWidth, vidHeight);

    // print instructions
    ofSetColor(255, 128, 0);
    ofDrawBitmapString(string(" Freeframe 1.5_FFGL OF_Host "), MARGIN, 280);
    ofDrawBitmapString(string(" Press (1 : Mirror)  (2 : Heat)  (3 : Tile) to toggle effects. "), MARGIN, 300);
    ofDrawBitmapString(string(" Mouse controls \"Tile\" parameters. "), MARGIN, 320);

    // print frame rate in the window's title
    char* s = new char[24];
    sprintf(s, "ofxFreeFrame - %d fps\n", int(ofGetFrameRate()));
    glutSetWindowTitle(s);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    switch (key) {
#ifdef USE_LIVE_VIDEO 
        case '0' :  video.videoSettings();
                    break;
#endif
        case '1' :  ffGL_1 = !ffGL_1;
                    ffHost.setPluginActive(0, ffGL_1);
                    break;
        case '2' :  ffGL_2 = !ffGL_2;
                    ffHost.setPluginActive(1, ffGL_2);
                    break;
        case '3' :  ffGL_3 = !ffGL_3;
                    ffHost.setPluginActive(2, ffGL_3);
                    break;
        default :
                    break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
    
    // set Tile plugin parameters using the mouse coordinates
    // param 0 is the number of horizontal tiles
    ffHost.setPluginFloatParameter(2, 0, MIN(MAX(x - MARGIN*2 - vidWidth, 0), vidWidth) / float(vidWidth));
    // param 1 is the number of vertical tiles
    ffHost.setPluginFloatParameter(2, 1, MIN(MAX(y - MARGIN, 0), vidHeight) / float(vidHeight));
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mouseReleased() {}
