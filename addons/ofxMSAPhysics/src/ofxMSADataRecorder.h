/*
 *  ofxMSADataRecorder.h
 *  MSH Ribbons 00573
 *
 *  Created by Mehmet Akten on 03/10/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#pragma once

#define OF_ADDON_USING_OFXMSADATARECORDER

#include "ofMain.h"

#define OFX_MSA_DATA_IDLE		0					// do nothing
#define OFX_MSA_DATA_SAVE		1					// save
#define OFX_MSA_DATA_LOAD		2					// load


// always tries to read _numItems, no matter how big the file is (quicker to not reallocate the buffer when reading)
template <typename Type> class ofxMSADataRecorder {
public:
	ofxMSADataRecorder() {
		_buffer = 0;
		_curItem = 0;
	}
	
	virtual ~ofxMSADataRecorder() {
		delete _buffer;
	}
	
	
	void setSize(int n) {
		if(_buffer) delete _buffer;
		_numItems = n;
		_buffer = new Type[_numItems];
		_curItem = 0;
	}
	
	void setFilename(string f) {
		_fileName = ofToDataPath(f);
	}
	
	void add(Type &t) {
		_buffer[_curItem++] = t;
	}
	
	Type &get() {
		return _buffer[_curItem++];
	}
	
	bool save(int i) {
		_curItem = 0;
		FILE *fileOut;											// output BIN file
		string fullFileName = _fileName + "_" + ofToString(i) + ".bin";
		fileOut = fopen(fullFileName.c_str(), "wb");					// open output bin file for writing
		if(fileOut == NULL) {
			printf("ofxMSADataRecorder::save() - could not save %s\n", fullFileName.c_str());
			exit(1);
		}
		int numWritten = fwrite(_buffer, sizeof(Type), _numItems, fileOut);
		fclose(fileOut);
		return numWritten == _numItems;
	}
	
	bool load(int i) {
		_curItem = 0;
		FILE *fileIn;											// output BIN file
		string fullFileName = _fileName + "_" + ofToString(i) + ".bin";
		fileIn = fopen(fullFileName.c_str(), "rb");					// open output bin file for writing
		if(fileIn == NULL) {
			printf("ofxMSADataRecorder::load() - could not load %s\n", fullFileName.c_str());
			exit(1);
		}
		
		int numRead = fread(_buffer, sizeof(Type), _numItems, fileIn);
		fclose(fileIn);
		return true;
	}

	
protected:
	Type *_buffer;
	int _numItems;
	int _curItem;
	string _fileName;
};