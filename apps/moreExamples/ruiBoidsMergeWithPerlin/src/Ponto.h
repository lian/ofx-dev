/*
 *  Ponto.h
 *  openFrameworks
 *
 *  Created by rui madeira on 6/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 #ifndef PONTO_H
 #define PONTO_H
 #include "ofMain.h"

struct Ponto{
	GLfloat x, y, z, vx, vy, vz, ax, ay, az;
	GLfloat offX, offY, ang, offAng;
};

#endif
