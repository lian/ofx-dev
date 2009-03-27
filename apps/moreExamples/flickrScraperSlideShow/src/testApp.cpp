#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(32);

	sws.textReady				+= Delegate<testApp, string>(this, &testApp::onTextReceived);
	sws.unthreadedStreamReady	+= Delegate<testApp, StreamEventArgs>(this, &testApp::onUnthreadedStreamReceived);
	sws.threadedStreamReady		+= Delegate<testApp, StreamEventArgs>(this, &testApp::onThreadedStreamReceived);
	
	threadedMemImage.setUseTexture(false); // we can't use a texture with this one
	received = false;
	txCount = 0;
	pixArr = new unsigned char * [4];
}


//--------------------------------------------------------------
void testApp::update(){
	if (received) {
		received = false;
		
		int pixSize = threadedMemImage.width*threadedMemImage.height*3;
		pixArr[txCount] = new unsigned char[pixSize];
		memcpy(pixArr[txCount], threadedMemImage.getPixels(), pixSize);
		tx[txCount].allocate(threadedMemImage.width, threadedMemImage.height, GL_RGB);
		tx[txCount].loadData(pixArr[txCount], threadedMemImage.width, threadedMemImage.height, GL_RGB);
		//tx[txCount].loadData(threadedMemImage.getPixels(), threadedMemImage.width, threadedMemImage.height, GL_RGB);
		txCount ++;		
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	memImg.draw(0,0);
	ofDrawBitmapString(resp, 20,20);
	for (int i = 0; i < txCount; i++) {
		glPushMatrix();
			tx[i].draw(i*150, 0);
		glPopMatrix();
	}
	
	// the great blocking test
	ofRect(ofRandom(10,20), ofRandom(10,20), 10,10);

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch (key) {
		case '1':
			sws.getStreamThreaded("http://www.jesusgollonet.com/blog/imagenes/chelpa_ferro1.jpg");
			break;
		case '2':
			sws.getStreamThreaded("http://www.jesusgollonet.com/blog/imagenes/djRupture-minesweeper_suite.jpg");
			break;
		case '3':
			sws.getStreamThreaded("http://www.jesusgollonet.com/blog/imagenes/dublab.gif");
			break;
		case '4':
			sws.getStreamThreaded("http://www.jesusgollonet.com/blog/imagenes/NaturalSynthesizer.jpg");
			break;
		case '5':
			sws.getText("http://www.jesusgollonet.com/");
			break;
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
