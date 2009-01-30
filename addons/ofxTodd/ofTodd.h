
#ifndef _OF_TODD_H_
#define _OF_TODD_H_

#include "ofMain.h"

//FPS
void	ofDrawFPS();
void	ofDrawFPS(int x, int y);	
void	ofDrawFPS(int color);	

//Mouse
bool ofMouseOn(int mx, int my, float x, float y, float w, float h);


//Math Utils
float	ofNorm(float value, float start, float stop);
float	ofMap(float value, float istart, float istop, float ostart, float ostop);	
float	sq(float a);
float	ofLerp(float start, float stop, float amt);


//String Utils
string	ofSecondsToMinutes(float s);


//Number Utils
int		ofConstrain(int amt, int low, int high);
float	ofConstrain(float amt, float low, float high);
float	ofDegrees(float radians);
float	ofRadians(float degrees);
float	ofDist(float a, float b, float c, float d);	


//Particle Utils
float	ofRanWidth();
float	ofRanHeight();

#endif