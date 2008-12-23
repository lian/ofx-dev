

#ifndef OFX_GUI_TITLE
#define OFX_GUI_TITLE

#include "ofxSimpleGuiMain.h"


class ofxGuiTitle {
	
public:
	
	float		posx, posy;
	string		name;

	//--------------------------------------------------------------------- construct
	ofxGuiTitle() {
		ofxGuiTitle("NO TITLE");
	}
	ofxGuiTitle(string _name) {
		name = _name;
	}
	
	//--------------------------------------------------------------------- set title
	void set(string _name) {
		name = _name;
	}
	
	//--------------------------------------------------------------------- render
	void render(float _x, float _y) {
		
		//update postion of gui object
		posx = _x;
		posy = _y;
		
		
		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(posx, posy, 0);		
		ofFill();
		ofSetColor(105, 105, 105, 200);
		ofRect(0, SLIDER_H, SLIDER_W, 25);
		ofSetColor(0xffffff);
		ofDrawBitmapString(name, 3, SLIDER_H+15);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
};
#endif