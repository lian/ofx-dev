/*
 *  main.cpp
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright (c) ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 *
 */

#include "ofMain.h"
#include "___PROJECTNAMEASIDENTIFIER___App.h"

int main(int argc, char *argv[]) {
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	ofRunApp(new ___PROJECTNAMEASIDENTIFIER___App);
}
