#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);

	//video.loadMovie("multiPerson-FromBehind-IR.mov");
	//video.play();

	camWidth = 320;
	camHeight = 240;
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	useCam = true;
	
	//allocate the openCV images
	// cvColor.allocate(video.width, video.height);
	// cvGray.allocate(video.width, video.height);
	// cvBackground.allocate(video.width, video.height);
	// cvThresh.allocate(video.width, video.height);
	
	cvColor.allocate(camWidth, camHeight);
	cvGray.allocate(camWidth, camHeight);
	cvBackground.allocate(camWidth, camHeight);
	cvThresh.allocate(camWidth, camHeight);
	
	
	//-----
	backSubMode = 2;
	threshold   = 30;
	
	//how far a blob has to move between frames before it is treated as a new blob
	//you usually have to adjust this based on the size of the video and the people within it.
	//basically this is 'how far do you think someone would normally move between frames measured in pixels'
	distanceThresh = 80;
	
	//we say that we are interested in previous blobs that are younger than 500ms
	//this means that if we don't see a stored blob for more than half a second we forget about it.
	//this is essentially the memory in milliseconds of your tracker
	tracker.setup(800);

}

//--------------------------------------------------------------
void testApp::update(){
	if (useCam == true) {
		
		vidGrabber.grabFrame();
		if (vidGrabber.isFrameNew()){
			unsigned char * pixels = vidGrabber.getPixels();
			cvColor.setFromPixels(pixels, camWidth, camHeight);
		}
		
	} else {
		
		video.idleMovie();
		if(video.isFrameNew()){
			unsigned char * pixels = video.getPixels();
			cvColor.setFromPixels(pixels, video.width, video.height);
		}
		
	}
	
	// video.idleMovie();	
	// unsigned char * pixels = video.getPixels();
	// cvColor.setFromPixels(pixels, video.width, video.height);
	
	//converting from color to grayscale is as simple as 
	//setting the gray cv image = to the color cv image
	cvGray = cvColor;
	
	//lets treat the first few frames of the video as our background
	if(ofGetFrameNum() < 20)	cvBackground = cvGray;

	//we do background subtraction - between the current frame and our background
	//we can do absolute difference / lighter than / and darker than
	//typical is absolute diff
	if(backSubMode == 0){
		cvThresh = cvGray;
		cvThresh.absDiff(cvBackground);
	}else if(backSubMode == 1){
		cvThresh = cvGray;
		cvThresh -= cvBackground;
	}else if(backSubMode == 2){
		cvThresh = cvBackground;
		cvThresh -= cvGray;
	}
	
	cvThresh.threshold(threshold);
	
	//lets find blobs and their contours
	int numFound = contourFinder.findContours(cvThresh, 10 * 10, 200 * 200, 100, false, false);
	
	//TRACKER  
	
	//we do this whether or not we have found any blobs because the tracker also kills its stored blobs
	//if they haven't been matched for a while.
	tracker.begin();
	
	if( numFound > 0){
		//allocate our array (vector) with enough space for the number of blobs we have found
		trackedBlobs.assign(numFound, trackedBlob());
		
		//loop through each blob found
		for(int i = 0; i < numFound; i++){
			
			//copy each blob over to our array
			trackedBlobs[i] = contourFinder.blobs[i];
			
			//see if the blob is one known from previous frames
			bool blobMatched = tracker.matchTrackedBlob( trackedBlobs[i], distanceThresh );
			
			//if the blob can't be matched against the stored blobs
			//add it to the stored blobs
			if( blobMatched == false ){
				tracker.addBlob(trackedBlobs[i]);
			}
		}
	}
	
	//this is where stored blobs that need to die, get killed :)
	tracker.end();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	cvColor.draw(0, 0);
	//cvGray.draw(video.width, 0);
	//cvBackground.draw(2 * video.width, 0);
	//cvThresh.draw(0, video.height);
	//contourFinder.draw(0, video.height);
	cvGray.draw(camWidth, 0);
	cvBackground.draw(2 * camWidth, 0);
	cvThresh.draw(0, camHeight);
	contourFinder.draw(0, camHeight);

	
	//lets draw the tracked blobs ids!
	
	//using our vector (c++ array) is cool because it knows how big it is. 
	//the size() function returns the number of things its storing.
		
	for(int i = 0; i < trackedBlobs.size(); i++){
		if( trackedBlobs[i].bNew ){
			ofSetColor(0xFFFF00);
		}else{
			ofSetColor(0x0000FF);
		}
		ofFill();
		ofCircle(trackedBlobs[i].centroid.x, trackedBlobs[i].centroid.y, 4);
		
		ofSetColor(0x00FFFF);
		ofDrawBitmapString("id: "+ofToString(trackedBlobs[i].id), trackedBlobs[i].boundingRect.x, trackedBlobs[i].boundingRect.y);		
	}
	
	
	ofSetColor(0x000000);
	ofFill();
	//ofRect(video.width, video.height, video.width, video.height);
	//contourFinder.draw(video.width, video.height);
	ofRect(video.width, camHeight, camWidth, camHeight);
	contourFinder.draw(camWidth, camHeight);
	
	ofSetColor(50, 50, 255);
	ofDrawBitmapString("the color video as an openCV image", 10, 15);
	//ofDrawBitmapString("now converted to grayscale\n", 10 + video.width, 15);
	//ofDrawBitmapString("this is our background", 10 + video.width*2, 15);
	ofDrawBitmapString("now converted to grayscale\n", 10 + camWidth, 15);
	ofDrawBitmapString("this is our background", 10 + camWidth*2, 15);
	
	string backSubModeStr = "\nbackSub is: ";
	if(backSubMode == 0)backSubModeStr += "absolute diff";
	if(backSubMode == 1)backSubModeStr += "lighter than";
	if(backSubMode == 2)backSubModeStr += "darker than";
	
	//ofDrawBitmapString("threshold is: "+ofToString(threshold) + backSubModeStr, 8, video.height+16);
	ofDrawBitmapString( ofToString(ofGetFrameRate()) + "threshold is: "+ofToString(threshold) + backSubModeStr, 8, camHeight+16);
	ofDrawBitmapString("keys 1 / 2 / 3 - change backSubtraction mode   'g' key to grab background  'r' reset tracker   UP/DN keys - adjust threshold", 10, ofGetHeight()-15);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key == '1'){
		backSubMode = 0;
	}else if(key == '2'){
		backSubMode = 1;
	}else if(key == '3'){
		backSubMode = 2;
	}
	
	if(key == 'g'){
		cvBackground = cvGray;
	}
	
	//reset the tracker and id count
	if(key == 'r'){
		tracker.resetCounter();
	}
	
	if( key == OF_KEY_UP ){
		threshold++;
		if(threshold > 255)threshold = 255;
	}else if(key == OF_KEY_DOWN){
		threshold--;
		if(threshold < 0)threshold = 0;
	}
	
	// switch cam/video
	if(key == 'c'){
		if (useCam == true) {
			useCam = false;
			video.play();
		} else {
			useCam = true;
			video.stop();
		}
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
void testApp::mouseReleased(){

}
