#ifndef CONSTANTS_H
#define CONSTANTS_H


//#define GRAB_FRAME_SEQUENCE //uncomenting this will save an image of every frame

// #define NumBands 1024
#define NumBands 512


//settings for when exporting a frame sequence
#ifdef GRAB_FRAME_SEQUENCE

//boids

#define NumEmitters NumBands

//particles

#define AddMult 150

//Pontos

#define NumP 3

#define ShowTrail // show a trail


//settings for when NOT exporting a frame sequence
#else

//boids

#define NumEmitters NumBands

//particles

#define AddMult 150

//Pontos

#define NumP 3

#endif

#endif


