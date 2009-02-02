

#include "Worm.h"
using namespace std;

Worm::Worm(ofxVec3f iniPos, Perlin *_noise){
	noise = _noise;
	fat = ofRandom(0.8f, 1.3f);
	numDisks = (int)ofRandom(10, 50);
	for(int i=0; i<numDisks; i++){
		float angle = (float)i/(numDisks-1) * PI;
		float radius = i*fat * sin(angle) * (sin(angle + HALF_PI)+1)/2;
		if(radius == 0) radius = 0.1;
		disk.push_back(Disk(iniPos, radius));
	}
	
	ofxVec3f colorVec = ofxVec3f(0, 0, 0.8);
	float rotX = ofRandom(0, 360);
	float rotY = ofRandom(0, 360);
	colorVec.rotate(rotX, rotY, 0.0f);
	color[0] = colorVec.x;
	color[1] = colorVec.y;
	color[2] = colorVec.z;
	for(int i=0; i<3; i++){
		if(color[i]<0.0f) color[i] *= -1;
	}
	/*
	//float colorBW = ofRandom(0.5, 0.8);
	float colorBW = ofRandom(0.7f, 1.0f);
	for(int i=0; i<3; i++){
		color[i] = colorBW; 
	}*/

}

void Worm::move(){
	
	//this part here, where perlin noise is used to get the angles find a rotating velocity vector is adapted from a robert hodgin source
	//which can be found here: http://www.flight404.com/blog/?p=113 
	float step = 5;
	int div = 4000;
	int mult = 5;
	
	float radXZ = noise->Get(disk[0].center.x/div, disk[0].center.z/div)*TWO_PI;
	float radY = noise->Get(disk[0].center.x/div, disk[0].center.y/div)*TWO_PI;
	
	ofxVec3f perlinVec = ofxVec3f(cos(radXZ)*mult, cos(radY)*mult, sin(radXZ)*mult);
	ofxVec3f randomVec = ofxVec3f(ofRandom(-step, step), ofRandom(-step, step), ofRandom(-step, step));
	
	ofxVec3f target = disk[0].center + perlinVec + randomVec;
	
	disk[0].move(target, 0, 0);
	for(int i=1; i<numDisks; i++){
		//this bit of code here, to find the angles that each disk shoudl rotate, is taken from here
		// http://processing.org/discourse/yabb_beta/YaBB.cgi?board=Programs;action=display;num=1170790832
		float deltaX = disk[i].center.x - disk[i-1].center.x;
		float deltaY = disk[i].center.y - disk[i-1].center.y;
		float deltaZ = disk[i].center.z - disk[i-1].center.z;
		
		float rotY = atan2(deltaY ,deltaX);
		float hyp = sqrt(deltaX*deltaX + deltaY*deltaY);
		float rotX = atan2(hyp, deltaZ);
		
		disk[i].move(disk[i-1].center, rotX, rotY);
	}
}

void Worm::render(){
	glColor4f(color[0], color[1], color[2], 1.0f);
	for(int i=0; i<numDisks-1; i++){
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<NUMP-1; j++){
	
			//cheating my way through normals...
			ofxVec3f normalVec = disk[i].p[j] - disk[i].center;
			normalVec.normalize();
			glNormal3f(normalVec.x, normalVec.y, normalVec.z);
			glVertex3f(disk[i].p[j].x, disk[i].p[j].y, disk[i].p[j].z);
			
			//and again...
			normalVec = disk[i+1].p[j] - disk[i+1].center;
			normalVec.normalize();
			glNormal3f(normalVec.x, normalVec.y, normalVec.z);
			glVertex3f(disk[i+1].p[j].x, disk[i+1].p[j].y, disk[i+1].p[j].z);
		}
		glEnd();
	}
}


void Worm::renderContours(){
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	for(int i=0; i<NUMP; i++){
		glBegin(GL_LINE_STRIP);
		for(int j=0; j<numDisks; j++){
			glVertex3f(disk[j].contourP[i].x, disk[j].contourP[i].y, disk[j].contourP[i].z);
		}
		glEnd();
	}
	
	for(int i=0; i<numDisks; i++){
		glBegin(GL_LINE_STRIP);
		for(int j=0; j<NUMP; j++){
			glVertex3f(disk[i].contourP[j].x, disk[i].contourP[j].y, disk[i].contourP[j].z);
		}
		glEnd();
	}
}

void Worm::dontGoTooFar(ofxVec3f midPt){
	float k = 0.008;
	disk[0].accel = (midPt - disk[0].center) * k;
	disk[0].vel += disk[0].accel;
	disk[0].center += disk[0].vel;
}

void Worm::renderNormals(){
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_LINES);
	for(int i=0; i<numDisks-1; i++){
		for(int j=0; j<NUMP; j++){
		int nextP = (j+1) % NUMP;
		
			ofxVec3f vecA = ofxVec3f(disk[i].p[j].x, disk[i].p[j].y, disk[i].p[j].z) - ofxVec3f(disk[i+1].p[j].x, disk[i+1].p[j].y, disk[i+1].p[j].z);
			ofxVec3f vecB = ofxVec3f(disk[i+1].p[j].x, disk[i+1].p[j].y, disk[i+1].p[j].z) - ofxVec3f(disk[i+1].p[nextP].x, disk[i+1].p[nextP].y, disk[i+1].p[nextP].z);
			ofxVec3f normalVec = vecA.cross(vecB);
			normalVec.normalize();
			normalVec *= 20;
			normalVec += disk[i].p[j];
			// ofCircle(normalVec.x, normalVec.y, normalVec.z, 2);
			// ofCircle(normalVec.x, normalVec.y, normalVec.z);
			ofCircle(normalVec.x, normalVec.y, 2);
			glBegin(GL_LINES);
			glVertex3f(normalVec.x, normalVec.y, normalVec.z);
			glVertex3f(disk[i].p[j].x, disk[i].p[j].y, disk[i].p[j].z);
			glEnd();
		}
	}
	
}
