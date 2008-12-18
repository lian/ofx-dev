/*
 *  ofx2dFluidConstants.h
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



#ifndef OF_X_2D_FLUID_CONSTANTS_H
#define OF_X_2D_FLUID_CONSTANTS_H

//color data structure
//	----------------------------------------------------------------------------------------------------
typedef struct rgbFloat {
	float r, g, b;
};

//The Fluid Object Class
//	----------------------------------------------------------------------------------------------------
class ofxFluidObject {
	
public:	
	int ID; // object id
	ofPoint position, delta;//position and delta variables/**should not mess with these use set_position**/
	rgbFloat cf; //color info
	bool color_set;// true if color data is set in cf
	bool update_color; //color was updated
	bool updated; //object updated
	
	//constructor
	ofxFluidObject() {
		ID				= -1;
		color_set		= false;
		update_color	= false;
		updated			= false;
		position.set(-100, -100);
		randomize_color();
	}
	
	//operator overloading
	void operator=(ofxFluidObject & _object) {
		ID = _object.ID;
		position.set(_object.position.x, _object.position.y);
		delta.set(_object.delta.x, _object.delta.y);
		cf.r = _object.cf.r;
		cf.g = _object.cf.g;
		cf.b = _object.cf.b;
		color_set = _object.color_set;
		update_color = _object.update_color;
		updated = _object.updated;
	}
	
	//sets random color data
	void randomize_color(bool _update = false) {
		float div = 1.0 / (RAND_MAX);
		cf.r = (float) rand() * div;
		cf.g = (float) rand() * div;
		cf.b = (float) rand() * div;
		color_set = true;
		update_color = _update;
	}
	
	//from 0 - 255
	void set_color(int _r, int _g, int _b, bool _update = false) {
		cf.r = (float)_r / 255.0f; cf.r = MAX(0,MIN(cf.r,1.0f));
		cf.g = (float)_g / 255.0f; cf.g = MAX(0,MIN(cf.g,1.0f));
		cf.b = (float)_b / 255.0f; cf.b = MAX(0,MIN(cf.b,1.0f));
		color_set = true;
		update_color = _update;
	}
	
	//get color data
	rgbFloat get_color() {
		return cf;
	}
	
	//sets the object id
	void set_id( int _id) {
		ID = _id;
	}
	
	//sets position & delta using x,y coordinates
	void set_position(float _x, float _y, bool _updateDelta = false) {
		if (_updateDelta) {
			delta.set(position.x, position.y);
		}
		position.set(_x, _y);		
	}
	
	//sets position & delta using ofPoint
	void set_position(ofPoint _pos, bool _updateDelta = false) {
		if (_updateDelta) {
			delta.set(position.x, position.y);
		}
		position.set(_pos.x, _pos.y);
	}
	
	//get current position
	ofPoint get_position() {
		return position;
	}
	
	//update position and color data
	void update( ofxFluidObject& object ) {
		set_position(object.get_position(), true);
		if (!object.update_color) update_color = false;
		else {
			cf.r					= object.cf.r;
			cf.g					= object.cf.g;
			cf.b					= object.cf.b;
			update_color			= true;
			object.update_color		= false;
		}
		updated = true;
	}
	
};


//The Force Object Class
//	----------------------------------------------------------------------------------------------------
class ofxForceObject {
	
public:	
	int ID; // object id
	ofPoint position, delta;//position and delta variables
	float force;//force influence
	bool updated, forceSet; //object updated
	
	//constructor
	ofxForceObject() {
		ID				= -1;
		updated			= false;
		force			= 0.5f;
		position.set(-1, -1);
	}
		
	//sets position & delta using x,y coordinates
	void set_position(float _x, float _y, bool _updateDelta = false) {
		if (_updateDelta) {
			delta.set(position.x, position.y);
		}
		position.set(_x, _y);		
	}
	
	//sets position & delta using ofPoint
	void set_position(ofPoint _pos, bool _updateDelta = false) {
		if (_updateDelta) {
			delta.set(position.x, position.y);
		}
		position.set(_pos.x, _pos.y);
	}
	
	//get current position
	ofPoint get_position() {
		return position;
	}
	
	void set_force(bool _set, float _force) {
		forceSet	= _set;
		force		= _force;
	}
	
	//sets the object id
	void set_id( int _id) {
		ID = _id;
	}
	
	//update position and color data
	void update( ofxForceObject& object ) {
		set_position(object.get_position(), true);
		updated = true;
	}
};

#endif