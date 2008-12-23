
#ifndef OFX_SLIDER_MOVIE
#define OFX_SLIDER_MOVIE
#include "ofxSimpleGuiMain.h"
#include "ofxGuiButton.h"

//------------------------------------------------------------------------------ Movie slider
class ofxSliderMovie : public ofMouseListener, public ofKeyListener, public ofAppListener {
	
public:
	
	float				pct;
	float				sliderPos;
	
	float*				value;
	string				name;	
	
	ofPoint				mouse;
	ofPoint				pos;
	float				barwidth;
	
	bool				mouseover;
	bool				lock;
	bool				focused;
	
	
	ofVideoPlayer*		input;
	int					guiID;
	
	float				videoLength;
	
	ofxGuiButton*		pauseBtn; 
	ofxGuiButton*		cue1Btn;
	ofxGuiButton*		cue2Btn;
	ofxGuiButton*		resetBtn;
	
	bool				doPause;
	bool				cue_1, cue_2, resetCue;
	float				cuePoint1, cuePoint2;
	
	//--------------------------------------------------------------------- movie slider
	ofxSliderMovie(string _name, ofVideoPlayer* _input, int _guiID=NULL) {
		
		guiID = _guiID;
		
		mouseover = false;
		lock	  = false;
		barwidth  = 0;
		
		name    = _name;
		input	= _input;
		
		//init
		if(_input) { 
			videoLength = input->getDuration();
		}
		
		//Buttons
		doPause = false;
		pauseBtn = new ofxGuiButton("Pause", &doPause);
		cue1Btn  = new ofxGuiButton("Cue 1", &cue_1);
		cue2Btn  = new ofxGuiButton("Cue 2", &cue_2);
		resetBtn = new ofxGuiButton("Reset", &resetCue);
		
		resetCue = false;
		cue_1 = false;
		cue_2 = false;
		cuePoint1 = 0.0;
		cuePoint2 = 1.0;
		
		ofAppEvents.addListener(this);
		ofMouseEvents.addListener(this);
		ofKeyEvents.addListener(this);
	}
	
	//--------------------------------------------------------------------- update
	void update() {
		if(!input) return;
		if(!lock) barwidth = ofMap(input->getPosition(), 0.0, 1.0, 0.0, (float)SLIDER_W);	
		
		if(resetCue) {
			cuePoint1 = 0.0;
			cuePoint2 = 1.0;
			input->setPosition(0.0);
			resetCue = false;
		}
		if(cue_1) {
			cuePoint1 = input->getPosition();
			cue_1 = false;
		}
		if(cue_2) {
			cuePoint2 = input->getPosition();
			cue_2 = false;
		}
		if(!lock) {
			if(input->getPosition() >= cuePoint2) {
				input->setPosition(cuePoint1);
			}
			else if(input->getPosition() <= cuePoint1) {
				input->setPosition(cuePoint1);
			}
		}
	}
	
	//--------------------------------------------------------------------- mouse toched
	bool mouseTouch() {
		if(mouse.x > pos.x && mouse.x < pos.x+SLIDER_W && mouse.y > pos.y && mouse.y < pos.y+SLIDER_H) {
			return true;
		}
		else {
			return false;
		}
	}
	
	//--------------------------------------------------------------------- mouse moved
	void mouseMoved(int x, int y) {
		mouse.set(x, y);
		mouseover = mouseTouch();
	}
	
	//--------------------------------------------------------------------- mouse dragged
	void mouseDragged(int x, int y, int buton) {
		if(lock) {
			
			cuePoint1 = 0.0;
			cuePoint2 = 1.0;
			
			barwidth = x-pos.x;						
			if(barwidth <= 0) barwidth = 0;
			if(barwidth >= SLIDER_W) barwidth = SLIDER_W;
			
			input->setPaused(true);
			input->setPosition(ofMap(barwidth, 0.0, (float)SLIDER_W, 0.0, 1.0));
		}
	}
	
	//--------------------------------------------------------------------- mouse pressed
	void mousePressed(int x, int y, int button) {
		if(mouseTouch()) {
			cuePoint1 = 0.0;
			cuePoint2 = 1.0;
			lock = true;
			input->setPaused(true);
			barwidth = x-pos.x;			
			input->setPaused(true);
			input->setPosition(ofMap(barwidth, 0.0, (float)SLIDER_W, 0.0, 1.0));
		}
	}
	
	//--------------------------------------------------------------------- mouse released
	void mouseReleased() {
		lock = false;
		input->play();
		input->setPaused(doPause);
	}
	
	//--------------------------------------------------------------------- render
	void render(float _x, float _y) {
		
		//update postion of gui object
		pos.set(_x, _y);
		
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		ofEnableAlphaBlending();
		ofFill();
		ofSetColor(255, 255, 255, 200);
		if(mouseover) ofSetColor(GUI_OVER_R, GUI_OVER_G, GUI_OVER_B);
		if(focused && !mouseover) ofSetColor(GUI_FOCUS_R, GUI_FOCUS_G, GUI_FOCUS_B);
		ofRect(0, 0, SLIDER_W, SLIDER_H);
		
		ofSetColor(SLIDER_R, SLIDER_G, SLIDER_B, 200);
		ofRect(0, 0, barwidth, SLIDER_H);
		
		ofSetColor(105, 105, 105, 200);
		ofRect(0, SLIDER_H, SLIDER_W, 20);
		ofSetColor(0xffffff);
		float inputpos = ofMap(input->getPosition(), 0.0, 1.0, 0.0, videoLength);
		ostringstream info;
		info << name << " [" << ofToString(inputpos, 3.0) << "/" << ofToString(videoLength, 3.0) <<"]" << endl;
		ofDrawBitmapString(info.str(), 3, SLIDER_H+15);
		ofDisableAlphaBlending();
		glPopMatrix();
		
		// a bit of a hack but for simple no images to load :)
		pauseBtn->render(pos.x, pos.y+37);
		cue1Btn->render(pos.x+25, pos.y+37);
		cue2Btn->render(pos.x+50, pos.y+37);
		resetBtn->render(pos.x+75, pos.y+37);
		
		ofSetColor(0xffffff);
		ofDrawBitmapString("1", pos.x+33, pos.y+51);
		ofDrawBitmapString("2", pos.x+56, pos.y+51);
		ofDrawBitmapString("R", pos.x+80, pos.y+51);
		
		ofSetColor(0xffffff);
		ofFill();
		
		if(!doPause) {
			ofRect(pos.x+6, pos.y+40, 2, 14);
			ofRect(pos.x+13, pos.y+40, 2, 14);
		}
		else if(doPause){
			glPushMatrix();
			glTranslatef(pos.x+6, pos.y+39, 0);
			ofTriangle(0, 0, 0, 16, 8, 8);	
			glPopMatrix();
		}
		
	}
	
};
#endif