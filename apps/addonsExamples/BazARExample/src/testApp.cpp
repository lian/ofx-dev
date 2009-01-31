#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	ofSetFrameRate(32);
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	
	detector.setup(320,240);
	
	detector.load_classifier("merkel.classifier");
	// detector.load_classifier("datenschleuder1.classifier");
	// detector.load_classifier("datenschleuder2.classifier");
	// detector.load_classifier("datenschleuder3.classifier");
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);	
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		detector.processNextImage( vidGrabber.getPixels(), 320, 240, OF_IMAGE_COLOR );
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);
	
	vidGrabber.draw(0,0);
	detector.detectImage.draw(0,258);

	for( int i = 0; i < detector.mBazARModels.size(); i += 1 ) {
		if (detector.mBazARModels[i]->isDetected == true) {

			detector.mBazARModels[i]->mImage.draw(420, i*55, 320, 240);
			
			ofSetColor(255,0,0);

			for( int a = 0; a < detector.mBazARModels[i]->por.model_point_number; a += 1 ) {
				int _x = detector.mBazARModels[i]->por.x0 + (int)PyrImage::convCoordf(float(detector.mBazARModels[i]->por.model_points[a].M[0]), int(detector.mBazARModels[i]->por.model_points[a].scale), 0);
				int _y = detector.mBazARModels[i]->por.y0 + (int)PyrImage::convCoordf(float(detector.mBazARModels[i]->por.model_points[a].M[1]), int(detector.mBazARModels[i]->por.model_points[a].scale), 0);
                int _z = (int)PyrImage::convCoordf(detector.mBazARModels[i]->por.forest->image_width/2.f, int(detector.mBazARModels[i]->por.model_points[a].scale), 0);

				ofCircle( 420+_x, (i*55)+_y, 2 );
			}
			
			
			detector.mBazARModels[i]->mImage.draw(338, i*55, 50, 50);
    
			ofSetColor(255,255,255);

		} else {
			detector.mBazARModels[i]->mImage.draw(338, i*55, 50, 50);
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if (key == 'c') {
		detector.create_new_classifier();
	} else if (key == 's') {
		vidGrabber.videoSettings();
	}
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
void testApp::mouseReleased(int x, int y, int button){

}
