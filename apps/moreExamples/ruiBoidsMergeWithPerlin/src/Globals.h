/*
 *  Globals.h
 *  openFrameworks
 *
 *  Created by rui madeira on 6/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLOBALS_H
#define GLOBALS_H

//#define SAVE_IMAGE_SEQUENCE

#ifdef SAVE_IMAGE_SEQUENCE
#define MaxParticles 6000
#define MaxFrames 3000
#else
#define MaxParticles 10
#endif



//boids
#ifdef SAVE_IMAGE_SEQUENCE
#define numBoids 500
#else
#define numBoids 50
#endif
#define larg 10


//pontos
#define numPoints 20
#define pK 0.8;
#define pDamp 0.4


//flowField complexity
#define fieldComplex 3000

#endif

