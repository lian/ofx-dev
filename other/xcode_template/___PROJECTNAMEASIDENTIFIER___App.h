/*
 *  ___PROJECTNAMEASIDENTIFIER___App.h
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright (c) ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 *
 */

#ifndef ____PROJECTNAMEASIDENTIFIER____APP
#define ____PROJECTNAMEASIDENTIFIER____APP

#include "ofMain.h"
#include "ofAddons.h"

class ___PROJECTNAMEASIDENTIFIER___App : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
};

#endif /*____PROJECTNAMEASIDENTIFIER____APP*/
