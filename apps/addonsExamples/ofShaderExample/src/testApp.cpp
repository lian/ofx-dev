#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofBackground(100, 100, 0);
	ofSetFrameRate(60);
	
	ofImage img;
    img.loadImage("oF.jpg");
    tex.allocate(img.width, img.height, GL_RGB); 
    tex.loadData(img.getPixels(), img.width, img.height, GL_RGB);
	
	shaderA_IsActive = false;
	shaderB_IsActive = false;
	cam_IsActive = false;
	useTex = false;
	
	shaderA.loadShader("color");
	shaderB.loadShader("faceCam");

	center.x = ofGetWidth()/2;
	center.y = ofGetHeight()/2;
	center.z = 0;
	
	cam.pos.x = 0;
	cam.pos.y = center.y;
	cam.pos.z = 9000;
	cam.center = &center;

}

//--------------------------------------------------------------
void testApp::update(){
	if (cam_IsActive) cam.move();
	timer += 0.01;
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0,0,0);
	ofDrawBitmapString("press '1' to turn off shaders\npress '2' to toggle on/off rotating camera\npress '3' to toggle on/off on shader A [only]\npress '4' to toggle on/off on shader B [only]\npress '5' to map or not a texture on the GL_QUAD", 20, 20);

	if (cam_IsActive) cam.place();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	if (useTex) {
		glEnable(tex.getTextureData().textureTarget );
		glBindTexture (tex.getTextureData().textureTarget, (GLuint)tex.getTextureData().textureID ); 
	}
	
	
	if (shaderA_IsActive) {
		shaderA.setShaderActive(shaderA_IsActive);
		shaderA.setUniform("time", (float)timer);
	} else if (shaderB_IsActive) {
		shaderB.setShaderActive(shaderB_IsActive);
	}
	
	//glTranslatef(256.0f,128.0f, 0.0f);

	if (useTex) {
	/*
		glBegin(GL_QUADS);
			glTexCoord3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f,0.0f, 0.0f);
			glTexCoord3f(512.0f, 0.0f, 0.0f);
			glVertex3f(512.0f,0.0f, 0.0f);
			glTexCoord3f(512.0f,512.0f, 0.0f);
			glVertex3f(512.0f,512.0f, 0.0f);
			glTexCoord3f(0.0f, 512.0f, 0.0f);
			glVertex3f(0.0f, 512.0f, 0.0f);
		glEnd();
	*/	
		glBegin(GL_QUADS);
			// x,y,z, size of the quad
			glTexCoord4f( 512.0f, 384.0f, 0.0f, 512.0f); // <-- IMPORTANT
			glVertex2f( -1.0f, -1.0f );
			glVertex2f( +1.0f, -1.0f );
			glVertex2f( +1.0f, +1.0f );
			glVertex2f( -1.0f, +1.0f ); 
		glEnd();
	} else {
		glTranslatef(256.0f,128.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f,0.0f, 0.0f);
			glVertex3f(512.0f,0.0f, 0.0f);
			glVertex3f(512.0f,512.0f, 0.0f);
			glVertex3f(0.0f, 512.0f, 0.0f);
		glEnd();
	}
	
 
	
	if (shaderA_IsActive) {
		shaderA.setShaderActive(false);
	} else {
		shaderB.setShaderActive(false);
	}
	
	if (useTex) {
		glBindTexture(tex.getTextureData().textureTarget, 0);
		glDisable(tex.getTextureData().textureTarget );
	}
	

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	switch (key) {
       
        case '1':
            printf("no shaders \n");
			shaderA_IsActive = false;
			shaderB_IsActive = false;
            break;
       
	    case '2':
			cam_IsActive = !cam_IsActive;
			printf("Toggle on/off rotating camera \n");
            break;
			
		case '3':
			shaderB_IsActive = false;
			shaderA_IsActive = !shaderA_IsActive;
			printf("Quads deformation via vertex shader : %d \n", shaderA_IsActive);
            break;
            
        case '4':
			shaderA_IsActive = false;
			shaderB_IsActive = !shaderB_IsActive;
            printf("Billboarding via vertex shader : %d \n", shaderB_IsActive);
            break;
			
		case '5':
			useTex = !useTex;
            printf("Using texture : %d \n", shaderB_IsActive);
            break;

    }
}
