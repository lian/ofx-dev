#ifndef OFX_TOUCHADAPTIVEFILTER
#define OFX_TOUCHADAPTIVEFILTER

#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxTouchFilter.h"


class ofxTouchAdaptiveFilter : public ofxTouchFilter {
  public:
  
    int cwidth;
    int cheight;   
	int threshold;
	bool bLearnBakground;     
    
    ofxCvFloatImage  floatBgImg;    
    ofxCvGrayscaleImage  grayBgImg;    

           
    
    void allocate( int w, int h ) {
        cwidth = w;
        cheight = h;
        threshold = 60;
        bLearnBakground = true;
        floatBgImg.allocate( cwidth,cheight );
        grayBgImg.allocate( cwidth,cheight );
    }
        
    
    void process( ofxCvGrayscaleImage& img ) {
        
        if( bLearnBakground ) {
            floatBgImg = img;
            bLearnBakground = false;
        } else {
            floatBgImg.addWeighted( img, 0.01);
        }

        grayBgImg = floatBgImg;
        img.absDiff( grayBgImg );
        img.blur( 11 );
        img.threshold( threshold );
    }
    
    
    void draw() {
        floatBgImg.draw( 20,280 );
        
        ofDrawBitmapString( "[space] to learn background\n[+]/[-] to adjust threshold", 
                            20,510 );
    }
    
    
    void keyPressed( int key ) {
        switch (key){
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
  
};


#endif
