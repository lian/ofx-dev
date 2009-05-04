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


MotionTracker::MotionTracker() {
}

MotionTracker::~MotionTracker() {
}


void MotionTracker::init(int w, int h, int i) {
	camWidth = w;
	camHeight = h;
	optFlowWidth = w;
	optFlowHeight = h;
	index = i;
	posX = index * camWidth;
	posY = 0;
	
	mirrorVideo = false;
	camThreshold = DEFAULT_CAM_THRESHOLD;
	camSilAlpha = DEFAULT_CAM_SIL_ALPHA;
	camVelocityBlur = DEFAULT_CAM_VELOCITY_BLUR;

	vidGrabber.setDeviceID(i); // must set camera ID and other options before calling initGrabber
	vidGrabber.initGrabber(camWidth, camHeight, false); // no texture
	
	opticalFlow.allocate(optFlowWidth, optFlowHeight);
	
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
	posX = index * camWidth;
}

void MotionTracker::setMirrorVideo(bool mirrorVideo){
	this->mirrorVideo = mirrorVideo;
}

void MotionTracker::setCamThreshold(int camThreshold){
	this->camThreshold = camThreshold;
}

void MotionTracker::setCamSilAlpha(float camSilAlpha){
	this->camSilAlpha = camSilAlpha;
}

void MotionTracker::setCamVelocityBlur(float camVelocityBlur){
	this->camVelocityBlur = camVelocityBlur;
}

void MotionTracker::setOpticalFlowSteps(int _cols, int _rows){
	this->opticalFlow.setCalcStep(_cols, _rows);
}

void MotionTracker::setOpticalFlowResolution(int w, int h){
	this->optFlowWidth = w;
	this->optFlowHeight = h;
	this->opticalFlow.allocate(this->optFlowWidth, this->optFlowHeight);
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
	x = (float)x/(float)camWidth*(float)optFlowWidth; // normalize co-ords from camera size to optical flow size
	y = (float)y/(float)camHeight*(float)optFlowHeight;
	*u = cvGetReal2D( opticalFlow.vel_x, y, x );
	*v = cvGetReal2D( opticalFlow.vel_y, y, x );
}

void MotionTracker::getVelAtNorm(float x, float y, float *u, float *v) {
	int ix = x * optFlowWidth;
	int iy = y * optFlowHeight;
	if(ix<0) ix = 0; else if(ix>=optFlowWidth) ix = optFlowWidth - 1;
	if(iy<0) iy = 0; else if(iy>=optFlowHeight) iy = optFlowHeight - 1;
	*u = cvGetReal2D( opticalFlow.vel_x, iy, ix );
	*v = cvGetReal2D( opticalFlow.vel_y, iy, ix );
}

void MotionTracker::getVelAverageComponents(float *u, float *v, ofRectangle* bounds){
	bool cleanBounds = false;
	if(bounds == NULL){
		bounds = new ofRectangle(0, 0, optFlowWidth, optFlowHeight);
		cleanBounds = true;
	}
	
	// normalize the bounds to optical flow system
	bounds->x = (float)bounds->x/(float)camWidth*(float)optFlowWidth; // normalize co-ords from camera size to optical flow size
	bounds->y = (float)bounds->y/(float)camHeight*(float)optFlowHeight;
	bounds->width = (float)bounds->width/(float)camWidth*(float)optFlowWidth;
	bounds->height = (float)bounds->height/(float)camHeight*(float)optFlowHeight;
	
	// fix out of bounds
	if(bounds->x < 0){
		bounds->width += bounds->x;
		bounds->x = 0;
	}
	else if(bounds->x + bounds->width > optFlowWidth){
		bounds->width -= ((bounds->x + bounds->width) - optFlowWidth);
	}
	if(bounds->y < 0){
		bounds->height += bounds->y;
		bounds->y = 0;
	}
	else if(bounds->y + bounds->height > optFlowHeight){
		bounds->height -= ((bounds->y + bounds->height) - optFlowHeight);
	}
	
/**	cout << "--bounds:norm--" << endl;
	cout << "x:" << bounds->x << endl;
	cout << "y:" << bounds->y << endl;
	cout << "w:" << bounds->width << endl;
	cout << "h:" << bounds->height << endl;
	cout << "--------------------" << endl;*/
	
	*u = 0.0;
	*v = 0.0;
	for(int i=bounds->x; i < bounds->x+(int)bounds->width; i++){
		for(int j=bounds->y; j < bounds->y+(int)bounds->height; j++){
			*u += cvGetReal2D( opticalFlow.vel_x, j, i);
			*v += cvGetReal2D( opticalFlow.vel_y, j, i);
//			cout << i << "," << j << "::" << *u << "," << *v << endl;
		}
	}
	
	*u /= 2.0 * (float)bounds->height; // effectively: u / (width*height) * width/2.0
	*v /= 2.0 * (float)bounds->width; // effectively: v / (width*height) * height/2.0
	
	if(cleanBounds)
		delete bounds;
}

void MotionTracker::getVelAverageAngleMag(float *angle, float *magnitude, ofRectangle* bounds){
	float u, v;
	this->getVelAverageComponents(&u, &v, bounds);
	*angle = tiRadiansToAngle(tiAngle(u, v));
	*magnitude = tiDistance(u, v);
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

	if(bHasNewFrame = vidGrabber.isFrameNew()){

		colorImg.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
		if(mirrorVideo) colorImg.mirror(false, true);		// mirror it

		greyNow.setFromColorImage(colorImg);			// make color image grey
		
		if (bLearnBG == true) {							// save background if nessecary
			greyBg = greyNow;
			bLearnBG = false;
		}
		
		// bg difference
		greyBgDiff.absDiff(greyBg, greyNow);			// subtract background from it
		
//		greyBgDiff.threshold(camThreshold, CV_THRESH_TOZERO);		// chop dark areas		THIS DOES NOT WORK HERE! MESSY EDGES FOR OPTICAL FLOW

		// consecutive frame difference and optical flow
		if(frameCounter > 5) {		// dont do anything until we have enough in history
			ofxCvGrayscaleImage optFlowPrev = greyPrev;
			ofxCvGrayscaleImage optFlowBgDiff = greyBgDiff;
			optFlowPrev.resize(this->optFlowWidth, this->optFlowHeight);
			optFlowBgDiff.resize(this->optFlowWidth, this->optFlowHeight);
			
			opticalFlow.calc(optFlowPrev, optFlowBgDiff, 11);
			cvSmooth(opticalFlow.vel_x, opticalFlow.vel_x, CV_BLUR , camVelocityBlur);
			cvSmooth(opticalFlow.vel_y, opticalFlow.vel_y, CV_BLUR , camVelocityBlur);
			
			greyCurDiff.absDiff(greyPrev, greyBgDiff);			// curDiff is the difference between the last 2 frames
			greyCurDiff.threshold(camThreshold, CV_THRESH_TOZERO);		// chop dark areas
			greyCurDiff.blur(3);
		} else {
			frameCounter ++;
		}
		
		greyPrev = greyBgDiff;							// save frame for next frame
		
//		greyNow.threshold(App::camThreshold, CV_THRESH_TOZERO);		// chop dark areas		GOOD FOR RENDERING
//		cvCanny(greyPrev.getCvImage(), greyNow.getCvImage(), 50, 100, 3);
//		greyNow.blur(5);

//		greyBgDiff.threshold(App::camThreshold);		// chop dark areas
		greyBgDiff.threshold(camThreshold, CV_THRESH_TOZERO);		// chop dark areas		
		greyBgDiff.blur(3);

	} 	
	//	printf("ending MotionTracker %i update \n", index);
}


//--------------------------------------------------------------
void MotionTracker::drawDebugVideo(int x, int y, int w, int h){
//		printf("drawing MOTION TRACKER %i \n", index);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	x -= w;
	colorImg.draw(x += w, y, w, h);
	drawBGDiff(x += w, y, w, h);
	drawCurDiff(x += w, y, w, h);
	drawOpticalFlow(x += w, y, w, h);
}

void MotionTracker::drawColor(int x, int y, int w, int h) {
//	glColor3f(camSilAlpha, camSilAlpha, camSilAlpha);
	colorImg.draw(x, y, w, h);
}

void MotionTracker::drawGrey(int x, int y, int w, int h) {
	glColor3f(camSilAlpha, camSilAlpha, camSilAlpha);
	greyNow.draw(x, y, w, h);
}


void MotionTracker::drawBGDiff(int x, int y, int w, int h) {
	glColor3f(camSilAlpha, camSilAlpha, camSilAlpha);
	greyBgDiff.draw(x, y, w, h);
}

void MotionTracker::drawCurDiff(int x, int y, int w, int h) {
	glColor3f(1.0f, 1.0f, 1.0f);
	greyCurDiff.draw(x, y, w, h);
}

void MotionTracker::drawOpticalFlow(int x, int y, int w, int h){
	glColor3f(0.0f, 0.0f, 0.0f);
	ofFill();
	ofRect(x, y, w, h);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef((float)w / (float)optFlowWidth, (float)h / (float)optFlowHeight, 1.0f);
	opticalFlow.draw();
	glPopMatrix();
}

void MotionTracker::drawOpticalFlowAverage(int x, int y, int w, int h, ofRectangle* averageBounds){
	float ratioX = (float)w / (float)this->optFlowWidth;
	float ratioY = (float)h / (float)this->optFlowHeight;
	float u, v;
	getVelAverageComponents(&u, &v, averageBounds);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	ofFill();
	ofRect(x, y, w, h);
	glColor3f(1.0f, 1.0f, 1.0f);
	ofCircle(x+w/2.0, y+h/2.0, 5);
	ofLine(x+w/2.0, y+h/2.0, x+w/2.0+u*ratioX/2.0, y+h/2.0+v*ratioY/2.0);
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
