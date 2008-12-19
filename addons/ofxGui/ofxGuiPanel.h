/*
 *  ofxGuiPanel.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_PANEL
#define OFX_GUI_PANEL

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiObject.h"
#include "ofxGuiGlobals.h"
#include "ofxGuiSlider.h"
#include "ofxGuiXYPad.h"
#include "ofxGuiPoints.h"
#include "ofxGuiButton.h"
#include "ofxGuiFiles.h"
#include "ofxGuiColor.h"
#include "ofxGuiMatrix.h"
#include "ofxGuiScope.h"
#include "ofxGuiKnob.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiPanel : public ofxGuiObject
{

public:

	ofxGuiPanel();

	void			init(int id, string name, int x, int y, int border, int spacing);

	bool			update(int parameterId, int task, void* data, int length);
	void			draw();

	bool			mouseDragged(int x, int y, int button);
	bool			mousePressed(int x, int y, int button);
	bool			mouseReleased(int x, int y, int button);

	ofxGuiSlider*	addSlider(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiXYPad*	addXYPad(int id, string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);
	ofxGuiPoints*	addPoints(int id, string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);
	ofxGuiButton*	addButton(int id, string name, int width, int height, bool value, int mode, int spacer);


	ofxGuiFiles*	addFiles(int id, string name, int width, int height, string value, string subPath, string suffix);
	ofxGuiColor*	addColor(int id, string name, int width, int height, ofRGBA value, int mode);
	ofxGuiMatrix*	addMatrix(int id, string name, int width, int height, int xGrid, int xGrid, int value, int mode, int spacing);
	ofxGuiScope*	addScope(int id, string name, int width, int height, int length, ofxPoint2f value, int mode);
	ofxGuiKnob*		addKnob(int id, string name, int width, int height, float min, float max, float value, int display, int steps);

	void			adjustToNewContent(int w, int h);

	void			buildFromXml();
	void			saveToXml();

	int				mBorder, mSpacing;

	vector			<ofxGuiObject*> mObjects;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
