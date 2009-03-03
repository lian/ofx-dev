/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

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
		delete []_buffer;
	}
	
	
	void setSize(int n) {
		if(n<1) return;
		
		if(_buffer) delete []_buffer;
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