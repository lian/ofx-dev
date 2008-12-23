/* 
	# based on post entries: http://www.openframeworks.cc/forum/viewtopic.php?t=1413
	# started by vanderlin - Posted: Wed Dec 10, 2008 7:48 pm
*/
#include "ofMoreUtils.h"

//-------------------------------------------------- Graphic Utils 

void ofDrawFPS(int x=15, int y=ofGetHeight()-35) { 
   glPushMatrix(); 
   glTranslatef(x, y, 0); 
   ofSetRectMode(OF_RECTMODE_CORNER); 
   ofFill(); 
   ofSetColor(0x000000); 
   ofSetColor(0, 255, 0); 
   string fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 2); 
   ofDrawBitmapString(fpsStr, 0, 0); 
   glPopMatrix(); 
} 

//-------------------------------------------------- Math Utils 

float ofNorm(float value, float start, float stop) { 
   return (value - start) / (stop - start); 
} 

float ofMap(float value, float istart, float istop, float ostart, float ostop) { 
   return ostart + (ostop - ostart) * ((value - istart) / (istop - istart)); 
} 

float ofDist(float a, float b, float c, float d) { 
   return sqrt(double((a - c) * (a - c) + (b - d) * (b - d))); 
} 

int ofConstrain(int amt, int low, int high) { 
   return (amt < low) ? low : ((amt > high) ? high : amt); 
} 

float ofSq(float n) { 
   return n*n; 
} 

float ofDegrees(float radians) { 
   return radians * RAD_TO_DEG; 
} 

float ofRadians(float degrees) { 
    return degrees * DEG_TO_RAD; 
} 

float ofLerp(float start, float stop, float amt) { 
    return start + (stop-start) * amt; 
} 

float dist(float x1, float y1, float x2, float y2) { 
    return sqrt(ofSq(x2-x1) + ofSq(y2-y1)); 
} 

float dist(float x1, float y1, float z1, float x2, float y2, float z2) { 
    return sqrt(ofSq(x2-x1) + ofSq(y2-y1) + ofSq(z2-z1)); 
} 

//-------------------------------------------------- Other Utils 

float ofRanWidth() { 
   return ofRandom(0, ofGetWidth()); 
} 
float ofRanHeight() { 
   return ofRandom(0, ofGetHeight()); 
}