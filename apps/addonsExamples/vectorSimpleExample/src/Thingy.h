#ifndef _THINGY
#define _THINGY

#include "ofMain.h"

struct Dimensions {
	float x, y;
};

class Thingy {

private:
	
public:
	
	// constructors
	Thingy();
	Thingy(float _x, float _y);
	// destructor
	~Thingy();
	// copy constructor
	Thingy(const Thingy &thingy);
	
	// methods
	void setup();
	void setup(float _x, float _y);
	void setup(float _x, float _y, float _size);
	void update();
	void draw();
	bool mousePressed(float _x, float _y);
	
	// properties
	Dimensions pos;
	Dimensions speed;
	float radius;

};

#endif