/*
 *  ofxFiducial.h
 *  openFrameworks
 *
 *  Created by Alain Ramos a.k.a. ding
 *  Copyright 2008 Alain Ramos.
 *
 *
 For Free you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 */
//	----------------------------------------------------------------------------------------------------

#ifndef OF_X_FIDUCIAL_H
#define OF_X_FIDUCIAL_H

#include "ofMain.h"
#include "libfidtrack/fidtrackX.h"

#define INVALID_ID     (-1)

#define FIDUCIAL_LOST 0
#define FIDUCIAL_FOUND 1
#define FIDUCIAL_INVALID 2
#define FIDUCIAL_WRONG 3
#define FIDUCIAL_REGION 4


//this is for storing x, y and angle 
//and to figure out speed and acceleration of position, rotation and angle
struct _frame {
 float xpos,ypos,angle;
 float rotation_speed, rotation_accel;
 float motion_speed, motion_accel;
 float motion_speed_x, motion_speed_y;
 int time;
 };

class ofxFiducial {
	
public:
	//public variables
	//****//--------------------------------------------------------------------------------------
	int		fidId; // fiducial id
	float	r_size, l_size; //root size and leaf size
	_frame	current, last; //current and last fid info
	bool	updateCorners; //do we want to auto update corners?
	vector	<ofPoint> cornerPoints;//vector to store corner points
	
	//Constructor
	//****//--------------------------------------------------------------------------------------
	ofxFiducial() {
		fidId			= INVALID_ID;
		current.xpos	= current.ypos = -100.0f;
		current.angle	= 0.0f;
		current.rotation_speed	= current.rotation_accel	= 0.0f;
		current.motion_speed	= current.motion_accel		= 0.0f;
		current.motion_speed_x	= current.motion_speed_y	= 0.0f; 
		alive			= true;
		cornersUpdated  = false;
		updated			= false;
		updateCorners	= false;
		life			= 3;
		current.time	= 0;
		cornerPoints.resize(4);
		saveLastFrame();
	}
	
	//getter functions
	//****//--------------------------------------------------------------------------------------
	int	  getId()		{ return fidId; }
	float getMSpeed()	{ return current.motion_speed; }
	float getMAccel()	{ return current.motion_accel; }
	float getMSpeedX()	{ return current.motion_speed_x; }
	float getMSpeedY()	{ return current.motion_speed_y; }
	float getX()		{ return current.xpos; }
	float getY()		{ return current.ypos; }
	float getAngle()	{ return TWO_PI - current.angle; } //radian (phi)
	float getAngleDeg()	{ return 360 - (current.angle * ( 180 / PI )); } //reversed to compensate for OF
	float getRSpeed()	{ return current.rotation_speed; }
	float getRAccel()	{ return current.rotation_accel; }
	float getRootSize()	{ return r_size; }
	bool  getCornerUpdateStatus() { return updateCorners; }
	void  setUpdateCorners(bool _update){ updateCorners	= _update; }
	
	
	//Update Fiducial
	//****//--------------------------------------------------------------------------------------
	void update(float _x, float _y, float _angle, float _root, float _leaf) {
		
		//this is to try and filter out some of the jitter
		//------------------------------------------------
		float jitterThreshold	= 1.0;
		
		//if new posit - current posit is less than threshold dont update it must be jitter 
		if ( fabs(_x - current.xpos) > jitterThreshold ) current.xpos = _x;
		else current.xpos = last.xpos;
		if ( fabs(_y - current.ypos) > jitterThreshold ) current.ypos = _y;
		else current.ypos = last.ypos;
		//if new angle - current angle is less than threshold/20 dont update it must be jitter
		if ( fabs(_angle - current.angle) > jitterThreshold/20 ) current.angle = _angle;
		else current.angle = last.angle;
		//------------------------------------------------
		
		current.time	= ofGetElapsedTimeMillis(); //get current time
		r_size			= _root; //update root size
		l_size			= _leaf; //update leaf size
		state			= FIDUCIAL_FOUND; //fiducial found
		updated			= true; //got updated
		
		computeSpeedAccel(); //compute speed & acceleration
		
		if ( updateCorners ) computeCorners(); //figures out the corners and fills the cornerPoints vector
		else cornersUpdated = false;
		saveLastFrame(); //last frame equal to this frame
	}
	
	//Check for Removal
	//this is done to make sure is survives for 2 frames if found missing
	//****//--------------------------------------------------------------------------------------
	bool isAlive() {
		//if not updated take care of some things
		if (!updated) {
			state			= FIDUCIAL_LOST;	//lable as lost
			current.time	= ofGetElapsedTimeMillis();
			current.xpos	= last.xpos;
			current.ypos	= last.ypos;
			current.angle	= last.angle;
			computeSpeedAccel();
			--life;					//if not updated subtract life
		}
		
		if (!life) alive = false;	//if life is gone alive is false ae. it is dead
		updated = false;			//reset updated message
		return alive;				//return life state
	}
	
	//computes the corners an fills the cornerPoints vector
	//****//--------------------------------------------------------------------------------------
	void computeCorners() {
		
		//**here is the order//
			//0+______+1//
			// |      | //
			// |      | //
			//3+______+2//
		
		//clear vector
		cornerPoints.clear();
		//get upper left corner
		float upperLeftCornerX	= current.xpos - (r_size/2);
		float upperLeftCornerY	= current.ypos - (r_size/2);
		//				this is half the width ---- ^^^^
		//get the hypotenuse
		float hyp = getDistance(upperLeftCornerX, upperLeftCornerY);
		//get the current angle in radian
		//must add pi to the radian to compensate for OF fliped cartesian coordinates
		float rad = getAngle() + PI;
		//the point we are going to use
		ofPoint addPoint;
		//this formula finds a point in the circumfrence of a circle
		//point.x = hypotenuse * cos(radian)
		//point.y = hypotenuse * sin(radian)
		
		//*corner degrees*/
		//UR = 45
		//UL = 135
		//LL = 225
		//LR = 315
		//http://en.wikipedia.org/wiki/Unit_circle
		
		//upper left
		addPoint.set((hyp * cos(rad + radians(135))) + current.xpos,
					(hyp * sin(rad + radians(135))) + current.ypos);
		cornerPoints.push_back(addPoint);
		//upper right
		addPoint.set((hyp * cos(rad +  radians(45))) + current.xpos,
					(hyp * sin(rad +  radians(45))) + current.ypos);
		cornerPoints.push_back(addPoint);
		//lower right
		addPoint.set((hyp * cos(rad + radians(315))) + current.xpos,
					(hyp * sin(rad + radians(315))) + current.ypos);
		cornerPoints.push_back(addPoint);
		//lower left
		addPoint.set((hyp * cos(rad + radians(225))) + current.xpos,
					(hyp * sin(rad + radians(225))) + current.ypos);
		cornerPoints.push_back(addPoint);
		
		cornersUpdated = true;
		}	
	
	//is a point inside this fiducial
	//http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
	//****//--------------------------------------------------------------------------------------
	bool isPointInside(float _x, float _y) {
		
		if ( !cornersUpdated ) computeCorners();
		
 		int counter = 0; 
 		int i; 
 		double xinters; 
 		ofPoint p1,p2;

 		p1 = cornerPoints[0]; 
 		for (i=1;i<=4;i++) { 
			p2 = cornerPoints[i % 4]; 
			if (_y > MIN(p1.y,p2.y)) { 
				if (_y <= MAX(p1.y,p2.y)) { 
					if (_x <= MAX(p1.x,p2.x)) { 
						if (p1.y != p2.y) { 
							xinters = (_y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x; 
							if (p1.x == p2.x || _x <= xinters) 
								counter++; 
							} 
						} 
					} 
				} 
				p1 = p2; 
			} 

		 	if (counter % 2 == 0) return false; 
 			else return true; 
	}
	
	// Returns true if this fiducial collided with an other fiducial.
	//****//--------------------------------------------------------------------------------------
	bool isFidCollided(ofxFiducial& fiducial_2) {
		
		//make sure corners are up to date
		fiducial_2.computeCorners();
		
		int counter = 0;
		bool inside = false;
		//check to make sure none of that fiducials points are inside this fiducial
		for(int i = 0; i < 4 ;i++) {
			if ( isPointInside(fiducial_2.cornerPoints[i].x, fiducial_2.cornerPoints[i].y) ) counter++;
		}
		//if we found a point its inside of us
		if (counter > 0) inside = true;
		//check to make sure none of this fiducials points are inside that fiducial
		for(int i = 0; i < 4 ;i++) {
			if ( fiducial_2.isPointInside(cornerPoints[i].x, cornerPoints[i].y) ) counter++;
		}
		//if we found a point we are inside of it
		if (counter > 0) inside = true;
		//return result
		return inside;
	}
	
	// returns the distance to this fiducials current position
	//****//--------------------------------------------------------------------------------------
	float getDistance(float _x, float _y) {
		
		float dx = _x - current.xpos;
		float dy = _y - current.ypos;
		return sqrt(dx*dx+dy*dy);
	}	
	
	
	//Operator overloading for FiducialX & ofxFiducial
	//****//--------------------------------------------------------------------------------------
	void operator=( const FiducialX& fiducial) {
		fidId			= fiducial.id;
		current.xpos	= fiducial.x;
		current.ypos	= fiducial.y;
		current.angle	= fiducial.angle;
		r_size			= fiducial.root_size;
		l_size			= fiducial.leaf_size;
		current.time	= ofGetElapsedTimeMillis();
	}
	
	void operator=( const ofxFiducial& fiducial) {
		fidId			= fiducial.fidId;
		current.xpos	= fiducial.current.xpos;
		current.ypos	= fiducial.current.ypos;
		current.angle	= fiducial.current.angle;
		r_size			= fiducial.r_size;
		l_size			= fiducial.l_size;
		current.time	= fiducial.current.time;
	}
	
	//draw fiducial
	//****//--------------------------------------------------------------------------------------
	void draw( float _x, float _y ) {
		ofNoFill();
		ofSetRectMode(OF_RECTMODE_CENTER);
		glPushMatrix();
		glTranslatef(current.xpos + _x, current.ypos + _y, 0);
		float deg = degrees(getAngle()); // get degree
		glRotatef(deg, 0, 0, 1.0); // must flip degrees to compensate for image flip
		ofSetColor(255, 0, 0);//set color red
		ofRect(0, 0, r_size, r_size); //draw root size red
		ofSetColor(0, 0, 255); //set color blue
		ofCircle(0, l_size*4, l_size); //draw leaf size blue
		ofSetColor(0, 255, 0); //set color green
		ofDrawBitmapString(ofToString( fidId ), 0, 0); //draw fiducial number green
		glPopMatrix();
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofSetColor(255,255,255);
	}
	
	//draw corners
	//****//--------------------------------------------------------------------------------------
	void drawCorners( float _x, float _y ) {
		if ( !cornersUpdated ) computeCorners();
		ofSetColor(0, 255, 0);
		ofNoFill();
		glPushMatrix();
		glTranslatef(_x, _y, 0);
		if (cornerPoints.size() > 0) {
			for(int i = 0; i < cornerPoints.size() ;i++) {
				ofCircle(cornerPoints[i].x, cornerPoints[i].y, 4);
				////printf("corner 0.x: %f corner 0.y %f\n", cornerPoints[i].x, cornerPoints[i].y);
				}
			}
		glPopMatrix();
		ofSetColor(255,255,255);
		//printf("corner 0.x: %f corner 0.y %f\n", cornerPoints[0].x, cornerPoints[0].y);
		}
		
	
	//private stuff
	//****//--------------------------------------------------------------------------------------
private:
	bool	alive; //can we remove fid from list
	bool	updated;// has fid been updated
	bool	cornersUpdated;
	int		life;//fids lifespan in frames
	int		state;//fids lost/found state
	
	// conversions from degree to radian and back
	float radians (float degrees) {
		return degrees*PI/180.0;
	}
	
	float degrees (float radians) {
		return radians*180.0/PI;
	}
	
	//compute speed, accel, etc...
	void computeSpeedAccel() {		
		if (last.time==0) return;
		
		int   dt	= current.time - last.time;
		float dx	= current.xpos - last.xpos;
		float dy	= current.ypos - last.ypos;
		float dist	= sqrt(dx*dx+dy*dy);
		
		current.motion_speed	= dist/dt;
		current.motion_speed_x	= fabs(dx/dt);
		current.motion_speed_y	= fabs(dy/dt);
		current.rotation_speed  = fabs(current.angle-last.angle)/dt;

		current.motion_accel	= (current.motion_speed-last.motion_speed)/dt;
		current.rotation_accel	= (current.rotation_speed-last.rotation_speed)/dt;		
	}
	
	//make last frame = this frame
	void saveLastFrame() {
		last.time	= current.time;
		last.xpos	= current.xpos;
		last.ypos	= current.ypos;
		last.angle	= current.angle;
		last.motion_speed	= current.motion_speed;
		last.rotation_speed = current.rotation_speed;
	}
	
};

#endif