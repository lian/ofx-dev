#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	videoAsInputSource = true;

	// Video grabber
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);

    staticImage.loadImage("image.jpg");
    
	// Allocations
    colorImg.allocate(staticImage.width, staticImage.height);				// Static Image as imput source
	colorImg.allocate(vidGrabber.width, vidGrabber.height);					// Live Cam as input source
    colorImgHSV.allocate(vidGrabber.width, vidGrabber.height);				// HSV Image
    hueImg.allocate(vidGrabber.width, vidGrabber.height);					// Hue Image
    satImg.allocate(vidGrabber.width, vidGrabber.height);					// Saturation Image
    valImg.allocate(vidGrabber.width, vidGrabber.height);					// value Image

    colorTrackedPixels = new unsigned char [vidGrabber.width * vidGrabber.height];	// Tracked Image
    trackedTexture.allocate(vidGrabber.width, vidGrabber.height, GL_LUMINANCE);

	// HSV variables. by default track red color.
	hue = 0.0;
	hueWidth = 0.06;
	sat = 0.62;
	satWidth = 0.94;
	val = 0.8;
	valWidth = 0.62;
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

	vidGrabber.grabFrame();
	if (vidGrabber.isFrameNew()){
	
		//Calculate min and max thersholds values
		minHue = max((hue - hueWidth*0.5) * 255, 0.0);
		maxHue = min((hue + hueWidth*0.5) * 255, 255.0);
		minSat = max((sat - satWidth*0.5) * 255, 0.0);
		maxSat = min((sat + satWidth*0.5) * 255, 255.0);
		minVal = max((val - valWidth*0.5) * 255, 0.0);
		maxVal = min((val + valWidth*0.5) * 255, 255.0);
	
		// Live video or Static image: input source
		if(videoAsInputSource){
			colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.width, vidGrabber.height);	
		}else{
			colorImg.setFromPixels(staticImage.getPixels(), staticImage.width, staticImage.height);
		}
		
		// HSV
		colorImgHSV = colorImg;
		colorImgHSV.convertRgbToHsv();
		colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, valImg);
	
		// Perform tracking calculations
		unsigned char * huePixels = hueImg.getPixels();
		unsigned char * satPixels = satImg.getPixels();
		unsigned char * valPixels = valImg.getPixels();
		int nPixels = vidGrabber.width * vidGrabber.height;
	
		for (int i = 0; i < nPixels; i++){
			if ((huePixels[i] >= minHue && huePixels[i] <= maxHue) &&
				(satPixels[i] >= minSat && satPixels[i] <= maxSat) &&
				(valPixels[i] >= minVal && valPixels[i] <= maxVal)){
				colorTrackedPixels[i] = 255;
			} else {
				colorTrackedPixels[i] = 0;
			}
		}
		trackedTexture.loadData(colorTrackedPixels, vidGrabber.width, vidGrabber.height, GL_LUMINANCE);
	
	// ******Laser
	LT.calcColorRange(hue, hueWidth, sat, satWidth, val);	
	}

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0xffffff);
	
	// Draw Input source
	ofDrawBitmapString("Input source:", 20, 20);
	colorImg.draw(20, 25);						 
	
	// Draw HSV texture
	ofDrawBitmapString("Input source converted to HSV:", 20, vidGrabber.height+45);	
	colorImgHSV.draw(20, vidGrabber.height+50);

	// Processed image: Tracked Texture
	ofDrawBitmapString("Result of HSV adjustments. Tracked texture:", vidGrabber.width+40, 20);	
	trackedTexture.draw(vidGrabber.width+40, 25);

	LT.drawColorRange(vidGrabber.width+40, vidGrabber.height+50, 120, 44);
	ofSetColor(0xffffff);	
	ofDrawBitmapString("hue: " + ofToString(hue) + "('a', 'z')", vidGrabber.width+40, vidGrabber.height+120);
	ofDrawBitmapString("hue width: " + ofToString(hueWidth) + "('s', 'x')", vidGrabber.width+40, vidGrabber.height+135);
	ofDrawBitmapString("saturation: " + ofToString(sat) + "('d', 'c')", vidGrabber.width+40, vidGrabber.height+150);
	ofDrawBitmapString("saturation width: " + ofToString(satWidth) + "('f', 'v')", vidGrabber.width+40, vidGrabber.height+165);
	ofDrawBitmapString("value: " + ofToString(val) + "('g', 'b')", vidGrabber.width+40, vidGrabber.height+180);
	ofDrawBitmapString("value width: " + ofToString(valWidth) + "('h', 'n')", vidGrabber.width+40, vidGrabber.height+195);
	ofDrawBitmapString("minHue: " + ofToString(minHue), vidGrabber.width+40, vidGrabber.height+210);
	ofDrawBitmapString("maxHue: " + ofToString(maxHue), vidGrabber.width+40, vidGrabber.height+225);
	ofDrawBitmapString("minSat: " + ofToString(minSat), vidGrabber.width+40, vidGrabber.height+240);
	ofDrawBitmapString("maxSat: " + ofToString(maxSat), vidGrabber.width+40, vidGrabber.height+255);
	ofDrawBitmapString("minVal: " + ofToString(minVal), vidGrabber.width+40, vidGrabber.height+270);
	ofDrawBitmapString("maxVal: " + ofToString(maxVal), vidGrabber.width+40, vidGrabber.height+285);

	ofDrawBitmapString("Switch video/image input: 'i'", vidGrabber.width+40, vidGrabber.height+310);
	ofDrawBitmapString("Video Configuration-preferences: 'p'", vidGrabber.width+40, vidGrabber.height+325);	
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key){
		case 'a':
			hue = min(hue + 0.02, 1.0);
			break;
		case 'z':
			hue = max(hue - 0.02, 0.0);
			break;
		case 's':
			hueWidth = min(hueWidth + 0.02, 1.0);
			break;
		case 'x':
			hueWidth = max(hueWidth - 0.02, 0.0);
			break;
		case 'd':
			sat = min(sat + 0.02, 1.0);
			break;
		case 'c':
			sat = max(sat - 0.02, 0.0);
			break;
		case 'f':
			satWidth = min(satWidth + 0.02, 1.0);
			break;
		case 'v':
			satWidth = max(satWidth - 0.02, 0.0);
			break;
		case 'g':
			val = min(val + 0.02, 1.0);
			break;
		case 'b':
			val = max(val - 0.02, 0.0);
			break;
		case 'h':
			valWidth = min(valWidth + 0.02, 1.0);
			break;
		case 'n':
			valWidth = max(valWidth - 0.02, 0.0);
			break;
		case 'i':
			if(videoAsInputSource){
				videoAsInputSource = false;
			}else{
				videoAsInputSource = true;
			}
			break;
		case 'p':
			vidGrabber.videoSettings();
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
