//
// ofxCvOpticalFlowBM.c - a OpenCV cvCalcOpticalFlowBM warpper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
// Copyright (C) 2008 Satoru Higa
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of 
// the GNU Lesser General Public License.
//

#include "ofxCvOpticalFlowBM.h"

ofxCvOpticalFlowBM::ofxCvOpticalFlowBM(void)
{
	captureWidth = DEFAULT_CAPTURE_WIDTH;
	captureHeight = DEFAULT_CAPTURE_HEIGHT;
}

ofxCvOpticalFlowBM::~ofxCvOpticalFlowBM(void)
{
  // TODO : release cv matrices 
  //cvReleaseImage(&vel_x);
  //cvReleaseImage(&vel_y);
}
	
void ofxCvOpticalFlowBM::allocate(int _w, int _h){
	captureWidth = _w;
	captureHeight = _h;
	
    cw = 320; ch = 240;

    block_size = 10;
    shift_size = 1;
    
    rows = int(ceil(double(ch) / block_size));
    cols = int(ceil(double(cw) / block_size));
    
    vel_x = cvCreateMat (rows, cols, CV_32FC1);
    vel_y = cvCreateMat (rows, cols, CV_32FC1);
    
    cvSetZero(vel_x);
    cvSetZero(vel_y);
    
    block = cvSize (block_size, block_size);
    shift = cvSize (shift_size, shift_size);
    max_range = cvSize (10, 10);

}

void ofxCvOpticalFlowBM::setCalcStep(int _cols, int _rows) {
	captureColsStep = _cols;
	captureRowsStep = _rows;
}

void ofxCvOpticalFlowBM::calc( ofxCvGrayscaleImage & pastImage, ofxCvGrayscaleImage & currentImage, int size) {
	cvCalcOpticalFlowBM(pastImage.getCvImage(), currentImage.getCvImage(), block, shift, max_range, 0, vel_x, vel_y);
}

void ofxCvOpticalFlowBM::draw(void){

	ofSetColor(0xffffff);
	ofNoFill();

	// draw for debug display
	int x, y, dx, dy;
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            int dx = (int) cvGetReal2D (vel_x, y, x);
            int dy = (int) cvGetReal2D (vel_y, y, x);
            int xx = x * block_size;
            int yy = y * block_size;
            ofLine(xx, yy, xx + dx, yy + dy);
        }
    }
}
