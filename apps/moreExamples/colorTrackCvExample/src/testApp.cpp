#include "testApp.h"

int xPosition(int pixelNum, int h, int w){
	int normalizedPixels = pixelNum/3;
	return normalizedPixels % w;
}

int yPosition(int pixelNum, int h, int w){
	int normalizedPixels = pixelNum/3;
	int temp = pixelNum % w;
	return (normalizedPixels - temp)/w;
}
//--------------------------------------------------------------
void testApp::setup(){	 
	vidGrabber0.setVerbose(true);
	vidGrabber0.listDevices();
	vidGrabber0.setDeviceID(3);
	vidGrabber1.setDeviceID(4);
	vidGrabber0.initGrabber(320,240);		
	vidGrabber1.initGrabber(320,240);
	colorImg0.allocate(320,240);
	colorImg1.allocate(320,240);
	posterized.allocate(320,240);
	
	cTracker0.findColor(160,160,0);
	cTracker1.findColor(160,160,0);
	cTracker0.setTolerance(60);
	cTracker1.setTolerance(60);
	
	//threshold = 80;
	xAvg = 0;
	yAvg = 0;

}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
	vidGrabber0.grabFrame();
	vidGrabber1.grabFrame();
	if (vidGrabber0.isFrameNew()){
		colorImg0.setFromPixels(vidGrabber0.getPixels(), 320,240);
		cTracker0.update(colorImg0);
		/*
		int tolerance = 40;
		unsigned char * pixels = colorImg0.getPixels();
		int totalPixels = colorImg0.width *colorImg0.height * 3; 
		int thisPixel[3];
		
		int targetRGB[3] = {160,160,0};//{235,91,21};
		
		stack<int> xes;
		stack<int> yes;
		
		long xTotal = 0;
		long yTotal = 0;
		int j = 0;
		
		for(int i = 0; i < totalPixels; i++){
			pixels[i] = floor(pixels[i] / threshold);
			pixels[i] *= threshold;
			thisPixel[i%3] = pixels[i];
			
			if(i%3 == 2){
				int brightness = (thisPixel[0] + thisPixel[1] + thisPixel[2])/3;
				int totalDiff = abs(targetRGB[0] - thisPixel[0]) + abs(targetRGB[1] - thisPixel[1]) + abs(targetRGB[2] - thisPixel[2]);
				if(totalDiff < tolerance){
					pixels[i] = 255;
					pixels[i-1] = 255;
					pixels[i-2] = 255;
					int tempX = xPosition(i+1, colorImg0.height, colorImg0.width);
					int tempY = yPosition(i+1, colorImg0.height, colorImg0.width);
					
					xTotal += tempX;
					yTotal += tempY;
					j++;
				}
			}
			
		}
		
		if( j < 1){
			j++;
		}

		if(j > 30){
			xAvg = (xTotal/j);
			yAvg = (yTotal/j);
		}
		
	
		float xPos = (xAvg/colorImg0.width);
		float yPos = (yAvg/colorImg0.height);
		
		xAvg = xPos;
		yAvg = yPos;
		
		colorImg0.setFromPixels(pixels,320,240);
		
		*/
		
		
		//cTracker0.update(colorImg0);
		//cout << 1;
	}
	
	if (vidGrabber1.isFrameNew()){
		colorImg1.setFromPixels(vidGrabber1.getPixels(), 320,240);
		cTracker1.update(colorImg1);
		//cout << 2;
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0xffffff);
	//colorImg0.draw(20,20);
	//draw the two cameras (for debugging)
	vidGrabber0.draw(680, 630, 160,120);
	vidGrabber1.draw(860, 630, 160,120);
	
	
	
	/*
	ofSetColor(255,0,0);
	ofEllipse(cTracker0.getX() * 1024, cTracker0.getY() * 768, 20, 20);
	ofSetColor(0,255,0);
	ofEllipse(cTracker1.getX() * 1024, cTracker1.getY() * 768, 20, 20);
	*/
	
	
	ofSetColor(0,0,255);
	int biggestBall = 300;
	ofEllipse(cTracker0.getX() * 1024, cTracker0.getY() * 768, biggestBall * (1-cTracker1.getX()), biggestBall * (1-cTracker1.getX()));
	

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case 's':
			vidGrabber0.videoSettings();
			break;
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
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
