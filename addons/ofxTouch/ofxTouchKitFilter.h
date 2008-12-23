#ifndef OFX_TOUCHKITFILTER
#define OFX_TOUCHKITFILTER

#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxPoint2f.h"


class ofxTouchKitFilter {
  public:
  
    int cwidth;
    int cheight;
	int threshold;
	bool bLearnBakground;     
    
    ofxCvGrayscaleImage  grayBg;
    ofxCvGrayscaleImage  grayBlurred;
    ofxCvGrayscaleImage  grayBgDiff;
    ofxCvGrayscaleImage  grayBlurDiff;
    
    ofxPoint2f pMTop;
    ofxPoint2f pMMid;
    ofxPoint2f pRTop;
    ofxPoint2f pRMid;
    ofxPoint2f pRBottom;
       
    
    
    void allocate( int w, int h ) {
        cwidth = w;
        cheight = h;
        threshold = 60;
        bLearnBakground = true;
        grayBg.allocate( cwidth,cheight );
        grayBlurred.allocate( cwidth,cheight );
        grayBgDiff.allocate( cwidth,cheight );
        grayBlurDiff.allocate( cwidth,cheight );
        
        pMTop.set( 360,20 );
        pMMid.set( 360,280 );
        pRTop.set( 700,20 );
        pRMid.set( 700,280 );
        pRBottom.set( 700,600 );
    }
        
    
    void process( ofxCvGrayscaleImage& img ) {
        /*
        if( bLearnBakground == true ) {
            grayBg = src;
            bLearnBakground = false;
        }

        grayBgDiff.absDiff(grayBg, src);
        //grayBgDiff.blurCheap();
        grayBgDiff.threshold(threshold);

        grayBlurred = src;
        //grayBlurred = grayBgDiff;
        grayBlurred.blur( 33 );
                
        grayBlurDiff.absDiff(grayBlurred, src);
        grayBlurDiff.blur( 3 );
        grayBlurDiff.threshold(threshold-5);

        dst = grayBlurDiff;
        dst &= grayBgDiff;
        dst.blur( 3 );
        dst.threshold(20);
        */
        
        if( bLearnBakground ) {
            grayBg = img;
            bLearnBakground = false;
        }    

        img.absDiff( grayBg );
        img.blur( 11 );
        img.threshold( threshold );
    }
    
    
    void draw() {
        grayBg.draw( 20,280 );
        grayBlurred.draw( 20,280 );
        grayBgDiff.draw( pRTop.x,pRTop.y, cwidth,cheight );
        grayBlurDiff.draw( pRMid.x,pRMid.y, cwidth,cheight );
        
        // REPORT
        ofSetColor( 0xffffff );
        ostringstream docstring;
        docstring << "bg subtraction and blob detection" << endl
                  << "press ' ' to capture bg" << endl
                  << "threshold " <<  threshold << " (press: +/-) " << endl;
        ofDrawBitmapString( docstring.str(), 360,600 );
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
