/* 
	# based on post entries: http://www.openframeworks.cc/forum/viewtopic.php?t=1413
	# kylemcdonald - Posted: Wed Dec 10, 2008 9:20 pm
*/
#ifndef OFX_PROCESSING_H
#define OFX_PROCESSING_H

#include "ofMain.h"

//--------------------------------------------------------- Output
//------------------------ Text Area: print() and println() 

void ofPrint(const char* str) { 
   printf("%s", str); 
} 

void ofPrint(string &str) { 
   printf("%s", str.c_str()); 
} 

void ofPrint(int i) { 
   printf("%i", i); 
} 

void ofPrint(float f) { 
   printf("%f", f); 
} 

void ofPrint(bool b) { 
   printf("%s", b ? "true" : "false"); 
} 

void ofPrint(char c) { 
   printf("%c", c); 
} 

template <class T> 
void ofPrint(vector<T> &vec) { 
   ofPrint("{ "); 
   for(int i = 0; i < vec.size(); i++) { 
      ofPrint(vec.at(i)); 
      ofPrint(", "); 
   } 
   ofPrint("}"); 
} 

void ofPrintln() { 
   ofPrint("\n"); 
} 

template <typename T> 
void ofPrintln(T &obj) { 
   ofPrint(obj); 
   ofPrintln(); 
} 

template <typename T> 
void ofPrintln(T* obj) { 
   ofPrint(obj); 
   ofPrintln(); 
} 

//--------------------------------------------------------- Output
//-------------------------------Image: save(), saveFrame() 

void ofSave(char* filename) { 
   ofImage screen; 
   screen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR); 
   screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight()); 
   screen.saveImage(filename); 
} 

int saveImageCounter = 0; 
void ofSaveFrame() { 
   char* filename = new char[255]; 
   sprintf(filename, "screen-%0.2i.tif", saveImageCounter++); 
   ofSave(filename); 
   delete filename; 
} 

//--------------------------------------------------------- Shapes
//----------- ellipse() with strokeWeight and CENTER/CORNER 

#define OF_ELLIPSE_CENTER 0
#define OF_ELLIPSE_CORNER 1
float ofEllipse(float x, float y, float w, float h, int mode) { 
   switch(mode) { 
      case OF_ELLIPSE_CENTER: 
         ofEllipse(x, y, w, h); 
      break; 
      case OF_ELLIPSE_CORNER: 
         ofEllipse(x + w, y + h, w, h); 
      break; 
   } 
} 

//------------------------------------------------------ Transform 

// void ofRotate(float r) { 
//    glRotatef(ofDegrees(r), 0, 0, 1); 
// } 

// void ofRotateX(float r) { 
//    glRotatef(ofDegrees(r), 1, 0, 0); 
// } 

// void ofRotateY(float r) { 
//    glRotatef(ofDegrees(r), 0, 1, 0); 
// } 

// void ofRotateZ(float r) { 
//    glRotatef(ofDegrees(r), 0, 0, 1); 
// } 

//------------------------------------------------------ Math
//-- Calculation: map(), sq(), constrain(), dist(), mag() 

// float ofMap(float x, float lowIn, float highIn, float lowOut, float highOut) { 
//    return ((x - lowIn) / (highIn - lowIn)) * (highOut - lowOut) + lowOut; 
// } 

float ofConstrain(float x, float low, float high) { 
   return x < low ? low : x > high ? high : x; 
} 

float ofDist(float x1, float y1, float x2, float y2) { 
   float a = x2 - x1; 
   float b = y2 - y1; 
   return sqrt(a * a + b * b); 
} 

float ofMag(float x, float y) { 
   return ofDist(0, 0, x, y); 
} 

//------------------------------------------------------ Other

float ofRandom(float max) { 
   return ofRandom(0, max); 
} 

#endif
