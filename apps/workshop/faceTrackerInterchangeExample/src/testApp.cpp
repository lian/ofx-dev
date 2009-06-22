#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	
	
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	bLearnBakground = true;
	threshold = 80;
	
    jesus.loadImage("0.png");
	
	//  load in our face
	haarfinder.setup("haarcascade_frontalface_default.xml");
	
	// 0 output channels, 
	// 2 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	/*
	ofSoundStreamSetup(0,2,this, 22050,256, 4);	
	left = new float[256];
	right = new float[256];	
	*/
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
    
    bool bNewFrame = false;
	
	#ifdef _USE_LIVE_VIDEO
       vidGrabber.grabFrame();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.idleMovie();
        bNewFrame = vidPlayer.isFrameNew();
	#endif
	
	if (bNewFrame){
		
		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		haarfinder.findHaarObjects(grayImage, 10, 999999, 10);
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
        
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
	}
}


//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	colorImg.draw(20,20);
	
	// draw bounding box
	// haarfinder.draw(20,20);
	
	int numFaces = haarfinder.blobs.size();
	// ofDrawBitmapString("dude there are : "+ofToString(numFaces)+" faces", 20, 20);

    glPushMatrix();
    glTranslatef(20, 20, 0);
    
	for(int i =0; i < numFaces; i++)
    {
        float x = haarfinder.blobs[i].boundingRect.x;
        float y = haarfinder.blobs[i].boundingRect.y;
        float w = haarfinder.blobs[i].boundingRect.width;
        float h = haarfinder.blobs[i].boundingRect.height;
        
        ofEnableAlphaBlending();
    	ofSetColor(0xffffff);
    	
    	// resample for 1*1 ratio image
    	w = h * 1.5;
    	
        jesus.draw(x-h*0.25, y, w, w);
        ofDisableAlphaBlending();
            
    }
    
    glPopMatrix();
	
}




//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 's':
			vidGrabber.videoSettings();
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
