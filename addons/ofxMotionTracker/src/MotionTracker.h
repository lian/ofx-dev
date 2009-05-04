/***********************************************************************
 -----------------------------------
 
 Copyright (c) 2008, Memo Akten, www.memo.tv
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

#pragma once


#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxCvOpticalFlowBM.h"
#include "ofxTI_Utils.h"

#define DEFAULT_CAM_THRESHOLD 30
#define DEFAULT_CAM_SIL_ALPHA 1.0f
#define DEFAULT_CAM_VELOCITY_BLUR 15

class MotionTracker {

protected:
	
	ofVideoGrabber			vidGrabber;
	ofxCvColorImage			colorImg;					// the color frame of now
	ofxCvGrayscaleImage 	greyNow;					// greyscale version of now
	ofxCvGrayscaleImage 	greyBgDiff;					// difference between background plate and now (matted)
	ofxCvGrayscaleImage 	greyPrev;					// previous frame
	ofxCvGrayscaleImage 	greyBg;						// background plate
	ofxCvGrayscaleImage 	greyCurDiff;				// difference between last 2 frames
	
	ofxCvOpticalFlowLK		opticalFlow;
	
	bool					bLearnBG, mirrorVideo;
	int						camWidth, camHeight;		// pixel size of camera
	int						optFlowWidth, optFlowHeight; // pixel size of optical flow image (huge performance gains the smaller it is)
	int						posX, posY;					// pixel position of this camera in the global composition
	int						camThreshold;
	float					camSilAlpha, camVelocityBlur;
	
public:
	bool					bHasNewFrame;
	int						index;
	int						frameCounter;				// keep track of frames running
	
	MotionTracker();
	~MotionTracker();
	
	void init(int w, int h, int i);
	void update();
	void reset();
	void setPosition(int i);
	void setMirrorVideo(bool mirrorVideo);
	void setCamThreshold(int camThreshold);
	void setCamSilAlpha(float camSilAlpha);
	void setCamVelocityBlur(float camVelocityBlur);
	void setOpticalFlowSteps(int _cols, int _rows);
	void setOpticalFlowResolution(int w, int h);
	
	void drawColor(int x, int y, int w, int h);
	void drawGrey(int x, int y, int w, int h);
	void drawBGDiff(int x, int y, int w, int h);
	void drawCurDiff(int x, int y, int w, int h);
	void drawDebugVideo(int x, int y, int w, int h);
	void drawOpticalFlow(int x, int y, int w, int h);
	void drawOpticalFlowAverage(int x, int y, int w, int h, ofRectangle* averageBounds=NULL);
	
	void keyPressed  (int key);
	
	void getVelAtPixel(int x, int y, float *u, float *v);			// takes coordinates in pixels 
	void getVelAtNorm(float x, float y, float *u, float *v);		// takes coordinates in normalized
	void getVelAverageComponents(float *u, float *v, ofRectangle* bounds=NULL);
	void getVelAverageAngleMag(float *angle, float *magnitude, ofRectangle* bounds=NULL);
	bool hasNewFrame() { return bHasNewFrame; }
};
