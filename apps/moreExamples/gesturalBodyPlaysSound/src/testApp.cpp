#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){
	 
	ofBackground(0,0,0);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);		// windows direct show users be careful
											// some devices (dvcams, for example) don't 
											// allow you to capture at this resolution. 
											// you will need to check, and if necessary, change 
											// some of these values from 320x240 to whatever your camera supports
											// most webcams, firewire cams and analog capture devices will support this resolution.
	
    	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	bLearnBakground = true;
	threshold = 23;
	
	
	xPos = 160;
	yPos = 120;
	width = 160;
	height = 120;
	
	NButtons = 5;
	
	//random seed
	srand ( time(NULL) );
	
	for(int i=0; i<NButtons ; i++){
		buttons[i].setPosition( i, i * 50, 50, 40,40); //button number, x, y, width, height
		string fileName = "sound" + ofToString(i) + ".wav";
			buttons[i].loadSound(fileName);
		fileName = "images" + ofToString(i+1) + ".jpeg"; 
			buttons[i].loadImage(fileName);
		}
	
}

//--------------------------------------------------------------
void testApp::update(){

	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		grayImage = (colorImg);
		
		//flip image horizontal
		grayImage.mirror(0,1);
		
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 20, false);	// number of blobs, holes or not

    	ofSetColor(0xffffff);
		
		for(int i=0; i<NButtons ; i++){
		buttons[i].countPixelsInImage(grayDiff);
		}
		
		for(int i=0; i<NButtons ; i++){
		buttons[i].update();
		}
		// count numbe rof white pixels within a specific region
		// put to screen, threshold and change bg
		nPixelsWhite = grayDiff.countNonZeroInRegion(xPos, yPos, width, height);
		//printf("%i \n", nPixelsWhite);
//		if (nPixelsWhite > 4000) ofBackground(255,0,0);
//		else ofBackground(255,255,255);        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	
	bool bShowFullScreen = true;
	if (bShowFullScreen){
		glScalef(1024.0 / 320.0f, 768.0f / 240.0f, 1);
	    grayDiff.draw(0,0);
		for(int i=0; i<NButtons ; i++){
			buttons[i].draw();
		}
		
	} else {
	grayImage.draw(320,0);
	grayDiff.draw(0,0);
	grayBg.draw(0,240);
	
		for(int i=0; i<NButtons ; i++){
		buttons[i].draw();
		}
	}
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
     	switch (key){
		case 's':
			vidGrabber.videoSettings();
			break;
		case ' ':
			bLearnBakground = true;
			break;
		case 'a':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case 'z':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
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
void testApp::mouseReleased(){

}
