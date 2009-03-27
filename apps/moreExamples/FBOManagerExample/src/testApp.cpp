#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(127,127,127);
    rm.allocateForNScreens(2, 1400, 500);
    rm.loadFromXml("fboSettings.xml");

    guiIn   = ofRectangle(10, 40, 500, 178);
    guiOut  = ofRectangle(guiIn.x + guiIn.width + 30, 40, 500, 178);

    twoScreenImage.loadImage("adam.jpg");
    toggleImage = true;
    doRender = true;
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){

	if ( doRender ) {
		ofSetColor(255, 255, 255, 255);
		
	    rm.startOffscreenDraw();

	        if( toggleImage ){
	            ofSetColor(255, 255, 255, 255);
	            twoScreenImage.draw(0, 0, 1400, 500);
	        }
	        else{

	            ofSetColor(50, 50, 50);
	            ofRect(0, 0, rm.width, rm.height);

	            ofSetColor(0xFF0000);
	            ofRect(100, 100, 100, 100);

	            ofSetColor(0xFF00FF);
	            ofRect(200, 100, 100, 100);

	            ofSetColor(0xFFFF00);
	            ofRect(800, 100, 100, 100);

	            ofSetColor(0x0000FF);
	            ofRect(1050, 100, 100, 100);
	        }

	    rm.endOffscreenDraw();

	}

    ofSetColor(255, 255, 255, 255);

    rm.drawInputDiagnostically(guiIn.x, guiIn.y, guiIn.width, guiIn.height);
    rm.drawOutputDiagnostically(guiOut.x, guiOut.y, guiOut.width, guiOut.height);

    glPushMatrix();
        glTranslatef(10, 300, 0);
        ofSetColor(255, 255, 255, 255);
        rm.drawScreen(0);
        rm.drawScreen(1);
    glPopMatrix();

    ofDrawBitmapString("internal texture points", 10, 228);
    ofDrawBitmapString("texture warping points", 535, 228);

    ofDrawBitmapString("screen 1", 10, 290);
    ofDrawBitmapString("screen 2", 710, 290);

    ofDrawBitmapString("s - to save to xml   r - to reload from xml    c - reset coordinates    g -  draw open gl shapes	t -  render to texture\n", 10, 16);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    if( key == 'g'){
        toggleImage = !toggleImage;
    }

    if( key == 's'){
        rm.saveToXml();
    }

    if( key == 'r' ){
        rm.reloadFromXml();
    }

    if(key == 'c'){
        rm.resetCoordinates();
    }

    if(key == 't'){
        doRender = !doRender;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    rm.mouseDragInputPoint(guiIn, ofPoint(x, y));
    rm.mouseDragOutputPoint(guiOut, ofPoint( x, y));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
     if( !rm.mouseSelectInputPoint(guiIn, ofPoint(x, y)) ){
        rm.mouseSelectOutputPoint(guiOut, ofPoint( x,  y));
    }
}
