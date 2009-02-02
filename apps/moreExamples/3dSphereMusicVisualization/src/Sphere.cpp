

#include "Sphere.h"
using namespace std;

Sphere::Sphere(){
	rotX = rotY = 0;
	radius = 190;
	for(int i=0; i<SphereNumRows; i++){
		v = (float)i/(SphereNumRows-1);
		phi = acos(2*v-1);
		for(int j=0; j<SphereNumLines; j++){
			u = (float)j/(SphereNumLines-1);
			theta = TWO_PI * u;
			p[i][j].pos.x =  (cos(theta)*sin(phi)*radius);
			p[i][j].pos.y = (sin(theta)*sin(phi)*radius);
			p[i][j].pos.z =  (cos(phi)*radius);
			p[i][j].radius = radius;
			p[i][j].band = (int)ofRandom(0, NumBands);
			p[i][j].theta = theta;
			p[i][j].phi = phi;
			p[i][j].currentRadius = 0;
		}
	}
}

Sphere::~Sphere(){}

void Sphere::move(){
rotX += 2;
rotY += 1;
	ofxVec3f target;
	for(int i=0; i<SphereNumRows; i++){
		for(int j=0; j<SphereNumLines; j++){
			target.x =  (cos(p[i][j].theta) * sin(p[i][j].phi) * p[i][j].radius);
			target.y = (sin(p[i][j].theta) * sin(p[i][j].phi) * p[i][j].radius);
			target.z =  (cos(p[i][j].phi) * p[i][j].radius);
			p[i][j].move(target);
		}
	}
}

void Sphere::render(){
	ofxVec3f dif;
	for(int i=0; i<SphereNumRows; i++){
		int next = (i+1)%SphereNumRows;
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<SphereNumLines; j++){
		ofSetColor(150, 150, 10, p[i][j].alphaVal);
			glVertex3f(p[i][j].pos.x, p[i][j].pos.y, p[i][j].pos.z);
			glVertex3f(p[next][j].pos.x, p[next][j].pos.y, p[next][j].pos.z);
		}
		glEnd();
	}
}









	
	
	
	
	
	
	