#pragma once

#include "ofxSimpleGuiControl.h"


//------------------------------------------------------------------------------ toggle
class ofxSimpleGuiToggle : public ofxSimpleGuiControl {
	
public:
	bool	*value;
	
	//---------------------------------------------------------------------
	ofxSimpleGuiToggle(string name, bool *value) : ofxSimpleGuiControl(name) {
		this->value	= value;
		controlType = "Toggle";
		setup();
	}
	
	
	virtual void setup() {
		setSize(config->gridSize.x - config->padding.x, config->toggleHeight);
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

	void onPress(int x, int y, int button) {
		toggle();
	}

	//---------------------------------------------------------------------		
	void update() {
		if(!enabled) return;
		enabled = false;
	}

	void onKeyEnter() {
		toggle();
	}
	
	void draw(float x, float y) {
		enabled = true;
		setPos(x, y);
		
		glPushMatrix();
		glTranslatef(x, y, 0);
		
		ofEnableAlphaBlending();
		ofFill();
		setFullColor(*value);
		ofRect(0, 0, height, height);
		
		if((*value)) {
			setTextColor();
			ofLine(0, 0, height, height);
			ofLine(height, 0, 0, height);
		}
		
		setTextBGColor();
		ofRect(height, 0, width - height, height);

		setTextColor();
		ofDrawBitmapString(name, height + 15, 15);
		ofDisableAlphaBlending();
		
		glPopMatrix();
	}
};
