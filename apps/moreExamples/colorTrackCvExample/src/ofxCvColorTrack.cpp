/*
 *  ofxCvColorTrack.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 3/12/08.
 *  http://www.candersonmiller.com/
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxCvColorTrack.h"
#include <stack>

ofxCvColorTrack::ofxCvColorTrack()
{
	nBlobs = 0;
	threshold = 55;
	tolerance = 40;
	
}

void ofxCvColorTrack::findColor( int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

void ofxCvColorTrack::update(ofxCvColorImage & input)
{

	//taking the fine image source allocation code from findContours code
	if (inputCopy.width == 0){	
		inputCopy.allocate(input.width, input.height);
		inputCopy = input;
	} else {
		if (inputCopy.width == input.width && inputCopy.height == input.height){
			inputCopy = input;
		} else {
			// we are allocated, but to the wrong size -- 
			// been checked for memory leaks, but a warning:
			// be careful if you call this function with alot of different
			// sized "input" images!, it does allocation every time
			// a new size is passed in....
			inputCopy.clear();
			inputCopy.allocate(input.width, input.height);
			inputCopy = input;
		}
	}
	
	//Now let's posterize this picture to reduce the number of potential colors
		unsigned char * pixels = inputCopy.getPixels();
		int totalPixels = inputCopy.width *inputCopy.height * 3; 
		int thisPixel[3];
		
		int targetRGB[3] = {red,green,blue};

		long xTotal = 0;
		long yTotal = 0;
		int j = 0;
		
		for(int i = 0; i < totalPixels; i++){
			pixels[i] = floor(pixels[i] / threshold);
			pixels[i] *= threshold;
			thisPixel[i%3] = pixels[i];
			
			if(i%3 == 2){
				int brightness = (thisPixel[0] + thisPixel[1] + thisPixel[2])/3;
				int totalDiff = abs(targetRGB[0] - thisPixel[0]) + abs(targetRGB[1] - thisPixel[1]) + abs(targetRGB[2] - thisPixel[2]);
				if(totalDiff < tolerance){
					pixels[i] = 255;
					pixels[i-1] = 255;
					pixels[i-2] = 255;
					int tempX = xPosition(i+1, inputCopy.height, inputCopy.width);
					int tempY = yPosition(i+1, inputCopy.height, inputCopy.width);
					
					xTotal += tempX;
					yTotal += tempY;
					j++;
				}
			}
			
		}
		
		if( j < 1){
			j++;
		}

		if(j > 30){
			xAvg = (xTotal/j);
			yAvg = (yTotal/j);
		}
		
	
		float xPos = (xAvg/inputCopy.width);
		float yPos = (yAvg/inputCopy.height);
		
		xAvg = xPos;
		yAvg = yPos;
		
		inputCopy.setFromPixels(pixels,320,240);

	
	
	
}
void ofxCvColorTrack::setTolerance(int t){
	tolerance = t;
}
float ofxCvColorTrack::getX(){
	return xAvg;
}

float ofxCvColorTrack::getY(){
	return yAvg;
}


int ofxCvColorTrack::xPosition(int pixelNum, int h, int w){
	int normalizedPixels = pixelNum/3;
	return normalizedPixels % w;
}

int ofxCvColorTrack::yPosition(int pixelNum, int h, int w){
	int normalizedPixels = pixelNum/3;
	int temp = pixelNum % w;
	return (normalizedPixels - temp)/w;
}
