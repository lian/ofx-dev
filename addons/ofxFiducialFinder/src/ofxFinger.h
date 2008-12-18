
#ifndef OF_X_FINGER_H
#define OF_X_FINGER_H

#include "ofMain.h"
#include "libfidtrack/fidtrackX.h"

#define FINGER_LOST 0
#define FINGER_FOUND 1

//this is for storing x, y and angle 
//and to figure out speed and acceleration of position, rotation and angle
struct finger_frame {
	float xpos,ypos;
	float motion_speed, motion_accel;
	float motion_speed_x, motion_speed_y;
	int time;
};

class ofxFinger {
	
public:
	//public variables
	//****//--------------------------------------------------------------------------------------
	int fingerID;
	int area;
	short width, height;
	finger_frame	current, last; //current and last fid info
	
	//Constructor
	//****//--------------------------------------------------------------------------------------
	ofxFinger() {
		fingerID		= INVALID_ID;
		current.xpos	= current.ypos = -100.0f;
		current.motion_speed	= current.motion_accel		= 0.0f;
		current.motion_speed_x	= current.motion_speed_y	= 0.0f;
		area			= 0;
		alive			= true;
		updated			= false;
		life			= 1;
		current.time	= 0;
		saveLastFrame();
	}
	
	//getter functions
	//****//--------------------------------------------------------------------------------------
	int	  getId()		{ return fingerID; }
	float getMSpeed()	{ return current.motion_speed; }
	float getMAccel()	{ return current.motion_accel; }
	float getMSpeedX()	{ return current.motion_speed_x; }
	float getMSpeedY()	{ return current.motion_speed_y; }
	float getX()		{ return current.xpos; }
	float getY()		{ return current.ypos; }
	short getWidth()	{ return width; }
	short getHeight()	{ return height; }
	int	  getArea()		{ return area; }
	
	//Update Finger
	//****//--------------------------------------------------------------------------------------
	void update(float _x, float _y, short _width, short _height, int _area) {
		
		//this is to try and filter out some of the jitter
		//------------------------------------------------
		float jitterThreshold	= 1.0;
		
		//if new posit - current posit is less than threshold dont update it must be jitter 
		if ( fabs(_x - current.xpos) > jitterThreshold ) current.xpos = _x;
		else current.xpos = last.xpos;
		if ( fabs(_y - current.ypos) > jitterThreshold ) current.ypos = _y;
		else current.ypos = last.ypos;

		//------------------------------------------------
		
		width			= _width;
		height			= _height;
		area			= _area;
		current.time	= ofGetElapsedTimeMillis(); //get current time
		state			= FINGER_FOUND; //finger found
		updated			= true; //got updated
		
		computeSpeedAccel(); //compute speed & acceleration

		saveLastFrame(); //last frame equal to this frame
	}
	
	//Check for Removal
	//this is done to make sure is survives for 2 frames if found missing
	//****//--------------------------------------------------------------------------------------
	bool isAlive() {
		//if not updated take care of some things
		if (!updated) {
			state			= FINGER_LOST;	//lable as lost
			current.time	= ofGetElapsedTimeMillis();
			current.xpos	= last.xpos;
			current.ypos	= last.ypos;
			computeSpeedAccel();
			--life;					//if not updated subtract life
		}
		
		if (!life) alive = false;	//if life is gone alive is false ae. it is dead
		updated = false;			//reset updated message
		return alive;				//return life state
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
	void operator=( const RegionX& region) {
		current.xpos	= region.x;
		current.ypos	= region.y;
		width			= region.width;
		height			= region.height;
		area			= region.area;
		current.time	= ofGetElapsedTimeMillis();
	}
	
	void operator=( const ofxFinger& finger) {
		fingerID		= finger.fingerID;
		current.xpos	= finger.current.xpos;
		current.ypos	= finger.current.ypos;
		width			= finger.width;
		height			= finger.height;
		area			= finger.area;
		current.time	= finger.current.time;
	}
	
	//draw fiducial
	//****//--------------------------------------------------------------------------------------
	void draw( float _x, float _y ) {
		ofNoFill();
		ofSetRectMode(OF_RECTMODE_CENTER);
		glPushMatrix();
		glTranslatef(current.xpos + _x, current.ypos + _y, 0);
		ofSetColor(255, 0, 0);//set color red
		ofRect(0, 0, width, height); //draw finger red
		ofDrawBitmapString(ofToString( fingerID ), 0, height+2); //draw finger number
		glPopMatrix();
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofSetColor(255,255,255);
	}
	
	
	//private stuff
	//****//--------------------------------------------------------------------------------------
private:
	bool	alive; //can we remove fid from list
	bool	updated;// has fid been updated
	int		life;//fids lifespan in frames
	int		state;//fids lost/found state
	
		
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
		
		current.motion_accel	= (current.motion_speed-last.motion_speed)/dt;	
	}
	
	//make last frame = this frame
	void saveLastFrame() {
		last.time	= current.time;
		last.xpos	= current.xpos;
		last.ypos	= current.ypos;
		last.motion_speed	= current.motion_speed;
	}
	
};


#endif