

#ifndef _OF_BALL		// by using this if statement you prevent the class to be called more than once - in other words what we're saying here is 
#define _OF_BALL		//if the class has NOT been defined then define it

					
#include "ofMain.h"


class ofBall {


	  
   public:   

		// methods
		void add_velocity(float _x, float _y);
		void set_color(float _r, float _g, float _b) {
			r = _r;
			g = _g;
			b = _b;
		}
		void update();
		void draw();	  

		//constructor
		ofBall();

		// variables
		float x;
		float y;
		int dim;
		float speedX;
		float speedY;
		float r, g, b;
 
   
};		

#endif 