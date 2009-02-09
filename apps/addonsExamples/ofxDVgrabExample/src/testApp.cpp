#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    /* allocate for PAL DV video.....NTSC has height = 480 */
	camWidth 		= 720;
	camHeight 		= 576;

    /* Load video into ofTexture... */
    useTexture = true;

    /* deinterlace types are OF_DV_NO_DEINTERLACE, OF_DV_AVERAGE_DEINTERLACE
    and OF_DV_LINEAR_BLEND_DEINTERLACE (a little slower than average, but a bit more subtle) */
    /* video types are OF_DV_PAL and OF_DV_NTSC */
	dvUtils.initGrabber(useTexture, 2, OF_DV_PAL);

	videoPixels 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);

    /* frame rate calculation for DV cam */
	mytimeThen = 0.0f;
	myframes = 0;
}

void testApp::exit(){

	delete [] videoPixels;
}

//--------------------------------------------------------------
void testApp::update(){

	ofBackground(100,100,100);

    dvUtils.grabFrame();

	if (dvUtils.isFrameNew())
	{
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = dvUtils.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoPixels[i] = 255 - pixels[i];
		}
		videoTexture.loadData(videoPixels, camWidth,camHeight, GL_RGB);

        mytimeNow = ofGetElapsedTimef();
		if( (mytimeNow-mytimeThen) > 0.05f || myframes == 0 ) {
			myfps = (double) myframes / (mytimeNow-mytimeThen);
			mytimeThen = mytimeNow;
			myframes = 0;
			myframeRate = 0.9f * myframeRate + 0.1f * myfps;
			sprintf(buf2,"DV Capture framerate : %f",myframeRate);
		}
		myframes++;
	}

	sprintf(buf,"App framerate : %f",ofGetFrameRate());


}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);

    dvUtils.draw(20,20);

	videoTexture.draw(20+camWidth,20,camWidth,camHeight);


	ofDrawBitmapString(buf,10,620);
	ofDrawBitmapString(buf2,10,640);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

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
