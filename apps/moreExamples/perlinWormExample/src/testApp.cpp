#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(250,250,250);
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetupScreen();
	
	glEnable(GL_DEPTH_TEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		
	center.x = ofGetWidth()/2;
	center.y = ofGetHeight()/2;
	center.z = 0;
	
	ofxSetSmoothLight(false);
	
	noise = new Perlin(4, 4, 1, time(NULL));
	
	for(int i=0; i<NUMW; i++){
		worms[i] = new Worm(center, noise);
	}
	num = 0;
	bShowMouse = true;
	
	camLight.specular(200, 250 , 200);
	camLight.ambient(0, 200, 0);
	upLight.directionalLight(100, 250, 100, 0, 1, 0);

	ofxMaterialSpecular(250, 250, 250);
	ofxMaterialShininess(20);
	
	bPause = false;
	
	camera.position(center.x, center.y, 2000);
	
	#ifdef GRAB_FRAME_SEQUENCE
	float totalFrames = 2700;
	frameGrabber = new FrameGrabber("worms", totalFrames, true);
	#endif
	
	ofxLightsOff();
}

//--------------------------------------------------------------
void testApp::update(){
	if(!bPause){
		ofxVec3f midPoint;
		midPoint.set(0, 0, 0);
		for(int i=0; i<NUMW; i++){
			worms[i]->move();
			midPoint += worms[i]->disk[0].center;
		}
		midPoint /= NUMW;
		
		for(int i=0; i<NUMW; i++){
			worms[i]->dontGoTooFar(midPoint);
		}
		
		camLight.pointLight(100, 250, 100, midPoint.x, midPoint.y, midPoint.z + 400);
		
		camera.lerpPosition(midPoint.x, midPoint.y, midPoint.z + 200, 0.1);
		camera.eye(midPoint.x, midPoint.y, midPoint.z);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofxSetSmoothLight(true);
	background.render();
	camera.place();
	ofxSetSmoothLight(false);
	ofxLightsOn();
	for(int i=0; i<NUMW; i++){
		worms[i]->render();
		//	worms[i]->renderNormals(); //for reference only
	}
	ofxLightsOff();
	for(int i=0; i<NUMW; i++){
		// worms[i]->renderContours();
		
	}
	
#ifdef GRAB_FRAME_SEQUENCE
	frameGrabber->grabFrame();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	if(key == ' ')std::cout << ofGetFrameRate() << std::endl;
	if(key == 'f' or key == 'F'){
		ofToggleFullscreen();
		bShowMouse = !bShowMouse;
		if(bShowMouse){
			ofShowCursor();
		} else {
		ofHideCursor();
		}
	}
	
	if(key == 'p' or key == 'P') bPause = !bPause;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	mouseX = x;
	mouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	

}
