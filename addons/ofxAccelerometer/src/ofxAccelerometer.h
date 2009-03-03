/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

#pragma once

#include "ofTypes.h"

typedef void (*ofxAccelCB)(ofPoint&);			// typedef for accelerometer callback

class ofxAccelerometerHandler {
public:
	ofxAccelerometerHandler() {
		callback = NULL;
		setForceSmoothing(0.1f);					// little bit of smoothing for force
		setOrientationSmoothing(0.9f);				// lots of smoothing for orientation / matrix
	}
	
	// call this to set it all up
	void setup();
	
	// call this when you no longer need the accelerometer
	void exit();
	
	// returns current smoothed accelerometer data (value in number of g's (1g = gravity, 9.8m/s^2)
	ofPoint &getForce() {
		return accelForce;
	}
	
	// returns current real accelerometer data (value in number of g's (1g = gravity, 9.8m/s^2)
	ofPoint &getRawAcceleration() {
		return accelReal;
	}
	
	// returns current orientation in degrees (x: pitch, y: roll, z: not used)
	ofPoint &getOrientation() {
		updateOrientation();
		return orientation;
	}
	
	
	GLfloat* getMatrix() {
		updateMatrix();
		return (GLfloat*)matrix;
	}
	
	
	// set amount of smoothing on data (0: no smooth, 1:very smooth)
	void setForceSmoothing(float forceSmoothing) {
		this->forceSmoothing = forceSmoothing;
	}
	
	void setOrientationSmoothing(float orientationSmoothing) {
		this->orientationSmoothing = orientationSmoothing;
	}
	
	
	// if you have a callback which conforms to ofxAccelCB, pass it to this to have it called when motion is detected
	void setCallback(ofxAccelCB new_callback) {
		callback = new_callback;
	}
	
	
	// platform specific accelerometer engine should call this when motion is detected
	void update(float x, float y, float z) {
		orientDirty = matrixDirty = true;
		
		accelReal.set(x, y, z);
		
		if(forceSmoothing) {
			float lerpFactor = 1 - forceSmoothing;	
			if(lerpFactor>1) lerpFactor = 1;
			else if(lerpFactor < 0.01) lerpFactor = 0.01;
			
			accelForce += (accelReal - accelForce) * lerpFactor;
		} else {
			accelForce.set(x, y, z);
		}
		
		if(orientationSmoothing) {
			float lerpFactor = 1 - orientationSmoothing;	
			if(lerpFactor>1) lerpFactor = 1;
			else if(lerpFactor < 0.01) lerpFactor = 0.01;
			
			accelOrientation += (accelReal - accelOrientation) * lerpFactor;
		} else {
			accelOrientation.set(x, y, z);
		}
		
		if(callback) callback(accelReal);
	}

	
protected:
	ofxAccelCB callback;
	float forceSmoothing;			// amount to smooth incoming data by
	float orientationSmoothing;	// amount to smooth orientation by
	//	ofPoint restAccel;			// rest acceleration (for calibration)
	ofPoint accelReal;			// current acceleration
	ofPoint accelForce;		// smoothed for force
	ofPoint accelOrientation;	// smoothed for acceleration
	ofPoint orientation;		// current orientation
	bool orientDirty;

	GLfloat matrix[4][4];		// contains orientation matrix
	bool matrixDirty;
	
	void updateOrientation() {
		if(!orientDirty) return;
		orientDirty = false;
		
		orientation.x = atan2(accelOrientation.y, -accelOrientation.z) * RAD_TO_DEG; 
		orientation.y = atan2(accelOrientation.x, -accelOrientation.z) * RAD_TO_DEG;
		orientation.z = 0;
	}
	
	
	void updateMatrix() {
		if(!matrixDirty) return;
		matrixDirty = false;
		
		float length;
		
		//Make sure we have a big enough acceleration vector
		length = sqrtf(accelOrientation.x * accelOrientation.x + accelOrientation.y * accelOrientation.y + accelOrientation.z * accelOrientation.z);
		
		if(length < 0.1) return;
		
		//Clear matrix to be used to rotate from the current referential to one based on the gravity vector
		bzero(matrix, sizeof(matrix));
		matrix[3][3] = 1.0;
		
		//Setup first matrix column as gravity vector
		matrix[0][0] = accelOrientation.x / length;
		matrix[0][1] = accelOrientation.y / length;
		matrix[0][2] = accelOrientation.z / length;
		
		//Setup second matrix column as an arbitrary vector in the plane perpendicular to the gravity vector {Gx, Gy, Gz} defined by by the equation "Gx * x + Gy * y + Gz * z = 0" in which we arbitrarily set x=0 and y=1
		matrix[1][0] = 0.0;
		matrix[1][1] = 1.0;
		matrix[1][2] = -accelOrientation.y / accelOrientation.z;
		length = sqrtf(matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] + matrix[1][2] * matrix[1][2]);
		matrix[1][0] /= length;
		matrix[1][1] /= length;
		matrix[1][2] /= length;
		
		//Setup third matrix column as the cross product of the first two
		matrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
		matrix[2][1] = matrix[1][0] * matrix[0][2] - matrix[1][2] * matrix[0][0];
		matrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

};

extern ofxAccelerometerHandler ofxAccelerometer;
