/*
 *  ofx2dFluid.cpp
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

#include "ofx2dFluid.h"

//constructors
//this constructor has a default grid size of 100
ofx2dFluid::ofx2dFluid() {
	
	if (!height) height = 480.0f; 
	if (!width) width 	= 640.0f;
	
	force = 0.5f; //force influence
	source = 45.0f; //source influence
	
	gravity = 5.0;//gravity amount
	wind	= 1.5;//wind amount
	fade	= 1.0;//fade amount
	
	fadeOut		= false;
	addWind		= false;
	addGravity	= false;
	
	//make boundry color red
	bound_color.r = 1.0f;
	bound_color.g = 0.0f;
	bound_color.b = 0.0f;
		
	drawvelocities	= false;
	drawcircle		= false;
	wireframe		= false;
	drawbounds		= false;
	drawAlpha		= false;
		
}

//this constructor can set the grid size
ofx2dFluid::ofx2dFluid(int _gridSize) : ofx2dSolver(_gridSize) {
	
	if (!height) height = 480.0f; 
	if (!width) width 	= 640.0f;

	force	= 0.5f; //force influence
	source	= 45.0f; //source influence
	
	gravity = 5.0;//gravity amount
	wind	= 1.5;//wind amount
	fade	= 1.0;//fade amount
	
	fadeOut		= false;
	addWind		= false;
	addGravity	= false;
	
	//make boundry color red
	bound_color.r = 1.0f;
	bound_color.g = 0.0f;
	bound_color.b = 0.0f;
	
	drawvelocities	= false;
	drawcircle		= false;
	wireframe		= false;
	drawbounds		= false;
		
}

//destructor
ofx2dFluid::~ofx2dFluid() {

}


//**------------------------------------------------------UPDATE THE FLUID
void ofx2dFluid::update() {
	
	//erase fluid objects that have not been updated
	 for (list<ofxFluidObject>::iterator f_object = fluid_objects.begin(); f_object != fluid_objects.end(); f_object++) {
		 if(!f_object->updated) fluid_objects.erase(f_object);
	 }
	//update fluid
	object_update( dens_prev, r0, g0, b0, u_prev, v_prev );
	
	//if there are any force objects
	if (force_objects.size() > 0) {
		//erase force objects that have not been updated
		for (list<ofxForceObject>::iterator f_object = force_objects.begin(); f_object != force_objects.end(); f_object++) {
			if(!f_object->updated) force_objects.erase(f_object);
		}
		//update fluid forces
		update_force();
	}
	
	//add curl
	add_vorocity( N, u, v, dt );
	
	//calculate the velocity field
	vel_step	( N, u, v, u_prev, v_prev, visc, dt );
	
	//calculate the density fields for all three colors
	dens_step_rgb ( r, r0, g, g0, b, b0, u, v, diff, dt );
	//calculate alpha channel only if needed
	if (drawAlpha) {
		dens_step ( N, dens, dens_prev, u, v, diff, dt ); //alpha
	}
	
	//if fade out added then do it
	if (fadeOut) {
		// fade out values
		for ( int i=0 ; i<size ; i++ ) {
		
			r0[i]  = 0;
			g0[i]  = 0;
			b0[i]  = 0;
		
			if(r[i] > 0) r[i] -= fade * .01;
			if(g[i] > 0) g[i] -= fade * .01;
			if(b[i] > 0) b[i] -= fade * .01;
			//calculate alpha channel only if needed
			if(drawAlpha && dens[i] > 0) {
				dens_prev [i]  = 0;
				dens[i] -= fade * .01;
			}
		
			if(u[i] > 0) u[i] -= fade * .001;
			if(v[i] > 0) v[i] -= fade * .001;
		}
	}
	
	//if gravity added then do it
	if (addGravity) {
		// add gravity
		for ( int i=0 ; i<size ; i++ ) {
			v_prev[i] += gravity;
		}
	}
	
	//if wind added then do it
	if (addWind) {
		// add wind
		for ( int i=size-(N+2)*20 ; i<size ; i++ ) {
			u_prev[i] += wind;
		}
	}
}


//**------------------------------------------------------DRAW THE FIELD
void ofx2dFluid::draw() {
	int i, j;
	float x, y, h, w;
	float d00,  d01,  d10,  d11;
	float d00r, d00g, d00b;
	float d01r, d01g, d01b;
	float d10r, d10g, d10b;
	float d11r, d11g, d11b;
	
	w = (float)width/N;
	h = (float)height/N;
	
	if (drawAlpha) ofEnableAlphaBlending();
	glShadeModel(GL_SMOOTH);
	glBegin (GL_QUADS);
	
	if (wireframe) {
	 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 }
	 else {
	 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	 }
	
	for ( i=0 ; i<=N ; i++ ) {
		x = i*w;
		for ( j=0 ; j<=N ; j++ ) {
			y = j*h;
			
			//calculate alpha channel only if needed
			if (drawAlpha) {
				d00 = dens[IX(i,j)];
				d01 = dens[IX(i,j+1)];
				d10 = dens[IX(i+1,j)];
				d11 = dens[IX(i+1,j+1)];
			} else {
				d00 = 1;
				d01 = 1;
				d10 = 1;
				d11 = 1;
			}
			
			d00r = r[IX(i,j)];
			d00g = g[IX(i,j)];
			d00b = b[IX(i,j)];
			
			d01r = r[IX(i,j+1)];
			d01g = g[IX(i,j+1)];
			d01b = b[IX(i,j+1)];
			
			d10r = r[IX(i+1,j)];
			d10g = g[IX(i+1,j)];
			d10b = b[IX(i+1,j)];
			
			d11r = r[IX(i+1,j+1)];
			d11g = g[IX(i+1,j+1)];
			d11b = b[IX(i+1,j+1)];
			
			glColor4f ( d00r, d00g, d00b, d00); glVertex2f ( x, y );
			glColor4f ( d10r, d10g, d10b, d10); glVertex2f ( x+w, y );
			glColor4f ( d11r, d11g, d11b, d11); glVertex2f ( x+w, y+h );
			glColor4f ( d01r, d01g, d01b, d01); glVertex2f ( x, y+h );
			
		}
	}
	
	if (drawAlpha) ofDisableAlphaBlending();
	glEnd ();
	
	//draw velocities
	if (drawvelocities) {
		int i, j;
		float x, y, h, w;
		
		w = (float)width/N;
		h = (float)height/N;
		
		glColor3f ( 1.0f, 1.0f, 1.0f );
		glLineWidth ( 100.0f );
		
		glBegin ( GL_LINES );
		
		for ( i=1 ; i<=N ; i++ ) {
			x = i*w;
			for ( j=1 ; j<=N ; j++ ) {
				y = j*h;
				
				glVertex2f ( x, y );
				glVertex2f ( x+u[IX(i,j)], y+v[IX(i,j)] );
			}
		}
		
		glEnd ();		
	}
	
	//draw circle around center
	if (drawcircle) {
		
		for (list<ofxFluidObject>::iterator f_object = fluid_objects.begin(); f_object != fluid_objects.end(); f_object++) {
			
			ofNoFill();			
			glColor3f(f_object->cf.r - 0.06, f_object->cf.g - 0.06 , f_object->cf.b - 0.06);
			ofCircle(f_object->position.x, f_object->position.y, 7);
		}
	}
	
	//draw boundries
	if (drawbounds) {
		int i, j;
		float x, y, h, w;
		
		w = (float)width/N;
		h = (float)height/N;
		
		glBegin(GL_QUADS);
		for ( i=0 ; i<=N ; i++ ) {
			x = (i-0.5f)*w;
			for ( j=0 ; j<=N ; j++ ) {
				y = (j-0.5f)*h;	
				if(blocked[IX(i,j)]) {	
					glColor3f  ( bound_color.r, bound_color.g, bound_color.b ); 
					glVertex2f ( x, y);
					glVertex2f ( x+w, y );
					glVertex2f ( x+w, y+h );
					glVertex2f ( x,  y+h);		
				}
			}
		}
		glEnd();		
	}
}


//**------------------------------------------------------------------------UPDATES OBJECTS INTERACTIONS WITH FLUID
void ofx2dFluid::object_update( float * d, float * r, float * g, float * b, float * u, float * v ) {
	
	int i, j, size = (N+2)*(N+2);
	
	for ( i=0 ; i<size ; i++ ) {
		u[i] = v[i] = r[i] = g[i] = b[i] = 0.0f;
		d[i] = 0.0f;
	}
	
	 for (list<ofxFluidObject>::iterator f_object = fluid_objects.begin(); f_object != fluid_objects.end(); f_object++) {
		
		mx	= f_object->position.x;
		my	= f_object->position.y;
		omx = f_object->delta.x;
		omy = f_object->delta.y;
		
		i = (int)((mx /(float)width)*N+1);
		j = (int)((my/(float)height)*N+1);
		
		if ( i<1 || i>N || j<1 || j>N ) return;
		
		//update colormap
		d[IX(i,j)] = source;
		r[IX(i,j)] = source * f_object->cf.r;
		g[IX(i,j)] = source * f_object->cf.g;
		b[IX(i,j)] = source * f_object->cf.b;
		
		//update force
		u[IX(i,j)] = force * (mx-omx);
		v[IX(i,j)] = force * (omy-my);
		 
		 f_object->updated = false;
	}
}


//**------------------------------------------------------UPDATES FORCES INTERACTIONS WITH FLUID
void ofx2dFluid::update_force() {
	int i, j, a, b;
	
	 for (list<ofxForceObject>::iterator f_object = force_objects.begin(); f_object != force_objects.end(); f_object++) {
		
		fx	= f_object->position.x;
		fy	= f_object->position.y;
		ofx = f_object->delta.x;
		ofy = f_object->delta.y;
		
		i = (int)((fx /(float)width )*N+1);
		j = (int)((fy/(float)height)*N+1);
		
		a = (int)((ofx /(float)width )*N+1);
		b = (int)((ofy/(float)height)*N+1);
		
		/*for (int r= 0; r < 10; r++) {
			for (int o = 0; o < 10; o++) {
				blocked[IX(a,b)]=false;
				blocked[IX(a-1,b)]=false;
				blocked[IX(a,b-1)]=false;
				blocked[IX(a-1,b-1)]=false;
			}
		}*/
		
		if ( i<1 || i>N || j<1 || j>N ) return;
		
		/*for (int r= 0; r < 10; r++) {
			for (int o = 0; o < 10; o++) {
				blocked[IX(i,j)]=true;
				blocked[IX(i-1,j)]=true;
				blocked[IX(i,j-1)]=true;
				blocked[IX(i-1,j-1)]=true;
			}
		}*/
		
		 if (f_object->forceSet) {
			 u[IX(i,j)] = f_object->force * (fx-ofx);
			 v[IX(i,j)] = f_object->force * (ofy-fy);
		 } else {
			 u[IX(i,j)] = force * (fx-ofx);
			 v[IX(i,j)] = force * (ofy-fy);
		}
	}
}


//**---------------------------------------------------------ADDS OBJECTS TO THE FLUID
void ofx2dFluid::add_object( ofxFluidObject & _object ) {
	
	//if object has constructor id we cant use it
	if (_object.ID == -1) {
		printf("This object needs a unique integer ID.\n");
		return;
	}
	
	ofxFluidObject * existing_object = NULL;
	//see if this ID is in the list of objects
	for (list<ofxFluidObject>::iterator f_object = fluid_objects.begin(); f_object != fluid_objects.end(); f_object++) {
		if (_object.ID == f_object->ID)  { //if fiducial id found 
			existing_object = &(*f_object); //make existing_object pointer point to found object in list
			break;
		}
	}
	//if it is update it
	if( existing_object != NULL )existing_object->update(_object);
	else {
		//if not then add it to the list
		_object.updated = true;//make sure to lable it as updated
		fluid_objects.push_back(_object);
		_object.updated = false;//revert
	}
}


//**------------------------------------------------------ADDS FORCES TO THE FLUID
void ofx2dFluid::add_force ( ofxForceObject& _object ) {
	
	
	//if object has constructor id we cant use it
	if (_object.ID == -1) {
		printf("This object needs a unique integer ID.\n");
		return;
	}
	
	ofxForceObject * existing_object = NULL;
	//see if this ID is in the list of objects
	for (list<ofxForceObject>::iterator f_object = force_objects.begin(); f_object != force_objects.end(); f_object++) {
		if (_object.ID == f_object->ID)  { //if fiducial id found 
			existing_object = &(*f_object); //make existing_object pointer point to found object in list
			break;
		}
	}
	//if it is update it
	if( existing_object != NULL )existing_object->update(_object);
	else {
		//if not then add it to the list
		_object.updated = true;//make sure to lable it as updated
		force_objects.push_back(_object);
		_object.updated = false;//revert
	}
	
}


//**------------------------------------------------------RETURNS FLUID OBJECT SPECIFIED
ofxFluidObject * ofx2dFluid::get_fluid (int _id) {
	ofxFluidObject * existing_object = NULL;
	for (list<ofxFluidObject>::iterator f_object = fluid_objects.begin(); f_object != fluid_objects.end(); f_object++) {
		if ( f_object->ID == _id )  {
			existing_object = &(*f_object);
			break;
		}
	}
		
		if ( existing_object != NULL ) {
			return existing_object;
		} else {
			printf("Fluid object not found\n");
			return 0;
		}
}


//**------------------------------------------------------RETURNS FORCE OBJECT SPECIFIED
ofxForceObject * ofx2dFluid::get_force(int _id) {
	ofxForceObject * existing_object = NULL;
	for (list<ofxForceObject>::iterator f_object = force_objects.begin(); f_object != force_objects.end(); f_object++) {
		if (_id == f_object->ID)  {
			existing_object = &(*f_object);
			break;
		}
	}
		
		if ( existing_object != NULL ) {
			return existing_object;
		} else {
			printf("Force object not found\n");
			return 0;
		}
}
		
		
//**------------------------------------------------------SETS FLUID SIZE
void ofx2dFluid::set_size (float _w, float _h) {
	
	width	= _w;
	height	= _h;
}


//**------------------------------------------------------SETS INFLUENCE (or strength) OF SOURCE AND FORCE POINTS
void ofx2dFluid::set_Influences (float _source, float _force) {
	force	= _force;
	source	= _source;
}


//**------------------------------------------------------GETS VELOCITY FROM x,y POSITION
ofPoint ofx2dFluid::get_velocity( float _x, float _y, int _influence) {
	
	int i = (int)(( _x / width)*N+1);
	int j = (int)(( _y/ height)*N+1);
	
	ofPoint veloc;
	
	veloc.x = u[IX(i,j)] * _influence; 
	veloc.y = v[IX(i,j)] * _influence;
	
	return veloc;
}


//**------------------------------------------------------GETS DENSITY FROM x,y POSITION
float ofx2dFluid::get_dencity (float _x, float _y) {
	
	int i = (int)(( _x / width)*N+1);
	int j = (int)(( _y/ height)*N+1);
	
	float dencity;
	float dencity1 = r[IX(i,j)];
	float dencity2 = g[IX(i,j)];
	float dencity3 = b[IX(i,j)];
	dencity = (dencity1 + dencity2 + dencity3) / 3;
	
	return dencity;
	
}
//**------------------------------------------------------SETS FLUID CURL
void ofx2dFluid::set_curl( float _curl) {
	epsilon = _curl;
}


//**------------------------------------------------------SETS FLUID VISCOCITY
void ofx2dFluid::set_viscocity (float _visc) {
	visc = (_visc/10000);
}

//**------------------------------------------------------SETS FADE VALUE
void ofx2dFluid::set_fade(bool _set, float _fade) {
	fadeOut = _set;
	fade	= _fade;
}

//**------------------------------------------------------SETS WIND VALUE
void ofx2dFluid::set_wind(bool _set, float _wind) {
	addWind = _set;
	wind	= _wind;
}

//**------------------------------------------------------SETS GRAVITY VALUE
void ofx2dFluid::set_gravity(bool _set, float _gravity) {
	addGravity	= _set;
	gravity		= _gravity;
}

//**------------------------------------------------------SETS ALPHA CHANNEL ON/OFF
void ofx2dFluid::set_alpha (bool _set) {
	drawAlpha = _set;
}

//**STILL FIGURING THIS PART OUT
//**------------------------------------------------------SETS BOUNDRY COLOR
void ofx2dFluid::set_bnd_color ( float _r, float _g, float _b) {
	bound_color.r = _r;
	bound_color.g = _g;
	bound_color.b = _b;
}


//**------------------------------------------------------ADDS BOUNDRIES
void ofx2dFluid::add_bound (float _x, float _y) {
	int i = (int)(( _x / width)*N+1);
	int j = (int)(( _y/ height)*N+1);

	if ( i<2 || i>N || j<2 || j>N ) return;
	
	blocked[IX(i,j)]=true;
	blocked[IX(i-1,j)]=true;
	blocked[IX(i,j-1)]=true;
	blocked[IX(i-1,j-1)]=true;
	
}


//**------------------------------------------------------REMOVES BOUNDRIES
void ofx2dFluid::remove_bound ( float _x, float _y) {
	int i = (int)(( _x / width)*N+1);
	int j = (int)(( _y/ height)*N+1);

	if ( i<2 || i>N || j<2 || j>N ) return;
	
	blocked[IX(i,j)]=false;
	blocked[IX(i-1,j)]=false;
	blocked[IX(i,j-1)]=false;
	blocked[IX(i-1,j-1)]=false;
}
