#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ toggle
class ofxSimpleGuiContent  : public ofxSimpleGuiControl {
public:
	float			fixwidth;
	float			fixheight;
	ofBaseDraws		*content;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiContent(string name, ofBaseDraws* content, float fixwidth=250.0) : ofxSimpleGuiControl(name) {
		this->content = content;
		this->fixwidth  = fixwidth;
		controlType = "Content";
		setup();
	}
	
	void setup() {
		fixheight = fixwidth * content->getHeight()/content->getWidth();
		setSize(fixwidth, fixheight + config->sliderTextHeight);
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		setup();
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofEnableAlphaBlending();
		ofFill();
		glColor4f(0, 0, 0, 0.8f);
		ofRect(0, 0, width, fixheight);

		ofSetColor(0xffffff);
		content->draw(0, 0, width, fixheight); 
		
		ofFill();
		setTextBGColor();
		ofRect(0, fixheight, width, config->sliderTextHeight);

		setTextColor();
		ofDrawBitmapString(name, 3, fixheight + 15);
		ofDisableAlphaBlending();
		glPopMatrix();
	}
	
};
