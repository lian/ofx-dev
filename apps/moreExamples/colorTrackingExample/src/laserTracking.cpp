#include "laserTracking.h"

laserTracking::laserTracking(){
}


void laserTracking::calcColorRange(float hue, float hueThresh, float sat, float satThresh, float value){
	
	//ehh this is kind of ugly and needs to be fixed I think
	//Lets calc the rgb values for the min and max hue range			
	float rgb[3];
	float hsb[3];
	
	hsb[0] = hue-hueThresh*0.5;
	hsb[1] = sat-satThresh*0.5;
	hsb[2] = value;
	
	hsbToRgb(hsb, rgb);
	
	r0Min = (int)(rgb[0]*255);
	g0Min = (int)(rgb[1]*255);
	b0Min = (int)(rgb[2]*255);
	
	hsb[0] = hue + hueThresh * 0.5;
	hsb[1] = sat + satThresh * 0.5;
	hsb[2] = value;
			
	hsbToRgb(hsb, rgb);
						
	r0Max = (int)(rgb[0]*255);
	g0Max = (int)(rgb[1]*255);
	b0Max = (int)(rgb[2]*255);
	
	hsb[0] = hue-hueThresh*0.5;
	if(sat == 0) hsb[1] = 0.0;
	else hsb[1] = 1.0;			
	hsb[2] = 1.0;
	
	hsbToRgb(hsb, rgb);
	
	r1Min = (int)(rgb[0]*255);
	g1Min = (int)(rgb[1]*255);
	b1Min = (int)(rgb[2]*255);
	
	hsb[0] = hue+hueThresh*0.5;
	if(sat == 0) hsb[1] = 0.0;
	else hsb[1] = 1.0;	
	hsb[2] = 1.0;
			
	hsbToRgb(hsb, rgb);
						
	r1Max = (int)(rgb[0]*255);
	g1Max = (int)(rgb[1]*255);
	b1Max = (int)(rgb[2]*255);
}

//---------------------------		
void laserTracking::drawColorRange(float x, float y, float w, float h){

	//this is not super accurate
	//but good for an indication
	glBegin(GL_QUADS);
		ofSetColor(r1Min, g1Min, b1Min);
		glVertex2f(x,  y);
		
		ofSetColor(r1Max, g1Max, b1Max);				
		glVertex2f(x+w, y);
		
		ofSetColor(r0Max, g0Max, b0Max);
		glVertex2f(x+w, y + h );

		ofSetColor(r0Min, g0Min, b0Min);
		glVertex2f(x, y + h);
	glEnd();

}
