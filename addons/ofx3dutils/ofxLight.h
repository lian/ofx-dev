#pragma once

#include "ofMain.h"

class ofxLight{
	
public:
	int lightNum;
	
	ofxLight();
	
	void on(); 
	void off();
	
	
	////////////////////////////////types of light
	//these can be used to make simple lights.
	//point light has an origin and emittes light in all directions.
	void pointLight(float _r, float _g, float _b, float _x, float _y, float _z);
	
	//spot light has an origin and is emmiting in a direction. 
	//_nx, _ny and _nz are a normal vector determining the direction of the light.
	//angle determines how open the light  cone is, and concentration determines how focused the light is in the midle of that cone
	void spotLight(float _r, float _g, float _b, 
				   float _x, float _y, float _z, 
				   float _nx, float _ny, float _nz, 
				   float _angle,  //must be between 0 and 90
				   float _concentration); //must be a value between 0 and 128
				   
	//direction light has no determined source, but has direction 
	void directionalLight(float _r, float _g, float _b, float _nx, float _ny, float _nz);
	
	
	////////////////////////////////light properties:
	//these can be used to to control each light component individually to create more complex lights 
	void position(float _x, float _y, float _z); //self explained ;)
	void ambient(float _r, float _g, float _b); //this basically tints everything with its color, by default is 0,0,0.
	void specular(float _r, float _g, float _b); //light that reflects off objects (used to create reflexions), by default is 0,0,0,
	void diffuse(float _r, float _g, float _b); //light that comes from an origin point, and hits the surface at an angle, by default is 128, 128, 128.
	
	void attenuation(float _constant, float _linear, float quadratic); //this will attenuate the intensity of the light according to the distance.
	// the formula to calculate this is attenuation = 1/(constant + linear*d + quadratic*d²), where d is the distance to the vertice.
	// values must be between 0 and 1.
	
protected:
	GLenum lightEnum;
	bool isSpot;
	//properties related to creating spotlights
	void spotDirection(float _nx, float _ny, float _nz);
	void spotCutOff(float _angle);
	void spotConcentration(float _concentration);
	 
};


//some general stuff
void ofxLightsOn();
void ofxLightsOff();
void ofxSetSmoothLight(bool mode);


//---------------------------------------------


////////////////////////////////material properties

//material's Ambient and Diffuse are already controled by glColor**() or by ofSetColor(), so no need
//to include them here... 
void ofxMaterialSpecular(float _r, float _g, float _b);//how much of the light Specular will be reflected by the object.
void ofxMaterialEmission(float _r, float _g, float _b);//light being emitted by the object
//material shininess determines how concentrated the light being reflected will be (uses the specular values of the light)
void ofxMaterialShininess(float _degrees); //between 0 and 128

////////////////////////////////calculate normal
//to draw lights, opengl needs to know the normal of each face forming the shape. this function takes the coordinates
//of 3 points and calculates the normal of the triangle formed by those points.
//it also calls the correspondent glNormal3f() comand so it should be placed between your glBegin(...) and glEnd() before calling the vertices.
//something like this:
/*
glBegin(...);
ofxCalcNormal(p1X, p1Y, p1Z, p2X, p2Y, p2Z, p3X, p3Y, p3Z);
glVertex3f(p1X, p1Y, p1Z);
glVertex3f(p2X, p2Y, p2Z);
glVertex3f(p3X, p3Y, p3Z);
ofxCalcNormal(...next points...)
glVertex3f(......)
glVertex3f(......)
glVertex3f(......)
... and so on...
glEnd();
*/
//its a pain, but at least with this function its slightly less painfull...
void ofxCalcNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3); 






