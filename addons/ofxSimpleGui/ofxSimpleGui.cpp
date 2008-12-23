
#include "ofxSimpleGui.h"

//------------------------------------------------------------------------------ constrcutor
ofxSimpleGui::ofxSimpleGui() {
	
	guiFocus	= 0;
	guiCount	= 0;
	
	mx			= 0;
	my			= 0;
	key			= 0;
	mousedown	= false;
	mouseup		= true;
	xmlFile		= "NULL";
	verbose		= true;
	doRender	= true;
	doAutoSave	= false;
	doSave		= false;
	saveButton	= new ofxToggle("Save XML Settings", &doSave); 
	
	setListeners();
}

//------------------------------------------------------------------------------ set listeners
void ofxSimpleGui::setListeners() {
	ofMouseEvents.addListener(this);
	ofKeyEvents.addListener(this);
	ofAppEvents.addListener(this);
}

//------------------------------------------------------------------------------ toggle render
void ofxSimpleGui::toggleRender() {
	doRender = !doRender;
}

//------------------------------------------------------------------------------ auto save
void ofxSimpleGui::setAutoSave(bool b) {
	doAutoSave = b;
}

//------------------------------------------------------------------------------ set from xml
void ofxSimpleGui::setFromXML(string file) {
	
	xmlFile = file;
	
	if(XML.loadFile(file)) {
		
		// --- Toggles ---
		int numTogglesTags = XML.getNumTags("toggles");
		if(numTogglesTags > 0) {
			XML.pushTag("toggles", numTogglesTags-1);
			int numElements  = XML.getNumTags("element");
			for(int i=0; i<numElements; i++) {
				
				int node_id		 =  XML.getValue("element:id", 0, i);
				string node_name =  XML.getValue("element:name", "Name", i);
				
				for(int j=0; j<toggles.size(); j++) {
					if(toggles[j]->guiID == node_id) {
						toggles[j]->set(XML.getValue("element:value", 0, i));
					}
				}
			}
		}
		XML.popTag();
		
		// --- Float Sliders
		int numSliderFTags = XML.getNumTags("slidersF");
		if(numSliderFTags > 0) {
			XML.pushTag("slidersF", numSliderFTags-1);
			int numElements  = XML.getNumTags("element");
			for(int i=0; i<numElements; i++) {
				
				int node_id		 =  XML.getValue("element:id", 0, i);
				string node_name =  XML.getValue("element:name", "Name", i);
				
				for(int j=0; j<slidersF.size(); j++) {
					if(slidersF[j]->guiID == node_id) {
						slidersF[j]->set(XML.getValue("element:value", 0.0, i));
					}
				}
			}
		}
		XML.popTag();
		
		// --- Int Sliders
		int numSliderITags = XML.getNumTags("slidersI");
		if(numSliderITags > 0) {
			XML.pushTag("slidersI", numSliderITags-1);
			int numElements  = XML.getNumTags("element");
			for(int i=0; i<numElements; i++) {
				
				int node_id		 =  XML.getValue("element:id", 0, i);
				string node_name =  XML.getValue("element:name", "Name", i);
				
				for(int j=0; j<slidersI.size(); j++) {
					if(slidersI[j]->guiID == node_id) {
						slidersI[j]->set(XML.getValue("element:value", 0.0, i));
					}
				}
			}
		}
		XML.popTag();
		
		// --- 2D Sliders
		int numSlider2DTags = XML.getNumTags("sliders2D");
		if(numSliderITags > 0) {
			XML.pushTag("sliders2D", numSlider2DTags-1);
			int numElements  = XML.getNumTags("element");
			for(int i=0; i<numElements; i++) {
				
				int node_id		 =  XML.getValue("element:id", 0, i);
				string node_name =  XML.getValue("element:name", "Name", i);
				
				for(int j=0; j<sliders2d.size(); j++) {
					if(sliders2d[j]->guiID == node_id) {
						sliders2d[j]->set(XML.getValue("element:valueX", 0.0, i), XML.getValue("element:valueY", 0.0, i));
						sliders2d[j]->setMin(XML.getValue("element:minX", 0.0, i), XML.getValue("element:minY", 0.0, i));
						sliders2d[j]->setMax(XML.getValue("element:maxX", 0.0, i), XML.getValue("element:maxY", 0.0, i));
					}
				}
			}
		}
		XML.popTag();		
		
		
		if(verbose) cout << " --- GUI set From XML ---\n";
	}
	else cout << " --- ERROR IN XML (no settings or missing file) ---\n";
}

//------------------------------------------------------------------------------ save to xml
void ofxSimpleGui::saveToXML(string file) {
	
	XML.clear();	// clear cause we are building a new xml file
	
	// --- Toggles ---
	XML.addTag("toggles");
	XML.pushTag("toggles");
	for(int i=0; i<toggles.size(); i++) {
		XML.addTag("element");
		
		XML.pushTag("element", i);
		XML.addValue("id", toggles[i]->guiID);
		XML.addValue("name", toggles[i]->name);
		XML.addValue("value", (*toggles[i]->value));
		XML.popTag();
	}
	XML.popTag();
	
	// --- sliders F ---
	XML.addTag("slidersF");
	XML.pushTag("slidersF");
	for(int i=0; i<slidersF.size(); i++) {
		XML.addTag("element");
		
		XML.pushTag("element", i);
		XML.addValue("id", slidersF[i]->guiID);
		XML.addValue("name", slidersF[i]->name);
		XML.addValue("value", (float)(*slidersF[i]->value));
		XML.addValue("min", (float)slidersF[i]->min);
		XML.addValue("max", (float)slidersF[i]->max);
		XML.popTag();
	}
	XML.popTag();
	
	// --- sliders I ---
	XML.addTag("slidersI");
	XML.pushTag("slidersI");
	for(int i=0; i<slidersI.size(); i++) {
		XML.addTag("element");
		
		XML.pushTag("element", i);
		XML.addValue("id", slidersI[i]->guiID);
		XML.addValue("name", slidersI[i]->name);
		XML.addValue("value", (int)(*slidersI[i]->value));
		XML.addValue("min", (int)slidersI[i]->min);
		XML.addValue("max", (int)slidersI[i]->max);
		XML.popTag();
	}
	XML.popTag();
	
	// --- 2D Slider ---
	XML.addTag("sliders2D");
	XML.pushTag("sliders2D");
	for(int i=0; i<sliders2d.size(); i++) {
		XML.addTag("element");
		
		XML.pushTag("element", i);
		XML.addValue("id", sliders2d[i]->guiID);
		XML.addValue("name", sliders2d[i]->name);
		XML.addValue("valueX", (*sliders2d[i]->value).x);
		XML.addValue("valueY", (*sliders2d[i]->value).y);
		
		XML.addValue("minX", sliders2d[i]->min.x);
		XML.addValue("minY", sliders2d[i]->min.y);
		XML.addValue("maxX", sliders2d[i]->max.x);
		XML.addValue("maxY", sliders2d[i]->max.y);
		
		XML.popTag();
	}
	XML.popTag();
	
	/*
	 // --- Toggles ---
	 int numTogglesTags = XML.getNumTags("toggles");
	 if(numTogglesTags > 0) {
	 XML.pushTag("toggles", numTogglesTags-1);
	 int numElements  = XML.getNumTags("toggles");
	 
	 // if there are no toggles create xml node 
	 // for the toggles
	 if(numElements <= 0) {
	 for(int j=0; j<toggles.size(); j++) {
	 //cout << j << endl;
	 //XML.addTag("element");
	 }
	 }
	 else {
	 for(int i=0; i<numElements; i++) {
	 
	 int node_id		 =  XML.getValue("element:id", 0, i);
	 string node_name =  XML.getValue("element:name", "Name", i);
	 
	 for(int j=0; j<toggles.size(); j++) {
	 if(toggles[j]->xmlID == node_id) {
	 //	XML.setValue("element:value", (*toggles[j]->value), i);
	 }
	 }
	 }
	 }
	 
	 //only pop if there are element tags
	 //if(numElements !=0) XML.popTag();
	 }
	 
	 // --- Float Sliders
	 int numSliderFTags = XML.getNumTags("slidersF");
	 if(numSliderFTags > 0) {
	 XML.pushTag("slidersF", numSliderFTags-1);
	 int numElements  = XML.getNumTags("element");
	 for(int i=0; i<numElements; i++) {
	 
	 int node_id		 =  XML.getValue("element:id", 0, i);
	 string node_name =  XML.getValue("element:name", "Name", i);
	 
	 for(int j=0; j<slidersF.size(); j++) {
	 if(slidersF[j]->xmlID == node_id) {
	 XML.setValue("element:value", (*slidersF[j]->value), i);
	 XML.setValue("element:min", (*slidersF[j]->min), i);
	 XML.setValue("element:max", (*slidersF[j]->max), i);
	 }
	 }
	 }
	 }
	 XML.popTag();
	 
	 
	 // --- Int Sliders
	 int numSliderITags = XML.getNumTags("slidersI");
	 if(numSliderITags > 0) {
	 XML.pushTag("slidersI", numSliderITags-1);
	 int numElements  = XML.getNumTags("element");
	 for(int i=0; i<numElements; i++) {
	 
	 int node_id		 =  XML.getValue("element:id", 0, i);
	 string node_name =  XML.getValue("element:name", "Name", i);
	 
	 for(int j=0; j<slidersI.size(); j++) {
	 if(slidersI[j]->xmlID == node_id) {
	 XML.setValue("element:value", (*slidersI[j]->value), i);
	 XML.setValue("element:min", (*slidersI[j]->min), i);
	 XML.setValue("element:max", (*slidersI[j]->max), i);
	 }
	 }
	 }
	 }
	 XML.popTag();
	 */
	XML.saveFile(file);
	cout << " --- Settings Saved ---\n";
	
}

//------------------------------------------------------------------------------ set gui title
void ofxSimpleGui::setTitle(string name) {
	guiTitle.set(name);
}

//------------------------------------------------------------------------------ set verbose
void ofxSimpleGui::setVerbose(bool v) {
	verbose = v;
}

//------------------------------------------------------------------------------ update
void ofxSimpleGui::update() {
	
	//save to xml	
	if(doSave) {
		if(xmlFile.compare("NULL") != 0) {
			saveToXML(xmlFile);
			doSave = false;
		}
	}
}

//------------------------------------------------------------------------------ get value 		
int ofxSimpleGui::getValueI(string nameID) {
	
	//SLIDER INTS
	for(int i=0; i<slidersI.size(); i++) {
		if(nameID.compare(slidersI[i]->name) == 0) return slidersI[i]->getValue();
		else return NULL;
	}
}

float ofxSimpleGui::getValueF(string nameID) {
	for(int i=0; i<slidersF.size(); i++) {
		if(nameID.compare(slidersF[i]->name) == 0) return slidersF[i]->getValue();
		else return NULL;
	}
}

bool ofxSimpleGui::getValueB(string nameID) {
	for(int i=0; i<toggles.size(); i++) {
		if(nameID.compare(toggles[i]->name) == 0) return toggles[i]->getValue();
		else return NULL;
	}
}

//------------------------------------------------------------------------------ render focus
void ofxSimpleGui::renderFocus(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	ofFill();
	ofSetColor(GUI_FOCUS_R, GUI_FOCUS_G, GUI_FOCUS_B, 200);
	ofRect(0, 0, 10, 10);
	glPopMatrix();
}
//------------------------------------------------------------------------------ draw		
void ofxSimpleGui::draw() {
	
	if(!doRender) return;
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	
	ofPoint	offset(10, 10);
	
	xspace = 10;
	yspace = 10;
	int sp = 50;
	
	//Gui Title
	guiTitle.render(GUI_OFFSET_X, GUI_OFFSET_Y);
	//Save XML Button
	saveButton->render(GUI_OFFSET_X, GUI_OFFSET_Y+42);
	
	yspace += sp;
	
	//Sliders 2d
	ofPoint slider2d_pos(0, 0);
	for(int i=0; i<sliders2d.size(); i++) {
		slider2d_pos.x = 260 + ((i%3) * (SLIDER2D_W+5));
		slider2d_pos.y = GUI_OFFSET_Y+77 + (floor(i/3) * (SLIDER2D_H+50));
		sliders2d[i]->render(slider2d_pos.x, slider2d_pos.y);
		if(guiFocus == sliders2d[i]->guiID) sliders2d[i]->focused = true;
		else							   sliders2d[i]->focused = false;
	}
	
	//Movie
	ofPoint movie_pos(GUI_OFFSET_X+250, 250); 
	for(int i=0; i<slidersMovie.size(); i++) {
		slidersMovie[i]->render(movie_pos.x, movie_pos.y);
		movie_pos.y += 66;
	}
	
	//Int Slider
	ofPoint slider_pos(GUI_OFFSET_X, GUI_OFFSET_Y+40);
	for(int i=0; i<slidersI.size(); i++) {
		slider_pos.y += SLIDER_H+25;
		slidersI[i]->render(slider_pos.x, slider_pos.y);
		if(guiFocus == slidersI[i]->guiID) slidersI[i]->focused = true;
		else							   slidersI[i]->focused = false;	
	}
	
	//Float Slider
	for(int i=0; i<slidersF.size(); i++) {
		slider_pos.y += SLIDER_H+25;
		slidersF[i]->render(slider_pos.x, slider_pos.y);
		if(guiFocus == slidersF[i]->guiID) slidersF[i]->focused = true;
		else							   slidersF[i]->focused = false;	
	}
	
	//Toggles
	ofPoint toggle_pos(GUI_OFFSET_X, slider_pos.y+45);
	for(int i=0; i<toggles.size(); i++) {		
		toggles[i]->render(toggle_pos.x, toggle_pos.y);
		if(guiFocus == toggles[i]->guiID) toggles[i]->focused = true;
		else							  toggles[i]->focused = false;
		toggle_pos.y += 25;
	}
	
	
	
	
	
	
	//VIDEO WARPER
	for(int i=0; i<quadWarpers.size(); i++) {
		quadWarpers[i]->render();
	}
	
	glPopMatrix();
}

//------------------------------------------------------------------------ adding ui elements	
void ofxSimpleGui::addSlider2d(string _name, ofxVec2f* _value, float xmin, float xmax, float ymin, float ymax) {
	sliders2d.push_back(new ofxGuiSlider2d(_name, _value, xmin, xmax, ymin, ymax, guiCount++));
}	
void ofxSimpleGui::addSlider(string _name, int *_value, int _min, int _max) {
	slidersI.push_back(new ofxSliderInt(_name, _value, _min, _max, guiCount++));
}
void ofxSimpleGui::addSlider(string _name, float *_value, float _min, float _max) {
	slidersF.push_back(new ofxSliderFloat(_name, _value, _min, _max, guiCount++));
}
void ofxSimpleGui::addMovieSlider(string _name, ofVideoPlayer* _input) {
	slidersMovie.push_back(new ofxSliderMovie(_name, _input, guiCount++));
}	
void ofxSimpleGui::addQuadWarper(float x, float y, float sw, float sh, ofPoint **pts) {
	quadWarpers.push_back(new ofxQuadWarp(x, y, sw, sh, pts));
}
void ofxSimpleGui::addToggle(string _name, bool *_value) {
	toggles.push_back(new ofxToggle(_name, _value, guiCount++));
}	
void ofxSimpleGui::addTitle(string _name) {
	titles.push_back(new ofxGuiTitle(_name));
}

//------------------------------------------------------------------------ mouse moved
void ofxSimpleGui::mouseMoved(int x, int y) {
	mx = x; my = y;
}

//------------------------------------------------------------------------ mouse released
void ofxSimpleGui::mouseReleased() {
	if(doAutoSave) {
		saveToXML(xmlFile);
	}
}

//------------------------------------------------------------------------ key released
void ofxSimpleGui::keyReleased(int key) {
	if(doAutoSave) {
		saveToXML(xmlFile);
	}
}

//------------------------------------------------------------------------ key press
void ofxSimpleGui::keyPressed(int key) {
	if(key == OF_KEY_DOWN) {
		if(guiFocus <= guiCount) guiFocus ++;
		else guiFocus = 0; 
	}
	if(key == OF_KEY_UP) {
		if(guiFocus <= guiCount) guiFocus --;
		else guiFocus = guiCount;
	}
	if(key == OF_KEY_RIGHT) {
		//INT
		for(int i=0; i<slidersI.size(); i++) {
			if(guiFocus == slidersI[i]->guiID) slidersI[i]->add();   			
		}
		//FLOAT
		for(int i=0; i<slidersF.size(); i++) {
			if(guiFocus == slidersF[i]->guiID) slidersF[i]->add();   			
		}
	}
	if(key == OF_KEY_LEFT) {
		//INT
		for(int i=0; i<slidersI.size(); i++) {
			if(guiFocus == slidersI[i]->guiID) slidersI[i]->sub();   			
		}
		//FLOAT
		for(int i=0; i<slidersF.size(); i++) {
			if(guiFocus == slidersF[i]->guiID) slidersF[i]->sub();   			
		}
	}
	if(key == OF_KEY_RETURN) {
		//TOGGLE
		for(int i=0; i<toggles.size(); i++) {
			if(guiFocus == toggles[i]->guiID) toggles[i]->toggle();   			
		}
	}
	
}
