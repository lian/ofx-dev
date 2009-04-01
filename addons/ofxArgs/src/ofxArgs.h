/*
 *  ofxArgs.h
 *  graffitiWall_TUIO
 *
 *  Created by Pat Long on 10/02/09.
 *  Copyright 2009 Tangible Interaction. All rights reserved.
 *
 */
#ifndef _OFXARGS
#define _OFXARGS

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class ofxArgs{
private:
	int argc;
	vector<string> args;
	map<string,string> opts;
	
	int strToInt(string value);
	float strToFloat(string value);
	
public:
	ofxArgs(int argc, char* argv[]);
	
	int getCount();
	
	bool contains(string key);

	float getFloat(string key);
	int getInt(string key);
	string getString(string key);
	
	float getFloat(int index);
	int getInt(int index);
	string getString(int index);
	
	void printArgs();
	void printOpts();
};

#endif
