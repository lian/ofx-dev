/*
*
* this class is a testing class for the box2d system
* christopher baker <http://christopherbaker.net>
*
*/

#ifndef _TEST_WORLD
#define _TEST_WORLD

#define OF_ADDON_USING_OFXBOX2D

#include "ofMain.h"
#include "ofAddons.h"

class TestWorld {

	public:
		TestWorld();
		~TestWorld();
		
		void update();	// the update function
		void draw();	// the draw function
		
		void makeStage();	// makes the bounding stage
		void drawStage();  // draws the bounding stage
		
		void reverseGravity(); // a function to just change the gravity
		
		// world data
		b2World* world; // a pointer of type b2World 
		float32 timeStep; // box2D time step
		int32 iterations; // box2D iterations

		
		int numBodies;	// this is the number of bodies in play 
		b2Body* bodies[500]; // this is an array of pointers to those bodies
		
		// this is the single body that acts as a "container" for the action
		// it is defined and created in makeStage()
		// right now the static massless body has four attached shapes
		// that form four walls that border the screen.  they appear as red boxes
		 
		b2Body* stage;	// the body tat defines the "inner zone, you can't escape from"

		
		// this pointer to a gravity vector allows us to change gravity based on a keypress
		b2Vec2* gravity;
		
		// something to bounce off of
		b2Body* obstacle;
		
		
		// these two functions aloows us to move between 
		// box2D kg/m/s system of measurement and screen pixels
		// the exact conversion are done by either pixels_per_meter
		// or meters_per_pixel variables below
		
		
		float m2p(float meters);	// convert meters to pixels
		float p2m(float pixels);	// convert pixels to meters

		
	protected:
	
			float pixels_per_meter;	// pixels/meter
							// box2d works best with items
							// that are 0.1 -> 10 meters
							// so if the biggest item is 10 meters
							// then this should scale the screen width
							// to 10 meters
							// 
			float meters_per_pixel;

		


};

#endif

