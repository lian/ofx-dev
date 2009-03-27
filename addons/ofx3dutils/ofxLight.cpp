

#include "ofxLight.h"


ofxLight::ofxLight(){
	bool anyLight = false;
	for(int i=0; i<8; i++){ 
		if(!(bool)glIsEnabled(GL_LIGHT0 +i)){ 
			lightEnum = GL_LIGHT0 + i;
			lightNum = i;
			anyLight = true;
			break;
		}
	}
	
	if(!anyLight){
		std::cout << "error creating light, maybe you're exceding the maximum 8 lights allowed?" << std::endl;
		return;
	}

	ambient(0, 0, 0);
	diffuse(0, 0, 0);
	specular(0, 0, 0);
	
	on();
	if(!(bool)glIsEnabled(GL_LIGHTING)){
		ofxLightsOn();
	}
	
	isSpot = false;
}

//on/off
void ofxLight::on(){
	glEnable(lightEnum);
}

void ofxLight::off(){
	glDisable(lightEnum);
}


//light types
void ofxLight::pointLight(float _r, float _g, float _b, float _x, float _y, float _z){
	diffuse(_r, _g, _b);
	position(_x, _y, _z);
	
	if(isSpot){
		spotCutOff(180);
	}
}

void ofxLight::spotLight(float _r, float _g, float _b, 
				   float _x, float _y, float _z, 
				   float _nx, float _ny, float _nz, 
				   float _angle, float _concentration){
	diffuse(_r, _g, _b);
	position(_x, _y, _z);
	spotDirection(_nx, _ny, _nz);
	spotCutOff(_angle);
	spotConcentration(_concentration);
	isSpot = true;
}

void ofxLight::directionalLight(float _r, float _g, float _b, float _nx, float _ny, float _nz){
	diffuse(_r, _g, _b);
	GLfloat justDirection[] = {-_nx, -_ny, _nz, 0.0f}; 
	glLightfv(lightEnum, GL_POSITION, justDirection);
}


//light components
void ofxLight::ambient(float _r, float _g, float _b){
	_r/=255.0f;
	_g/=255.0f;
	_b/=255.0f;
	
	GLfloat ambientLight[4] = {_r, _g, _b, 1.0f};
	glLightfv(lightEnum, GL_AMBIENT, ambientLight);
}

void ofxLight::specular(float _r, float _g, float _b){
	_r/=255.0f;
	_g/=255.0f;
	_b/=255.0f;
	
	GLfloat specularLight[4] = {_r, _g, _b, 1.0f};
	glLightfv(lightEnum, GL_SPECULAR, specularLight);
}

void ofxLight::diffuse(float _r, float _g, float _b){
	_r/=255.0f;
	_g/=255.0f;
	_b/=255.0f;
	
	GLfloat diffuseLight[4] = {_r, _g, _b, 1.0f};
	glLightfv(lightEnum, GL_DIFFUSE, diffuseLight);
}

void ofxLight::position(float _x, float _y, float _z){
	GLfloat positionLight[] = {_x, _y, _z, 1.0f};
	glLightfv(lightEnum, GL_POSITION, positionLight);
}

void ofxLight::attenuation(float _constant, float _linear, float _quadratic){
	glLightfv(lightEnum, GL_CONSTANT_ATTENUATION, &_constant);
	glLightfv(lightEnum, GL_LINEAR_ATTENUATION, &_linear);
	glLightfv(lightEnum, GL_QUADRATIC_ATTENUATION, &_quadratic);
}

//protected stuff
void ofxLight::spotDirection(float _nx, float _ny, float _nz){
	GLfloat spotDirectionArray[] = {_nx, _ny, _nz, 1.0f};
	glLightfv(lightEnum, GL_SPOT_DIRECTION, spotDirectionArray);
}

void ofxLight::spotCutOff(float _angle){
	if(_angle != 180){
		_angle = MIN(90, _angle);
	}
	glLightfv(lightEnum, GL_SPOT_CUTOFF, &_angle);
}

void ofxLight::spotConcentration(float _concentration){
	_concentration = MIN(128, _concentration);
	glLightfv(lightEnum, GL_SPOT_EXPONENT, &_concentration);
}



//smoooooth
void ofxSetSmoothLight(bool mode){
	if(mode){
		glShadeModel(GL_SMOOTH);
	}else {
		glShadeModel(GL_FLAT);
	}
}

//on/off
void ofxLightsOn(){
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void ofxLightsOff(){
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

//---------------------------------------

//material components
void ofxMaterialSpecular(float _r, float _g, float _b){
	_r/=255.0f;
	_g/=255.0f;
	_b/=255.0f;
	
	GLfloat materialSpecularArray[] = {_r, _g, _b};
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularArray); 
}

void ofxMaterialEmission(float _r, float _g, float _b){
	_r/=255.0f;
	_g/=255.0f;
	_b/=255.0f;
	
	 GLfloat materialEmissionArray[] = {_r, _g, _b};
	 glMaterialfv(GL_FRONT, GL_EMISSION, materialEmissionArray); 
}

void ofxMaterialShininess(float _degrees){
	_degrees = MIN(128, _degrees);
	 glMaterialfv(GL_FRONT, GL_SHININESS, &_degrees); 
}


//normal calculation
void ofxCalcNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){
	
	float vec1X = x2-x1;
	float vec1Y = y2-y1;
	float vec1Z = z2-z1;
	
	float vec2X = x3-x2;
	float vec2Y = y3-y2;
	float vec2Z = z3-z2;
	
	float crossX = vec1Y*vec2Z - vec1Z*vec2Y;
	float crossY = vec1Z*vec2X - vec1X*vec2Z;
	float crossZ = vec1X*vec2Y - vec1Y*vec2X;
	
	float dist = sqrt(crossX*crossX + crossY*crossY + crossZ*crossZ);
	
	glNormal3f(crossX/dist, crossY/dist, crossZ/dist);
}






