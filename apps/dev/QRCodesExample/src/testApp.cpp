#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	 
	ofSetFrameRate(32);
	
	orgImg.loadImage("1.jpg");
	colorImg.allocate( orgImg.getWidth(), orgImg.getHeight() );
	colorImg.setFromPixels( orgImg.getPixels(), orgImg.getWidth(), orgImg.getHeight() );
	
	QrDecoderHandle decoder=qr_decoder_open();
	short stat=qr_decoder_decode_image(decoder, colorImg.getCvImage() );
    // printf("STATUS=%04x\n",stat);
	
	QrCodeHeader header;
    if(qr_decoder_get_header(decoder,&header)){
        char *buf=new char[header.byte_size+1];
        qr_decoder_get_body(decoder,(unsigned char *)buf,header.byte_size+1);
        // printf("%s\n",buf);
		debug_string = debug_string+buf;
    }
   	qr_decoder_close(decoder);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	colorImg.draw(0,0);
	
	ofSetColor(245, 0, 0);
    ofDrawBitmapString( debug_string, 10, colorImg.height+15 );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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
