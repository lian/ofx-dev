#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0,0,0);

    image.loadImage(ofToDataPath("images/board_0.jpg"));

    w = image.width;
    h = image.height;

    imageAsGray.allocate(w,h);

    mouseX = 0;
    mouseY = 0;


    imageAsGray.setFromPixels( image.getPixels(), w, h);
    imageAsGray.threshold(100);
    imageAsGray.invert();


    int     minArea             = 20;
    int     maxArea             = w*h*.5;
    int     nConsidered         = 30;
    bool    bFindHoles          = false;
    bool    bUseApproximation   = false;

    contourFinder.findContours(imageAsGray,minArea,maxArea,nConsidered, bFindHoles,bUseApproximation);


}
//--------------------------------------------------------------
void testApp::update(){







}

//--------------------------------------------------------------
void testApp::draw(){


    ofEnableAlphaBlending();

    ofSetColor(0xffffff);
    image.draw(0,0);


    ofSetColor(0x8aff00);
    ofNoFill();
    glLineWidth(2.0);

    for( int i = 0; i < contourFinder.nBlobs; i++)
    {
        findLines(contourFinder.blobs[i].pts,lines,30,40,30);

        for( int j = 0; j < lines.size(); j++)
        {
            ofLine(lines[j].x,lines[j].y,lines[j].z,lines[j].w);
            ofCircle(lines[j].x,lines[j].y,3);
            ofCircle(lines[j].z,lines[j].w,3);
        }

    }


    ofSetColor(0xffffff);
    ofDrawBitmapString( ofToString( ofGetFrameRate(),2), 40, 460);


}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){



    switch( key )
    {
        default: break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
