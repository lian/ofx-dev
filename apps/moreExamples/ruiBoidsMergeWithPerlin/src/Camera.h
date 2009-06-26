// a lot of this camera class is adapted from the ofCamera class which can be found here:
// http://www.openframeworks.cc/forum/viewtopic.php?t=363&highlight=ofcamera
 
 #ifndef CAMERA_H
 #define CAMERA_H

#include "ofMain.h"
class Camera{
private:
	float	fieldOfView;
	float	yon;
	float	hither;
	
	int	w; 
	int	h; 
	float	aspectRatio;
	
	float k, damp, ax, ay, az, vx, vy, vz;
	
public:
	float camX, camY, camZ, eyeX, eyeY, eyeZ, upX, upY, upZ;

	Camera();
	~Camera();
	
	void goTo(float _x, float _y, float _z);
	
	void place();
	
	
	
};
#endif

