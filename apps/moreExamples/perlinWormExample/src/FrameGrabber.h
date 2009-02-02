#pragma once

#include "ofMain.h"

class FrameGrabber{
public:
string fileName;
int frameCounter;
int maxFrames;
bool close;
ofImage img;

float seconds, minutes;

FrameGrabber(string _fileName, int _numFrames, bool _close);
void grabFrame();

};