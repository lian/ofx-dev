/*
 *  NSvidbutton.h
 *  openFrameworks
 *
 *  Created by Nathaniel Stern on 02/03/2008.
 *
 */


#ifndef _NSVIDBUTTON
#define _NSVIDBUTTON

#include "ofMain.h"
#include "ofxCvMain.h"

class NSvidbutton {
//	private:
	
	public:	
	
		// vars
		int x, y, w, h;
		int theNum;
		int nPixelsWhite;
		bool toggle;
		ofImage myimage;
		
		bool bShowImage;
		// methods
		void update();
		
		void setPosition(int _theNum, int _x, int _y, int _width, int _height);
		void loadSound(string str);
		
		void loadImage(string str);
		
		void countPixelsInImage(ofxCvGrayscaleImage & temp);  // ofCv.. = data type, & = reference for pass by refence, temp =temporary variable name
		
		void draw();
		
		ofSoundPlayer mySound;
		int nFramesWhite;
		int count; 		  
	// constructor
	NSvidbutton();
};
#endif
