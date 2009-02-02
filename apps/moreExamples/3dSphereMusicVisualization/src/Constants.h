#ifndef CONSTANTS_H
#define CONSTANTS_H


// #define GRAB_FRAME_SEQUENCE


#ifdef GRAB_FRAME_SEQUENCE

//boids

#define NumBoids 10000
#define NumP 10

//sphere

#define SphereNumLines 100
#define SphereNumRows 100

//particles

#define AddMult 1000


#else

//boids

//#define NumBoids 2000
#define NumBoids 800

// #define NumP 10
#define NumP 10

//sphere

// #define SphereNumLines 100
// #define SphereNumRows 100
#define SphereNumLines 50
#define SphereNumRows 50

//particles

// #define AddMult 1000
#define AddMult 520

#endif

// #define NumBands 1024
#define NumBands 512

#endif


