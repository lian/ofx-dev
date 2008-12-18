/*
 *  ofx2dFluid.h
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


#ifndef OF_X_2D_FLUID_H
#define OF_X_2D_FLUID_H

#include <list>
#include "ofMain.h"
#include "ofx2dSolver.h"
#include "ofx2dFluidConstants.h"


//The Fluid Class
//	----------------------------------------------------------------------------------------------------
class ofx2dFluid : public ofx2dSolver {
	
	public:
	
		//constructors
		//this constructor has a default grid size of 100
		ofx2dFluid ();
		//this constructor can set the grid size 
		ofx2dFluid (int _gridSize);
	
		//destructor
		~ofx2dFluid ();
	
		//draw variables
		bool	wireframe, //draw wireframe
				drawvelocities, //draw velocities
				drawcircle, //draw circles 
				drawbounds, //draw bounds
				drawAlpha;
	
		//general variables
		float height, width;//with and height of fluid
	
		//force and source values
		float	force, source; //amount of influence of force and source points
	
		//influence values
		float gravity, wind, fade; //self explanatory
	
		//influences
		bool	fadeOut,
				addWind,
				addGravity;
	
		//**still working on this-----------------//
		rgbFloat bound_color;//bound color//	 //
		//--------------------------------------//
	
		//fluid objects
		list <ofxFluidObject> fluid_objects;
	
		//force position data
		list <ofxForceObject> force_objects;
	
		// main fluid functions//
		void update(); //updates the fluid
		void draw(); //draws the fluid
		void add_object ( ofxFluidObject & _object ); //adds object to the fluid
		void add_force ( ofxForceObject & _object ); // adds forces only to the fluid
		//THE GETTERS
		ofPoint get_velocity ( float _x, float _y, int _influence = 100);// gets velocity of fluid at x,y position
		float get_dencity (float _x, float _y); //gets dencity of fluid at x,y position
		ofxFluidObject * get_fluid(int _id);//returns fluid object with specified id
		ofxForceObject * get_force(int _id);//returns force object with specified id
		//THE SETTERS
		void set_size (float _w, float _h); // sets sizes of fluid
		void set_curl ( float _curl); //sets curl of fluid
		void set_viscocity ( float _visc); //set viscocity of fluid
		void set_Influences ( float _source, float _force = 0.5f);//sets the amount of influence of force and source points
		void set_fade ( bool _set, float _fade = 1.0f);//sets the fade value
		void set_wind ( bool _set, float _wind = 1.5f);//sets the wind value
		void set_gravity ( bool _set, float _gravity = 5.0);//sets the gravity value
		void set_alpha ( bool _set); //true to turn on alpha **off by default for speeds sake
	
		//**still working on this part----------------------------------------------------------//
		void add_bound (float _x, float _y);//adds blocked pixels where there is no fluid		//
		void remove_bound ( float _x, float _y);// removes blocked pixels						//
		void set_bnd_color ( float _r, float _g, float _b);//sets boundry color					//
		//**------------------------------------------------------------------------------------//
	
	private:
		//position variables
		int omx, omy, mx, my;
		int fx, fy, ofx, ofy;
		//update
		void object_update( float * d, float * r, float * g, float * b, float * u, float * v ); //updates object densities
		void update_force(); //updates forces only
};

#endif
