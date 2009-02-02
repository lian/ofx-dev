#include "NSvidbutton.h"

NSvidbutton::NSvidbutton(){

  count = 0;
//	nFramesWhite = 0; 
	bShowImage = false;
};


void NSvidbutton::loadSound(string soundName){
	mySound.loadSound(soundName);
	mySound.setMultiPlay(false);
}

void NSvidbutton::loadImage(string imagename){
	myimage.loadImage(imagename);
   w =  myimage.width;
   h = myimage.height;
}

void NSvidbutton::setPosition(int _theNum, int _x, int _y, int _width, int _height){
	theNum = _theNum;
	x = _x;
	y = _y;
	w = _width;
	h = _height;
	toggle = false;
}
		

void NSvidbutton::update(){
	
	
	if (mySound.getIsPlaying() == false) {
		if (bShowImage == true){
			bShowImage = false;
		}
	}
	
	if (nPixelsWhite > (w*h/10)){
	
		if (toggle == false) {
			toggle = true;
			 mySound.play();
			 bShowImage = true;
		
		  		}
	} else {
		toggle = false;
	}
}


void NSvidbutton::draw(){

	if (bShowImage) {
	  myimage.draw(x,y);
	}
	
/*	if (nPixelsWhite > (w*h/4)){
		ofSetColor(255,0,0);
	} else {
		ofSetColor(255,255,255);
	}
	ofRect(x,y,w,h);
	ofSetColor(255,255,255); */
}

void NSvidbutton::countPixelsInImage(ofxCvGrayscaleImage & temp){
	nPixelsWhite = temp.countNonZeroInRegion(x, y, w, h);
}





