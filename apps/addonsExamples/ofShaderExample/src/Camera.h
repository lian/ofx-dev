// a lot of this camera class is adapted from the ofCamera class which can be found here:
// http://www.openframeworks.cc/forum/viewtopic.php?t=363&highlight=ofcamera
 
#ifndef CAMERA_H
#define CAMERA_H

#include "ofMain.h"
#include "ofShader.h"
#include "ofxVec3f.h"

class Camera{
private:
	float	fieldOfView;
	float	yon;
	float	hither;
	
	int	w; 
	int	h; 
	float	aspectRatio;
	
	float k, damp;
	
	ofxVec3f acel, vel;
	
public:
	ofxVec3f pos, eye, up;
	ofxVec3f * center;
	float rotY;
	float radius;
	float step;

	Camera();
	~Camera();
	
	void goTo(ofxVec3f target);
	
	void move();
	
	void place();
	
	
	
};

#endif

