//
// ofxCvOpticalFlowBM.h - a OpenCV cvCalcOpticalFlowBM warpper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
// Copyright (C) 2008 Satoru Higa
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of 
// the GNU Lesser General Public License.
//

#pragma once

#include "ofMain.h"
#include "ofxCvConstants.h"
#include "ofxCvGrayscaleImage.h"

#define DEFAULT_CAPTURE_WIDTH 320
#define DEFAULT_CAPTURE_HEIGHT 240

#define DEFAULT_CAPTURE_COLS_STEP 4
#define DEFAULT_CAPTURE_ROWS_STEP 4

class ofxCvOpticalFlowBM
{
public:
	ofxCvOpticalFlowBM(void);
	~ofxCvOpticalFlowBM(void);
		
	void allocate(int _w, int _h);

	void calc( ofxCvGrayscaleImage & pastImage,
			   ofxCvGrayscaleImage & currentImage,					   
			   int size
			  );

	void setCalcStep(int _cols, int _rows);
		
	void reset();
	void draw();

private:
	int captureWidth;
	int captureHeight;

	int captureColsStep;
	int captureRowsStep;

    int block_size;
    int shift_size;

	int rows,cols;
	int cw, ch;

	CvSize block;
	CvSize shift;
	CvSize max_range;

	CvMat *vel_x, *vel_y;

};
