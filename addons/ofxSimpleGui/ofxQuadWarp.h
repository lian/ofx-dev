
#ifndef OFX_QUARD_WARP
#define OFX_QUARD_WARP
#include "ofxSimpleGuiMain.h"

//------------------------------------------------------------------------------ quad warp
class ofxQuadWarp : public ofKeyListener, public ofMouseListener, public ofAppListener {
	
public:
	float			drawx, drawy;
	ofxPoint2f		mouse;
	ofxPoint2f		offset;
	ofxPoint2f	*	pts;
	ofxPoint2f	*	pts_int;
	ofPoint		*   cvpts;
	int				onPnt;
	bool			mouseOn;
	float			sw, sh;
	
	//---------------------------------------------------------------------
	ofxQuadWarp(float x, float y, float _sw, float _sh, ofPoint **_pts) {
		
		cvpts	= *_pts;
		onPnt	= 6;
		offset.set(x, y);
		mouseOn = false;
		sw		= _sw;
		sh		= _sh;
		
		
		pts = new ofxPoint2f[4];
		pts_int = new ofxPoint2f[4];
		
		for(int i=0; i<4; i++) {
			float x = cvpts[i].x;
			float y = cvpts[i].y;
			pts[i].set(x, y);
			pts_int[i].set(x, y);
		}
		
		ofMouseEvents.addListener(this);
		ofKeyEvents.addListener(this);	
		ofAppEvents.addListener(this);
		
	}
	
	//---------------------------------------------------------------------
	bool checkDistanceToPoint() {
		for(int i=0; i<4; i++) {	
			ofxPoint2f pt = pts[i]+offset;
			float dis	  = pt.distance(mouse);
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
			pts[onPnt].set(x-offset.x, y-offset.y);
		}
	}
	//---------------------------------------------------------------------
	void mouseReleased() {
		mouseOn = false;
		onPnt = 6;
	}
	
	//---------------------------------------------------------------------
	void render() {
		glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
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
#endif