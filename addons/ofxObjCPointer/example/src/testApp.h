#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "MyObject.h"
#include "DataUser.h"

#define NUM_USERS	6

class testApp : public ofSimpleApp{
	
public:
	
	DataUser user[NUM_USERS];
	
	void setup();
	void draw();
	void keyPressed(int key);
};

#endif

