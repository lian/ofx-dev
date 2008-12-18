#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
  
  //set background to black
  ofBackground(255,255,200);  
  
  //for smooth animation
  ofSetVerticalSync(true);
  

  //turn on alpha blending for colors
  ofEnableAlphaBlending();

  //load some obj files from disk
  crane.loadFile("crane.obj");

  bMousePressed = false;
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetupScreen();
  
  //draw in middle of the screen
  glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);

  //tumble according to mouse
  glRotatef(mouseY,1,0,0);
  glRotatef(mouseX,0,1,0);

  //scale large enough to see the model
  float s = min(ofGetWidth(),ofGetHeight())*0.4;
  glScalef(s,s,s);


  if (bMousePressed == false){
                    
        //draw the model
        glColor4f(0.5,1,0,0.4);//lime color
        crane.fillFaces();//first the faces
        
        glColor4f(0,0.8,0,1);//outline
        crane.outlineFaces();//then the edges.
      
  } else {
    
        glColor4f(0,0.1,0,0.5);//outline
        crane.outlineFaces();//then the edges.
        
        //wanna see the vertices?
        glColor4f(0,0,0,0.85);
        glPointSize(1);
        crane.pointVertices();
  }
  
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
  //loop through all the crane's vertices and scramble each point a
  //little bit.
  for(int i=0;i<crane.vertices.size();i++){
    crane.vertices[i].x += ofRandomf()*0.1;
    crane.vertices[i].y += ofRandomf()*0.1;
    crane.vertices[i].z += ofRandomf()*0.1;
  }
  
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
     bMousePressed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
     bMousePressed = false;
}
