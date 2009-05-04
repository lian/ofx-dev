#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ button
class ofxSimpleGuiTitle : public ofxSimpleGuiControl {
	
public:
	
	bool*			value;
	
	bool			beToggle;
	bool			beenPressed;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiTitle(string name, bool *value = NULL) : ofxSimpleGuiControl(name) {
		beToggle	= false;
		beenPressed = false;
		this->value	= value;
		controlType = "Title";
		setup();
	}
	
	void setup() {
		setSize(config->gridSize.x - config->padding.x, config->titleHeight);
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		if(!value) return;
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		if(!value) return;
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	bool getValue() {
		if(!value) return false;
		return (*value);
	}
	void set(bool b) {
		if(!value) return;
		(*value) = b;
	}
	void toggle() {
		if(!value) return;
		(*value) = !(*value); 
	}
	
	void setToggleMode(bool b) {
		if(!value) return;
		beToggle = b;
	}
	
	void onPress(int x, int y, int button) {
		if(!value) return;
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;
	}
	
	void onRelease(int x, int y, int button) {
		if(!value) return;
		if(!beToggle) (*value) = false;
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		
		ofEnableAlphaBlending();
		ofFill();
		setTextBGColor(value != NULL);
		ofRect(0, 0, width, height);
		
		// if a toggle
		if(value && (*value) && beToggle) {
			setTextColor();
			//ofLine(0, 0, box.width, box.height);
			//ofLine(box.width, 0, 0, box.height);
		}
		
		setTextColor(value != NULL);
		ofDrawBitmapString(name, 3, 15);
		
		ofDisableAlphaBlending();
		
		glPopMatrix();
	}
	
};
