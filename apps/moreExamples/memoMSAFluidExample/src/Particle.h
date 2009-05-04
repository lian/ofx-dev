/*
 *  Particle.h
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once


class Particle {
public:	

    float x, y;
    float vx, vy;
    float radius;
    float alpha;
    float mass;
	
    void init(float x, float y);
    void update();
	void updateVertexArrays(int i, float* posBuffer, float* colBuffer);
	void drawOldSchool();
};

