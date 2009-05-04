#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ button
class ofxSimpleGuiButton : public ofxSimpleGuiControl {
	
public:
	
	bool*			value;
	
	bool			beToggle;
	bool			beenPressed;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiButton(string name, bool *value) : ofxSimpleGuiControl(name) {
		beToggle	= false;
		beenPressed = false;
		this->value	= value;
		controlType = "Button";
		setup();
	}
	
	void setup() {
		setSize(config->gridSize.x - config->padding.x, config->buttonHeight);
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	bool getValue() {
		return (*value);
	}
	void set(bool b) {
		(*value) = b;
	}
	void toggle() {
		(*value) = !(*value); 
	}
	
	void setToggleMode(bool b) {
		beToggle = b;
	}
	
	void onPress(int x, int y, int button) {
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;
	}

	void onRelease(int x, int y, int button) {
		if(!beToggle) (*value) = false;
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		
		ofEnableAlphaBlending();
		ofFill();
		setTextBGColor();
		ofRect(0, 0, width, height);
		
		// if a toggle
		if((*value) && beToggle) {
			setTextColor();
			//ofLine(0, 0, box.width, box.height);
			//ofLine(box.width, 0, 0, box.height);
		}
		
		setTextColor();
		ofDrawBitmapString(name, 3, 15);

		ofDisableAlphaBlending();
		
		glPopMatrix();
	}
	
};
