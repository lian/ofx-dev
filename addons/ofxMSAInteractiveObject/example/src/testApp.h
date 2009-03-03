#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "MyTestObject.h"

class testApp : public ofSimpleApp{
	
public:
	
	MyTestObject obj;
	void setup();
};

#endif

