/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 
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

#include "ofxObjCPointer.h"

//string ofxObjCPointer::__myInstanceName = string("ofxObjCPointer");

ofxObjCPointer::ofxObjCPointer() {
	__useCountOfThisObject = 1;
	setInstanceName("");
	setClassName("ofxObjCPointer");
}

void ofxObjCPointer::retain() {
	__useCountOfThisObject++;
//	printf("%s (%s) - retain() - Use Count: %i\n", __myInstanceName.c_str(), __myClassName.c_str(), __useCountOfThisObject);
}

void ofxObjCPointer::release() {
	__useCountOfThisObject--;
//	printf("%s (%s) - release() - Use Count: %i\n", __myInstanceName.c_str(), __myClassName.c_str(), __useCountOfThisObject);
	if(__useCountOfThisObject == 0) {
//		printf("%s (%s) - release() - deleting", __myInstanceName.c_str(), __myClassName.c_str());
		delete this;
	}
}


void ofxObjCPointer::setInstanceName(string n) {
	__myInstanceName = n;
}


void ofxObjCPointer::setInstanceName(const char* sz) {
	setInstanceName(string(sz));
}



void ofxObjCPointer::setClassName(string n) {
	__myClassName = n;
}


void ofxObjCPointer::setClassName(const char* sz) {
	setClassName(string(sz));
}

string ofxObjCPointer::getClassName() {
	return __myClassName;
}

string ofxObjCPointer::getInstanceName() {
	return __myInstanceName;
}

