

#ifndef OFX_GUI_SLIDER_2D
#define OFX_GUI_SLIDER_2D

#include "ofxSimpleGuiMain.h"

class ofxGuiSlider2d : public ofMouseListener, public ofAppListener {
	
public:
	
	bool		mouseover;
	bool		lock;
	bool		focused;
	ofPoint		mouse;
	ofPoint		pos;
	string		name;
	
	ofxVec2f	point;
	ofxVec2f*	value;
	ofxVec2f	min, max;
	int			guiID;
	
	//--------------------------------------------------------------------- construct
	ofxGuiSlider2d(string _name, ofxVec2f* _value, float xmin, float xmax, float ymin, float ymax, int _guiID=NULL) {
		
		guiID	  = _guiID;
		
		mouseover = false;
		lock	  = false;
		focused	  = false;
		name = _name;
		
		pos.set(0, 0);
		point.set(0, 0);
		min.set(xmin, ymin);
		max.set(xmax, ymax);
		value = _value;
		
		//init set
		point.x = ofMap((*value).x, xmin, xmax, pos.x, pos.x+SLIDER2D_W); 
		point.y = ofMap((*value).y, ymin, ymax, pos.y, pos.y+SLIDER2D_H); 
		
		ofMouseEvents.addListener(this);
		ofAppEvents.addListener(this);
	}
	
	//--------------------------------------------------------------------- mouse touch
	bool mouseTouch() {
		if(mouse.x > pos.x && mouse.x < pos.x+SLIDER2D_W && mouse.y > pos.y && mouse.y < pos.y+SLIDER2D_H) {
			return true;
		}
		else return false;
	}
	
	//--------------------------------------------------------------------- set xy
	void set(float x, float y) {
		(*value).x = x;
		(*value).y = y;
	}
	void setMin(float x, float y) {
		min.x = x;
		min.y = y;
	}	
	void setMax(float x, float y) {
		max.x = x;
		max.y = y;
	}	
	//--------------------------------------------------------------------- mouse move
	void mouseMoved(int x, int y) {
		mouse.set(x, y);
	}
	
	//--------------------------------------------------------------------- mouse pressed
	void mousePressed(int x, int y, int button) {
		mouse.set(x, y);
		
		if(mouseTouch()) {
			lock = true;
			point.set(x, y);
		}
	}
	
	//--------------------------------------------------------------------- mouse dragged
	void mouseDragged(int x, int y, int button) {
		mouse.set(x, y);
		if(lock) {
			point.set(x, y);
		}
	}
	
	//--------------------------------------------------------------------- mouse released
	void mouseReleased() {
		lock = false;
	}
	
	//--------------------------------------------------------------------- update
	void update() {
		
		if(point.x > pos.x+SLIDER2D_W)				point.x = pos.x+SLIDER2D_W; 
		else if(point.x < pos.x)					point.x = pos.x; 
		
		if(point.y > pos.y+SLIDER2D_H)				point.y = pos.y+SLIDER2D_H;
		else if(point.y < pos.y)					point.y = pos.y;
		
		if(lock){
			(*value).x = ofMap(point.x, pos.x, pos.x+SLIDER2D_W, min.x, max.x); 
			(*value).y = ofMap(point.y, pos.y, pos.y+SLIDER2D_H, min.y, max.y); 
		}
	}
	
	//--------------------------------------------------------------------- render
	void render(float _x, float _y) {
		
		//update postion of gui object
		pos.set(_x, _y);
		ofxVec2f	pointv;
		pointv.x = ofMap((*value).x, min.x, max.x, pos.x, pos.x+SLIDER2D_W);
		pointv.y = ofMap((*value).y, min.y, max.y, pos.y, pos.y+SLIDER2D_H);
		
		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);		
		
		ofFill();
		ofSetColor(SLIDER_R, SLIDER_G, SLIDER_B, 200);
		if(mouseTouch() || lock)	ofSetColor(GUI_OVER_R, GUI_OVER_G, GUI_OVER_B, 200);
		if(focused && !mouseTouch()) ofSetColor(GUI_FOCUS_R, GUI_FOCUS_G, GUI_FOCUS_B);
		
		ofRect(0, 0, SLIDER2D_W, SLIDER2D_H);
		
		ofFill();
		ofSetColor(105, 105, 105, 200);
		ofRect(0, SLIDER2D_H, SLIDER2D_W, 50);
		ofSetColor(0xffffff);
		ofDrawBitmapString(name+"\nx:"+ofToString(value->x, 2)+"\ny:"+ofToString(value->y, 2), 3, SLIDER2D_H+15);
		
		ofSetColor((int)SLIDER_R/10, (int)SLIDER_G/10, (int)SLIDER_B/10, 200);
		ofCircle(pointv.x-pos.x, pointv.y-pos.y, 2);
		ofSetColor((int)SLIDER_R/10, (int)SLIDER_G/10, (int)SLIDER_B/10, 100);
		
		ofLine(pointv.x-pos.x, 0, pointv.x-pos.x, SLIDER2D_H);
		ofLine(0, pointv.y-pos.y,SLIDER2D_W, pointv.y-pos.y);
		
		glPopMatrix();
		ofDisableAlphaBlending();
		
	}
	
};
#endif