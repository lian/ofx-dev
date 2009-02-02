#ifndef IMAGESEQUENCER_H
#define IMAGESEQUENCER_H
#include "ofMain.h"

class SnapShooter{
public:

string fileName;
int frameCounter;
int maxFrames;
bool close;
ofImage img;

float seconds, minutes;

SnapShooter(string _fileName, int _numFrames, bool _close);
~SnapShooter();
void grabFrame();

};




#endif