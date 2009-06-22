#include "videoHandDetector.h"


//--------------------------------------------------------------
void videoHandDetector::setup(int w, int h){
	width 		= w;
	height 		= h;
	videoImageGray.allocate(width, height);
	handDetectionImage.allocate(width, height);
	nHands		= 0;
}

//--------------------------------------------------------------
void videoHandDetector::update(ofxCvColorImage video){
	
	videoImageGray.setFromColorImage(video);
	videoImageGray.threshold(20);
	videoImageGray.erode_3x3();
	contourFinder.findContours(videoImageGray, 4000,320*240, 5, false);
	handDetectionImage.set(0);
	
	nHands = contourFinder.nBlobs;
	for (int i = 0; i < contourFinder.nBlobs; i++){
	//	handDetectionImage.draw(contourFinder.blobs[i], 255);
		hands[i].myBlob = contourFinder.blobs[i];
		fingerFinder.findFingers(hands[i]);
	}
	
	
	//---------------------------------------------
	for (int i = 0; i < MAX_N_TRACKED_FINGERS; i++){
   		fingers[i].energy *= 0.905f;
   		fingers[i].bFoundMeThisFrame = false;
   	}
   
   
   	for (int i = 0; i < nHands; i++){
		int nFingers = hands[i].nFingers;
		for (int j = 0; j < nFingers; j++){
	   		
	   			
	   		bool bFound = false;	
	   		int  smallestIndex = -1;
	   		float smallestDist = 10000;
		    
		    for (int k = 0; k < MAX_N_TRACKED_FINGERS; k++){
		    	
		    	if (fingers[k].energy < 0.01 || fingers[k].bFoundMeThisFrame) continue;	// skip non energized persistant faces. 
		    	
		    	
		    	float dx = fingers[k].pos.x - hands[i].fingerPos[j].x;
		    	float dy = fingers[k].pos.y - hands[i].fingerPos[j].y;
		    	float len = sqrt((dx*dx) + (dy*dy));
		   		
		   		if (len < smallestDist){
		   			smallestDist 		= len;
		   			smallestIndex		= k;
		   		} 
		   	}
		   	
		   	
		   
		   	if (smallestDist < 80){
		   		fingers[smallestIndex].energy += 0.2f;
		   		fingers[smallestIndex].energy = MIN(fingers[smallestIndex].energy, 1);
		   		fingers[smallestIndex].bFoundMeThisFrame = true;
		   		fingers[smallestIndex].pos.x = hands[i].fingerPos[j].x;
		    	fingers[smallestIndex].pos.y = hands[i].fingerPos[j].y;
		   		fingers[smallestIndex].birthday = ofGetElapsedTimef();
		   		bFound = true;
		   	}
		   	
		   	if (!bFound){
		   		
		   		int  smallestIndex = -1;
	   			float smallestEnergy = 100000000	;
		   		// ok find the earliest, of first non energized persistant face:
		   		for (int k = 0; k < MAX_N_TRACKED_FINGERS; k++){
		    		if (fingers[k].bFoundMeThisFrame) continue;
		    		if (fingers[k].birthday < smallestEnergy){
		    			smallestEnergy 	= fingers[k].birthday;
		    			smallestIndex 	= k;
		    		}
		    	}
		    	
		    	if (smallestIndex != -1){
		    		fingers[smallestIndex].pos.x = hands[i].fingerPos[j].x;
		    		fingers[smallestIndex].pos.y = hands[i].fingerPos[j].y;
		   			fingers[smallestIndex].energy = 0.2f;
		   			fingers[smallestIndex].bFoundMeThisFrame = true;
		   			fingers[smallestIndex].birthday = ofGetElapsedTimef();
		    	}
		   	}
		   	
	   	
	   	}
   	}
   	
   	
   	for (int i = 0; i < MAX_N_TRACKED_FINGERS; i++){
   		if (fingers[i].bFoundMeThisFrame == false){
   			fingers[i].energy = 0;
   		}
   	}
	
	
	
	
	
	
	
	
}

//--------------------------------------------------------------
void videoHandDetector::draw(float x, float y){

	handDetectionImage.draw(x,y);
	
	//return;
	
	/*for (int i = 0; i < nHands; i++){
		int nFingers = hands[i].nFingers;
		for (int j = 0; j < nFingers; j++){
			ofCircle(hands[i].fingerPos[j].x*3, hands[i].fingerPos[j].y*3, 4);
		}
	} 
	
	
	for (int i = 0; i < MAX_N_TRACKED_FINGERS; i++){
   		if (fingers[i].energy > 0.11f){
   			
   			ofEnableAlphaBlending();
   			ofSetColor(255,255,255,fingers[i].energy * 255);
   			ofCircle(fingers[i].pos.x,fingers[i].pos.y, 4);
   			ofDisableAlphaBlending();
   			char temp[255];
   			sprintf(temp, "id: %i \n", i);
   			ofDrawBitmapString(temp,fingers[i].pos.x*3,fingers[i].pos.y*3);
   		}
   	}*/
}
		