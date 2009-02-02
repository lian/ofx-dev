
#include "Particles.h"
using namespace std;

Particles::Particles(ofxVec3f iniPos, ofxVec3f _vel, Perlin *_noise, int _type=0){
	pos = iniPos;
	vel = _vel;
	noise = _noise;
	life = (int)ofRandom(20, 50);
	iniLife = life;
	size = ofRandom(4, 8);
	type = _type;

	ofxVec3f colorVec = ofxVec3f(0,0,250);
	colorVec.rotate(ofRandom(0, 360), ofRandom(0, 360), 0);

	color[0] = abs((int)colorVec.x);
	color[1] = abs((int)colorVec.y);
	color[2] = abs((int)colorVec.z);
	
	G = -ofRandom(3, 6);
	
	for(int i=0; i<NumP; i++){
		pontos[i] = Ponto(iniPos);
	}
	
	doTail = false;
}

Particles::~Particles(){}

void Particles::move(){
float damp = 0.5;
	life--;
	int step = 2;
	int mult = 5;
	int div = 4000;
	
	float radXZ = noise->Get(pos.x/div, pos.z/div)* TWO_PI;
	float radY = noise->Get(pos.x/div, pos.y/div)*TWO_PI;
	
	acel.x = cos(radXZ)*mult+ofRandom(-step, step);
	acel.y = -sin(radY)*mult+ofRandom(-step, step);
	acel.z = sin(radXZ)*mult+ofRandom(-step, step);
	
	vel += acel;
	vel.y += G;
	vel *= damp;
	
	pos += vel;
	
	if (doTail)		moveTrail();
}

void Particles::render(){
	float scale =  (float)life/iniLife;
	ofSetColor(color[0],color[1], color[2]);
	// float curTime = ofGetFrameNum() * 1.0f/60.0f;

	ofTranslate(0, 0, pos.z);	
	if (type == 0) {
		ofCircle(pos.x, pos.y, (size*scale)*2);
	   // ofCircle(pos.x, pos.y, pos.z, size*scale);
	} else if (type == 1) {
		ofCube((size*scale)*4, pos.x, pos.y);
	} else if (type == 2) {
		ofSphere((size*scale)*4, pos.x, pos.y, 5);
	}
	ofTranslate(0, 0, -pos.z);
    
	if (doTail) {
		ofSetColor(color[0],color[1], color[2], 40);
		renderTrail();		
	}
	
}

void Particles::moveTrail(){
	pontos[0].pos = pos;
	for(int i=1; i<NumP; i++){
		pontos[i].ang = atan2(pontos[i-1].pos.y - pontos[i].pos.y, pontos[i-1].pos.x + pontos[i].pos.x);
		pontos[i].move(pontos[i-1].pos);
	}
}

void Particles::renderTrail(){
	glBegin(GL_QUAD_STRIP);
	float scale = ((float)life)/iniLife;
	float actualSize = size * scale;
	for(int i=0; i<NumP; i++){
		float normalI = 1-((float)i)/(NumP-1);
		
		float offSetX = cos(pontos[i].ang)*actualSize*normalI;
		float offSetY = sin(pontos[i].ang)*actualSize*normalI; 
		
		glVertex3f(pontos[i].pos.x + offSetX, pontos[i].pos.y + offSetY, pontos[i].pos.z);
		glVertex3f(pontos[i].pos.x - offSetX, pontos[i].pos.y - offSetY, pontos[i].pos.z);
	}
	glEnd();
}