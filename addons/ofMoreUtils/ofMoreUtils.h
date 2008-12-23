/* 
	# based on post entries: http://www.openframeworks.cc/forum/viewtopic.php?t=1413
	# started by vanderlin - Posted: Wed Dec 10, 2008 7:48 pm
*/
#ifndef OF_MORE_UTILS
#define OF_MORE_UTILS


#include "ofConstants.h" 
#include "ofMain.h" 
#include "ofxProcessing.h"
#include "ofxMemoUtils.h"

//-------------------------------------------------- Graphic Utils 

void   ofDrawFPS(int x=15, int y=ofGetHeight()-35); 

//-------------------------------------------------- Math Utils 

float   ofNorm(float value, float start, float stop); 
float   ofMap(float value, float istart, float istop, float ostart, float ostop); 
float   ofDist(float a, float b, float c, float d); 
int      ofConstrain(int amt, int low, int high); 
float   ofSq(float n); 
float   ofDegrees(float radians); 
float   ofRadians(float degrees); 
float   ofLerp(float start, float stop, float amt); 
float   dist(float x1, float y1, float x2, float y2); 
float   dist(float x1, float y1, float z1, float x2, float y2, float z2); 

//-------------------------------------------------- Other Utils 

float ofRanWidth(); 
float ofRanHeight()

#endif
