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



#include "MotionTracker.h"
#include "App.h"


MotionTracker::MotionTracker() {
}



MotionTracker::~MotionTracker() {
}


void MotionTracker::init(int w, int h, int i) {
	camWidth = w;
	camHeight = h;
	index = i;
	
	posX = index * CAM_DISPLAY_WIDTH;
	posY = 0;
	
	vidGrabber.initGrabber(camWidth, camHeight);	
	vidGrabber.listDevices();
	vidGrabber.setDeviceID(i);
	vidGrabber.setUseTexture(false);
	
	opticalFlow.allocate(camWidth, camHeight);
	
	colorImg.allocate(camWidth, camHeight);
	greyNow.allocate(camWidth, camHeight);
	greyBgDiff.allocate(camWidth, camHeight);
	greyPrev.allocate(camWidth, camHeight);
	greyCurDiff.allocate(camWidth, camHeight);
	greyBg.allocate(camWidth, camHeight);
	
	bLearnBG = true;
	bHasNewFrame = false;
	
	reset();
}


void MotionTracker::setPosition(int i) {
	index = i;
	posX = index * CAM_DISPLAY_WIDTH;
}

void MotionTracker::reset() {
	colorImg.set(0);
	greyNow.set(0);
	greyBgDiff.set(0);
	greyPrev.set(0);
	greyCurDiff.set(0);
    cvSetZero(opticalFlow.vel_x);
    cvSetZero(opticalFlow.vel_y);
	
	frameCounter = 0;
}


void MotionTracker::getVelAtPixel(int x, int y, float *u, float *v) {
	*u = cvGetReal2D( opticalFlow.vel_x, y, x );
	*v = cvGetReal2D( opticalFlow.vel_y, y, x );
}

void MotionTracker::getVelAtNorm(float x, float y, float *u, float *v) {
	int ix = x * camWidth;
	int iy = y * camHeight;
	if(ix<0) ix = 0; else if(ix>=camWidth) ix = camWidth - 1;
	if(iy<0) iy = 0; else if(iy>=camHeight) iy = camHeight - 1;
	*u = cvGetReal2D( opticalFlow.vel_x, iy, ix );
	*v = cvGetReal2D( opticalFlow.vel_y, iy, ix );
}

/*
 bool MotionTracker::capture() {
 bool ret;
 if(lock()) {
 vidGrabber.grabFrame();
 if(ret = bHasNewFrame = vidGrabber.isFrameNew()) {
 colorImg.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
 colorImg.mirror(false, true);					// mirror it
 }
 unlock();
 } 
 
 return true;
 }
 */

//--------------------------------------------------------------
void MotionTracker::update(){
	//	printf("starting MotionTracker %i update \n", index);
	vidGrabber.grabFrame();
	
	if (bHasNewFrame = vidGrabber.isFrameNew()){

		colorImg.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
		if(App::mirrorVideo) colorImg.mirror(false, true);					// mirror it

		greyNow.setFromColorImage(colorImg);			// make color image grey
		
		if (bLearnBG == true) {							// save background if nessecary
			greyBg = greyNow;
			bLearnBG = false;
		}
		
		greyBgDiff.absDiff(greyBg, greyNow);			// subtract background from it
		
//		greyBgDiff.thresholdMSA(App::camThreshold, CV_THRESH_TOZERO);		// chop dark areas		THIS DOES NOT WORK HERE! MESSY EDGES FOR OPTICAL FLOW

		if(frameCounter > 5) {		// dont do anything until we have enough in history
			opticalFlow.calc(greyPrev, greyBgDiff, 11);
			cvSmooth(opticalFlow.vel_x, opticalFlow.vel_x, CV_BLUR , CAM_VELOCITY_BLUR);
			cvSmooth(opticalFlow.vel_y, opticalFlow.vel_y, CV_BLUR , CAM_VELOCITY_BLUR);
			
			greyCurDiff.absDiff(greyPrev, greyBgDiff);			// curDiff is the difference between the last 2 frames
			greyCurDiff.thresholdMSA(App::camThreshold, CV_THRESH_TOZERO);		// chop dark areas
			greyCurDiff.blur(3);
		} else {
			frameCounter ++;
		}
		
		greyPrev = greyBgDiff;							// save frame for next frame
		
//		greyNow.thresholdMSA(App::camThreshold, CV_THRESH_TOZERO);		// chop dark areas		GOOD FOR RENDERING
//		cvCanny(greyPrev.getCvImage(), greyNow.getCvImage(), 50, 100, 3);
//		greyNow.blur(5);

//		greyBgDiff.thresholdMSA(App::camThreshold);		// chop dark areas
		greyBgDiff.thresholdMSA(App::camThreshold, CV_THRESH_TOZERO);		// chop dark areas
		greyBgDiff.blur(3);

	} 	
	//	printf("ending MotionTracker %i update \n", index);
}


#define VIDEO_DRAW_WIDTH		320
#define VIDEO_DRAW_HEIGHT		(VIDEO_DRAW_WIDTH * 0.75f)
//--------------------------------------------------------------
void MotionTracker::drawDebugVideo(){
//		printf("drawing MOTION TRACKER %i \n", index);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	int drawY = HEIGHT + VIDEO_DRAW_WIDTH * index;
	int drawX = -VIDEO_DRAW_WIDTH;
	
	greyBg.draw(drawX += VIDEO_DRAW_WIDTH, drawY, VIDEO_DRAW_WIDTH, VIDEO_DRAW_HEIGHT);
//	colorImg.draw(drawX += VIDEO_DRAW_WIDTH, drawY, VIDEO_DRAW_WIDTH, VIDEO_DRAW_HEIGHT);	
//	greyNow.draw(drawX += VIDEO_DRAW_WIDTH, drawY, VIDEO_DRAW_WIDTH, VIDEO_DRAW_HEIGHT);
	greyBgDiff.draw(drawX += VIDEO_DRAW_WIDTH, drawY, VIDEO_DRAW_WIDTH, VIDEO_DRAW_HEIGHT);	
	greyCurDiff.draw(drawX += VIDEO_DRAW_WIDTH, drawY, VIDEO_DRAW_WIDTH, VIDEO_DRAW_HEIGHT);
	
	glPushMatrix();
	glTranslatef(drawX += VIDEO_DRAW_WIDTH, drawY, 0);
	glScalef(VIDEO_DRAW_WIDTH / camWidth, VIDEO_DRAW_HEIGHT / camHeight, 1.0f);
	opticalFlow.draw();
	glPopMatrix();
	
}

void MotionTracker::drawColor() {
	glColor3f(App::camSilAlpha, App::camSilAlpha, App::camSilAlpha);
	colorImg.draw(posX, posY, CAM_DISPLAY_WIDTH, HEIGHT);
}

void MotionTracker::drawGrey() {
	glColor3f(App::camSilAlpha, App::camSilAlpha, App::camSilAlpha);
	greyNow.draw(posX, posY, CAM_DISPLAY_WIDTH, HEIGHT);
}


void MotionTracker::drawBGDiff() {
	glColor3f(App::camSilAlpha, App::camSilAlpha, App::camSilAlpha);
	greyBgDiff.draw(posX, posY, CAM_DISPLAY_WIDTH, HEIGHT);
}

void MotionTracker::drawCurDiff() {
	glColor3f(1.0f, 1.0f, 1.0f);
	greyCurDiff.draw(posX, posY, CAM_DISPLAY_WIDTH, HEIGHT);
}



//--------------------------------------------------------------
void MotionTracker::keyPressed  (int key){ 
	switch (key){
		case 't':if(ofGetWindowMode() == OF_WINDOW) vidGrabber.videoSettings();
			break;
		case 's':
			bLearnBG = true;
			break;
	}
}
