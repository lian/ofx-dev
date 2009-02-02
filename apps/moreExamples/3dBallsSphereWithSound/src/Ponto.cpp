
#include "Ponto.h"

Ponto::Ponto(){
	pos = 0;
	vel = 0;
	acel = 0;
	k = 0.5;
	damp = 0.6;

}

Ponto::Ponto(ofxVec3f iniPos){
	pos = iniPos;
	acel = 0;
	vel = 0;
	k = 0.5;
	damp = 0.45;

}

void Ponto::move(ofxVec3f target){
	acel = (target - pos) * k;
	vel += acel;
	vel *= damp;
	pos += vel;
}
