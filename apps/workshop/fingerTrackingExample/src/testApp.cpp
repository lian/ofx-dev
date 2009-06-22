#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	
	ofBackground(255,255,255);

	vid_w = ofGetWidth();
	vid_h = ofGetHeight();
	
	numBlobs =0;
	
	
	//setup our camera
	camera.setVerbose(true);
	//camera.setDeviceID(2);
	camera.initGrabber(vid_w, vid_h);
	
	//check that we got the height we want
	vid_w = camera.width;
	vid_h = camera.height;
	
	
	//allocate our openCV images
	cvColor.allocate(vid_w, vid_h);
	cvGray.allocate(vid_w, vid_h);
	cvBackground.allocate(vid_w, vid_h);
	cvThresh.allocate(vid_w, vid_h);
	
	threshold=0;
	
	ffound=false;
	hfound=false;
	
	diffMode=2;
}

//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	bool bNewFrame = false;
	camera.grabFrame();
	bNewFrame = camera.isFrameNew();
	
	if (bNewFrame)
	{
	
		cvColor.setFromPixels( camera.getPixels(), vid_w, vid_h);
	
		cvGray = cvColor;
		cvThresh = cvBackground;
		cvThresh -= cvGray;
		
		if(diffMode == 0){
			cvThresh = cvGray;
			cvThresh.absDiff(cvBackground);
		}else if(diffMode == 1){
			cvThresh = cvGray;
			cvThresh -= cvBackground;
		}else if(diffMode == 2){
			cvThresh = cvBackground;
			cvThresh -= cvGray;
		}
		
		cvThresh.threshold(threshold);
		numBlobs = contour.findContours(cvThresh, 100, 9999999, 40,true,false);
		
			if(numBlobs > 0)
			{
				ffound=false;
				hfound=false;
				
				ffound=fingerFinder.findFingers(contour.blobs[0]);
				hfound=fingerFinder.findHands(contour.blobs[0]);
			}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(0xffffff);
	camera.draw(0,0);
	contour.draw();
	
	ofSetColor(0,0,0);
	string threshStr = "threshold cv image - thresh is ";
	threshStr += ofToString(threshold);
	threshStr +=  "\nthresh mode is: ";
	if(diffMode == 0)threshStr += "abs diff";
	if(diffMode == 1)threshStr += "lighter than";
	if(diffMode == 2)threshStr += "darker than";
	ofDrawBitmapString(threshStr,10,10);
	
	
	if(ffound) fingerFinder.draw(0,0);
	if(hfound)fingerFinder.drawhands(0,0);
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if(key == 'c'){
		camera.videoSettings();
	}
	
	if(key == 'b'){
		cvBackground = cvGray;
	}
	if(key =='1'){
		diffMode = 0;
	}else if(key =='2'){
		diffMode = 1;
	}else if(key == '3'){
		diffMode = 2;
	}
	
	if(key == '+'){
		threshold += 2;
	}else if(key == '-'){
		threshold -= 2;
		if(threshold < 0)threshold = 0;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

