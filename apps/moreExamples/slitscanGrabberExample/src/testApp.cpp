#include "testApp.h"
// -.-.-.-
struct Portion {

    int x;
    int y;
    
    int w; 
    int h;
    int size;
    
};
// -.-.-.-

//--------------------------------------------------------------
void testApp::setup(){	 
	imgW = 320;
    imgH = 240;
    imgColors = 3;
    
    nRecorded = 0;
    
    nFramesToRecord = 40;
    
	nPortions = 10;

    maxFramesToRecord = 1000;
    maxPortions = imgH; // we can't have more portions than vertical pixels
    
    // if you want to render the slitscan bigger...
    zoom = 1;
	
	reverse = false;
    
    // video buffer --------------------------------------------------------

    videoData = new unsigned char *[maxFramesToRecord];
    for (int i = 0; i < maxFramesToRecord; i++){
        videoData[i] = new unsigned char[imgW*imgH*imgColors];
    }
	
	slitData = new unsigned char *[maxFramesToRecord];
    for (int i = 0; i < maxFramesToRecord; i++){
        slitData[i] = new unsigned char[imgW*imgH*imgColors];
    }





    //portions ---------------------------------------------------------------
    strPortions = new Portion * [maxPortions];

    for (int i = 0; i < maxPortions; i++){
        strPortions[i]     = new Portion;
        strPortions[i]->w  = imgW;
        
    }

        
	vid.setVerbose(true);
	vid.initGrabber(imgW,imgH);
	delayed.allocate(imgW, imgH, GL_RGB);

    verdana.loadFont("verdana.ttf",8, false, true);
	
	// monoTex
	slitPx = new unsigned char [imgW * imgH * imgColors];
	slitTex.allocate(imgW, imgH, GL_RGB);
	
	// horiz ----
	horizPw = 20;
	horizPh = 240;
	horizP = new unsigned char [imgW*imgH*imgColors];
	horizPtex.allocate(imgW, imgH, GL_RGB);
	
}
//--------------------------------------------------------------
void testApp::update(){
// capture the frame ++++++++++++++++++++++++++++++++++++++
    vid.grabFrame();

	if (vid.isFrameNew()){
		
		//unsigned char * currentPixels = ;
        // for every frame, we save the current one to videoData
		memcpy(videoData[nRecorded], vid.getPixels(), imgW*imgH*imgColors);
		// portion size +++++++++++++++++++++++++++++++++++++++++++++++    
		pW = imgW;
		pH = imgH / nPortions;


		// to fill the whole img height... 
		// if we have a remainder, we'll have to share it up between portions
		pMod = imgH % nPortions;
		
			
		int tempY    = imgH;
		int posInImg;
		//posInImg = imgW * imgH * imgColors; 
		if (!reverse) 
			posInImg = 0;
		else 
			posInImg = imgW * imgH * imgColors;	
		
		int tempSize, tempH;
		
		// delay in frames between portions
		
		int frameDiff =  (nFramesToRecord / nPortions); //  this is reversed so it goes from bottom to top.
		int portionFrame;		
		for (int i = 0; i < nPortions; i ++) {
			tempH = pH;
			// remainder correction. 
			if (pMod > 0) {
				tempH ++;
				pMod--;
			}
			
			tempSize  = pW * tempH * imgColors;
			
			// which frame of the videoData are we going to use for this portion?
			portionFrame = (nRecorded - (i*frameDiff))%nFramesToRecord;
			if (portionFrame < 0) portionFrame = nFramesToRecord +portionFrame;

			if (!reverse) {
				memcpy(slitPx + posInImg  , videoData[portionFrame]+  (posInImg), tempSize);			
				posInImg += tempSize;
			} else {
				posInImg -= tempSize;
				memcpy(slitPx + posInImg  , videoData[portionFrame]+  (posInImg), tempSize);
			}
			
			// horiz.
			horizPw = imgW/nPortions;
			for (int j = 0; j < horizPh; j++) {
				memcpy((horizPw*i *3) + horizP + j *imgW * 3, (horizPw*i *3) +videoData[portionFrame]+ j*imgW*3, horizPw * 3); 
				//memcpy((horizPw*i *3) + horizP + j *imgW * 3, (horizPw*i *3) +slitData[portionFrame]+ j*imgW*3, horizPw * 3);  
			}
			memcpy(slitData[nRecorded], slitPx, imgW*imgH*imgColors);
		
		}
		
		
		
		slitTex.loadData(slitPx, imgW, imgH, GL_RGB);
		horizPtex.loadData(horizP, imgW, imgH, GL_RGB);

		nRecorded++;
		nRecorded %= nFramesToRecord;

		
		
	}
	
	
    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(230,230,255);
	
	ofBackground(1,1,1);
    
    // draw the preview
	vid.draw(10,10,320,240);
    /*
    for (int i = 0; i < nPortions; i ++) {
        strPortions[i]->tex.draw(340, 10 + strPortions[i]->y * zoom, pW*zoom, strPortions[i]->h* zoom);
    }
	*/
    slitTex.draw( 20, 260, imgW*zoom, imgH*zoom);
		
    char tempString[255];
	sprintf(tempString,"[ +/- ] --> portions: %i             \n[ a/z ] --> frames in buffer: %i   \n[ s/x ] --> zoom: %i               ", nPortions, nFramesToRecord, zoom);    
    
    ofDrawBitmapString(tempString ,340 ,40);
	
	horizPtex.draw((imgW+20)*zoom, 260,imgW*zoom, imgH*zoom);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	// portions
    if (key=='+') {
        if (nPortions < maxPortions && nPortions < nFramesToRecord) {
            nPortions++;
        }
	}   
	 
    if (key=='-') {
        if (nPortions > 1) {
            nPortions--;
        }
    }

    // frames
    if (key == 'a') {
        if (nFramesToRecord < maxFramesToRecord) {
            nFramesToRecord++;
        }
    }

    if (key == 'z') {
        if (nFramesToRecord >nPortions) {
            nFramesToRecord--;
        }
    }
    
    // zoom
    if (key == 's') {
        if (zoom < 5) {
            zoom ++;
        }
        
    }

    if (key == 'x') {
        if (zoom > 1) {
            zoom --;
        }
    }
	if (key == 'r') {
		reverse = !reverse;
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
