/***********************************************************************

 Super simple Objective C style Smart Pointer which keeps reference count 
 and frees memory when reference count is zero.
 
 Any object you want this functionality, should extend ofxObjCPointer

 
 If someone passes you a pointer and you only need the data temporarily
 (you do NOT need the data beyond the scope of the function)
 just use the pointer/data and do NOT call any of the special methods (retain or release).
 
 If you DO need to keep the data beyond the scope of the function,
 call myObjPointer->retain() on the pointer to indicate that you need the data, 
 and call myObjPointer->release() when you are done with it.
 
 If you allocated the pointer with 'new MyObject' or retained it with myObj->retain()
 then you must ALWAYS release it 'myObj->release()' when you are done.
 You do not need to worry about whether anyone else is using the data or not, 
 the reference count will take care of that.
 
 Never use 'delete myObj', only use 'myObj->release();
 
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
#include "ofMain.h"
//#include <string>
 
class ofxObjCPointer {
public:
	bool verbose;
	
	ofxObjCPointer();
	virtual ~ofxObjCPointer();
	
	// use this to indicate you are using the object and want to keep it safe in memory
	void retain();
	
	// use this to indicate you re done with the object and as far as you are concerned, it can be deleted
	void release();	

	void setInstanceName(string n);
	void setInstanceName(const char* sz); 
	
	string getClassName();
	string getInstanceName();
	
protected:	
	void setClassName(string n);
	void setClassName(const char* sz); 
	
private:
	unsigned int	__useCountOfThisObject;
	string			__myClassName;
	string			__myInstanceName;
};

