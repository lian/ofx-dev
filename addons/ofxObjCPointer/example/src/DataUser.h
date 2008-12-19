/*
 *  Users.h
 *  objcPointerTest
 *
 *  Created by Mehmet Akten on 15/10/2008.
 *  Copyright 2008 MSA Visuals. All rights reserved.
 *
 */

#pragma once


/********** Example data user *************/
class DataUser {
public:
	MyObject *myData;
	int	index;
	
	DataUser() {
		printf("User::User()\n");
		myData = NULL;
	}
	
	~DataUser() {
		printf("User::~User()\n");
		releaseData();
	}
	
	
	// point myData pointer to the passed data, and retain it
	void setData(MyObject *d) {
		printf("User::setData(%p)\n", d);		
		myData = d;
		myData->retain();
	}
	
	
	// just some arbitrary function to do something with the data
	void displayData() {
		if(myData) {
			glColor4f(0, 0, 0, 0);
			ofRect(myData->a, myData->b, myData->c, myData->d);
			glColor4f(1, 0, 0, 1);
			ofDrawBitmapString( " Data for " + ofToString(index) + ": \n   " + ofToString(myData->a, 2) + "\n   " + ofToString(myData->b, 2) + "\n   " + ofToString(myData->c, 2) + "\n   "  + ofToString(myData->d, 2) + "\n   ", myData->a, myData->b + 30);
		}
	}
	
	
	// release the data and set pointer to NULL - GOOD
	void releaseData() {
		printf("User::releaseData() - GOOD\n");
		if(myData) myData->release();
		myData = NULL;
	}
	
	
	// delete the data and set pointer to NULL - BAD
	void deleteData() {
		printf("User::deleteData() - BAD\n");
		if(myData) delete myData;
		myData = NULL;
	}
	
};
