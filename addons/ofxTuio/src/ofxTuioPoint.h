/*
	TUIO C++ Library for OpenFrameworks
    http://www.openframeworks.cc
	
	Copyright (c) 2008 by Matthias Dörfelt based on the Classes by Martin Kaltenbrunner
	which can be found at http://reactivision.sourceforge.net/
	
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _TUIO_POINT
#define _TUIO_POINT

//--------------------------------------------------------
class ofxTuioPoint{
	
public:
	
	ofxTuioPoint(float _xpos, float _ypos){
		xpos = _xpos;
		ypos = _ypos;
	};
	
	ofxTuioPoint(ofxTuioPoint * _tuioPoint){
		xpos = _tuioPoint->getX();
		ypos = _tuioPoint->getY();
	};
	
	~ofxTuioPoint(){};
	
	void update (float _xpos, float _ypos) {
		xpos = _xpos;
		ypos = _ypos;
	};
	
	void update (ofxTuioPoint * _tuioPoint) {
	    xpos = _tuioPoint->getX();
		ypos = _tuioPoint->getY();
	};
	
	float getX(){
		return xpos;
	};
	
	float getY(){
		return ypos;
	};
	
	float getDistance(float _x, float _y) {
		float dx = xpos-_x;
		float dy = ypos-_y;
		return sqrtf(dx*dx+dy*dy);
	};
	
	float getDistance(ofxTuioPoint * _tuioPoint) {
		float dx = xpos-_tuioPoint->getX();
		float dy = ypos-_tuioPoint->getY();
		return sqrtf(dx*dx+dy*dy);
	};
	
	float getAngle(ofxTuioPoint * _tuioPoint) {
		
		float side = _tuioPoint->getX()-xpos;
		float height = _tuioPoint->getY()-ypos;
		float distance = _tuioPoint->getDistance(xpos,ypos);
		
		float angle = (float)(asin(side/distance)+PI/2);
		if (height<0) angle = 2.0f*(float)PI-angle;
		
		return angle;
	};
	
	float getAngleDegrees(ofxTuioPoint * _tuioPoint) {
		return ((getAngle(_tuioPoint)/(float)PI)*180.0f);
	};

	
protected:
	float xpos, ypos;
};

#endif	
