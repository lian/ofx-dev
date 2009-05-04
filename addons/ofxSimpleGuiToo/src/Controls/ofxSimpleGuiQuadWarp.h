#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ quad warp
class ofxSimpleGuiQuadWarp : public ofxSimpleGuiControl {
public:
	float			drawx, drawy;
	ofPoint			mouse;
	ofPoint			*pts;
	ofPoint			*pts_int;
	ofPoint			*cvpts;
	int				onPnt;
	bool			mouseOn;
	float			sw, sh;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiQuadWarp(string name, float x, float y, float sw, float sh, ofPoint **inpts) : ofxSimpleGuiControl(name) {
		cvpts		= *inpts;
		onPnt		= 6;
		setPos(x, y);
		mouseOn		= false;
		this->sw	= sw;
		this->sh	= sh;
		
		
		pts = new ofPoint[4];
		pts_int = new ofPoint[4];
		
		for(int i=0; i<4; i++) {
			float x = cvpts[i].x;
			float y = cvpts[i].y;
			pts[i].set(x, y);
			pts_int[i].set(x, y);
		}
		controlType = "QuadWarp";
		setup();
	}
	
	//---------------------------------------------------------------------
	bool checkDistanceToPoint() {
		for(int i=0; i<4; i++) {	
			ofPoint pt = pts[i] + ofPoint(x, y);
//			float dis	  = pt.distance(mouse);		  // MEMO
			float dis = 0;
			if(dis < 30) {
				mouseOn = true;
				onPnt = i;
			}
		}	
	}
	//---------------------------------------------------------------------
	void mousePressed(int x, int y, int button) {
		mouse.set(x, y);
		if(checkDistanceToPoint()) {
			
		}
	}
	
	void mouseDragged(int x, int y, int button) {
		mouse.set(x, y);
		if(checkDistanceToPoint()) {
			pts[onPnt].set(x-this->x, y-this->y);
		}
	}

	//---------------------------------------------------------------------
	void mouseReleased() {
		mouseOn = false;
		onPnt = 6;
	}
	
	//---------------------------------------------------------------------
	void draw(float x, float y) {
		setPos(x, y);
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofEnableAlphaBlending();
		ofFill();
		
		for(int i=0; i<4; i++) {
			
			if(i == onPnt) ofSetColor(255, 0, 0);
			else		   ofSetColor(255, 255, 0);
			ofRect(pts[i].x, pts[i].y, 4, 4);
		}
		
		
		ofBeginShape();
		ofNoFill();
		ofSetColor(255, 255, 255);
		for(int i=0; i<4; i++) {
			ofVertex(pts[i].x, pts[i].y);
			
			cvpts[i].x = pts[i].x*2.3;
			cvpts[i].y = pts[i].y*2.3;
			
		}
		ofEndShape(TRUE);
		ofDisableAlphaBlending();
		
		glPopMatrix();
	}
	
	
};
