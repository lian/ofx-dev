#include "testApp.h"

// try commenting out the line below to see what it'll be like without using smart pointers
// as soon as you delete one instance, the data is lost
// and all other users of the data screwup

#define USE_SMART_POINTER


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(255, 255, 255);
	
	MyObject *tempData = new MyObject(20, 70, 100, 500);
	
	for(int i=0; i < NUM_USERS; i++) {
		user[i].setData(tempData);			// users' internal pointer points to the same data, and retains it
		user[i].index = i+1;				// just arbitrary unique data per user for display
	}
	tempData->release();			// data is released from tempData, but is still in memory because its being used by the users
}


//--------------------------------------------------------------
void testApp::draw(){
	glColor4f(0, 0, 0, 1);
	
#ifdef USE_SMART_POINTER	
	ofDrawBitmapString( " Press number keys 1-6 to destroy the objects. \n Even though they share data, the data remains until all objects have been destroyed.\n Check the console to see when the data is actually deleted.", 20, 20);
#else
	ofDrawBitmapString( " Press number keys 1-6 to destroy the objects. \n They share data, so when one is destroyed, all others go bonkers.", 20, 20);
#endif
	
	for(int i=0; i<NUM_USERS; i++) {
		user[i].displayData();
		glTranslatef(150, 0, 0);
	}
}


//--------------------------------------------------------------
void testApp::keyPressed (int key){ 
	int i = key - '0';
	if(i<1 || i>NUM_USERS) return;
	printf("Pressed key: %i\n", i);
	
#ifdef USE_SMART_POINTER
	user[i-1].releaseData();
#else 
	user[i-1].deleteData();
#endif	
}
