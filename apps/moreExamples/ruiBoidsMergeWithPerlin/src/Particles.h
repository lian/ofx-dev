#ifndef PARTICLES_H
#define PARTICLES_H

#include "ofMain.h"
#include "perlin.h"


class Particles{
public:
	GLfloat x, y, z, vx, vy, vz, G, size;
	Perlin *noise;
	GLint fieldDivide;
	GLint life, step;
	GLint r, g, b;
	Particles();
	~Particles();
	void partSetup(GLfloat _x, GLfloat _y, GLfloat _z, Perlin *_noise);
	void move();
	void render();
};

#endif