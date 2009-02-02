

#include "ofx3D.h"
#include "ofMath.h"
//-------------------------------------------------------------- NOTES
/*

Alpha:
when calling a sphere or any shape you can use the ofEnable / disable alphaBlending
*/

//-------------------------------------------------------------- GLUT Nurb

void ofNurb() {
}


void ofInitNurb() {
}

void ofNurbCtrlPoints() {

}

void ofTeaPot(float d, float x, float y) {
	glPushMatrix();
		glTranslatef(x, y, 0.0);
		
		if(OF_POLY_MODE == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(OF_POLY_MODE == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if(OF_POLY_MODE == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		
		ofLightsOn();
		glutSolidTeapot(d);
		ofLightsOff();
		
		//Turn back to normal for 2d object
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	glPopMatrix();


}
//-------------------------------------------------------------- GLUT Cube
void ofCube(float d, float x, float y) {
	glPushMatrix();
		glTranslatef(x, y, 0.0);
		
		if(OF_POLY_MODE == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(OF_POLY_MODE == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if(OF_POLY_MODE == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		
		ofLightsOn();
		glutSolidCube(d);

		ofLightsOff();
		
		//Turn back to normal for 2d object
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	glPopMatrix();
}

//-------------------------------------------------------------- GLUT Sphere	
void ofSphere(float _r, float _x, float _y) {
	
	float res = 20;
		   
	glPushMatrix();
		glTranslatef(_x, _y, 0.0); 
		glColor3f(1.0, 0.0, 0.0);
		
		if(OF_POLY_MODE == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(OF_POLY_MODE == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if(OF_POLY_MODE == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		
		ofLightsOn();
		glutSolidSphere(_r, res, res);
		ofLightsOff();
		
		//Turn back to normal for 2d object
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	glPopMatrix();
	//drawsphere(3.0, 65.0);	
}

//-------------------------------------------------------------- GLUT Sphere	
void ofSphere(float _r, float _x, float _y, float _res) {

	glPushMatrix();
		glTranslatef(_x, _y, 0.0); 
		// glColor3f(1.0, 0.0, 0.0);
		
		if(OF_POLY_MODE == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(OF_POLY_MODE == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if(OF_POLY_MODE == 2) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		
		ofLightsOn();
		glColor3f(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
		glutSolidSphere(_r, _res, _res);
		ofLightsOff();
		
		//Turn back to normal for 2d object
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	glPopMatrix();
	//drawsphere(3.0, 65.0);	
}

//-------------------------------------------------------------- Fog
void ofFog() {
	glEnable(GL_FOG);
	GLfloat fogColor[4] = {0.3, 0.3, 0.3, 1.0};
	GLint fogMode = GL_EXP;
	glFogi(GL_FOG_MODE, fogMode);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 2.0);	
}

//-------------------------------------------------------------- Init lights

/*
This needs work LOTS of WORK!
*/

void ofInitLights() {		
	//glClearColor(0.0, 0.1, 0.1, 0.0);
	//glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	GLfloat mat_specular[]	 = { 1.0, 0.0, 1.0, 0.4 };
    GLfloat mat_shininess[]	 = { 61.0 };
    //GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST); 
	
	ofPositionLight();
	
  }

//-------------------------------------------------------------- Position Light
//float x, float y, float z, float w
void ofPositionLight(float x, float y, float z) {
	
	// (x, y, z, w)
	// w should be 1 || 0
	// 0, map(mousex, 0, 1024, 0.0, 1.0), 0, 1
	//static GLfloat light_position[] = { 0.0, 3.0, 2.0, 0.0 };

	light_position[0] = x; //x
	light_position[1] = y; //y
	light_position[2] = z; //z
	light_position[3] = 0; //w type of light 1 = direction light
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void ofPositionLight() {
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//-------------------------------------------------------------- on/off lights

void ofLightsOn() {
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void ofLightsOff() {
	glDisable(GL_LIGHTING);
}

//-------------------------------------------------------------- 3D Mode
// 0 = fill
// 1 = line
// 2 = points

void ofSet3DMode(int mode) {
	OF_POLY_MODE = mode;
}






