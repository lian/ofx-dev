/*
 *  Boid.h
 *  openFrameworks
 *
 *  Created by rui madeira on 6/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 #ifndef BOID_H
 #define BOID_H
 #include "Globals.h"
 #include "ofMain.h"
 #include "Ponto.h"
 #include "perlin.h"
 #include "Particles.h"

 class Boid{
 public:
	
	Ponto *p[numPoints];
		
	GLint step;
	GLint r, g, b;
	Perlin *noise;
	vector <Particles> *part;
	GLfloat k;
		
	Boid(Perlin *_noise, vector <Particles> *_part);
	~Boid();
	
	void mover();
	void render();
	void constrainMovement(float _averX, float _averY, float _averZ);
	GLfloat var(GLint _step);
};

#endif
	
	
 
	

