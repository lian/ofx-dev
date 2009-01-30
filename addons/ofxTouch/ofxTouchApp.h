#ifndef _OFX_TOUCHAPP
#define _OFX_TOUCHAPP


// #include "ofApp.h"
#include "ofxTouchBlobListener.h"
#include "ofVideoGrabber.h"
#include "ofxTouchContourFinder.h"
#include "ofxTouchBlobTracker.h"
#include "ofxTouchAdaptiveFilter.h"



#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
                            // otherwise, we'll use a movie file



class ofxTouchApp : public ofApp, public ofxTouchBlobListener {

  public:
    
    int cwidth;
    int cheight;
    bool bDebug;    
    float camToScreenScale;
    
    #ifdef _USE_LIVE_VIDEO
      ofVideoGrabber  vidGrabber;
    #else
      ofVideoPlayer  vidPlayer;
    #endif

    ofxCvColorImage  colorImg;
    ofxCvGrayscaleImage  img;

    ofxCvGrayscaleImage  afterAcquiringImg;
    ofxCvGrayscaleImage  afterCalibratingImg;
    ofxCvGrayscaleImage  afterFilteringImg;

    ofxTouchAdaptiveFilter  filter;
    ofxTouchContourFinder  contourFinder;
    ofxTouchBlobTracker  blobTracker;
    


    virtual void assignEventHandlers() {
        using Poco::Delegate;
        using Poco::EventArgs;
        ofSetupEventManager += Delegate<ofxTouchApp, EventArgs>(this, &ofxTouchApp::_setup);
        ofUpdateEventManager += Delegate<ofxTouchApp, EventArgs>(this, &ofxTouchApp::_update);
        ofDrawEventManager += Delegate<ofxTouchApp, EventArgs>(this, &ofxTouchApp::_draw);
        ofExitEventManager += Delegate<ofxTouchApp, EventArgs>(this, &ofxTouchApp::_exit);
        ofKeyPressedEventManager += Delegate<ofxTouchApp, ofKeyEvent>(this, &ofxTouchApp::_keyPressed);
        ofKeyReleasedEventManager += Delegate<ofxTouchApp, ofKeyEvent>(this, &ofxTouchApp::_keyReleased);
        ofMouseMovedEventManager += Delegate<ofxTouchApp, ofMouseEvent>(this, &ofxTouchApp::_mouseMoved);
        ofMouseDraggedEventManager += Delegate<ofxTouchApp, ofMouseEvent>(this, &ofxTouchApp::_mouseDragged);
        ofMousePressedEventManager += Delegate<ofxTouchApp, ofMouseEvent>(this, &ofxTouchApp::_mousePressed);
        ofMouseReleasedEventManager += Delegate<ofxTouchApp, ofMouseEvent>(this, &ofxTouchApp::_mouseReleased);
    }
            
    
    virtual void _setup( const void* sender, Poco::EventArgs& event ) {
    
        cwidth = 320;
        cheight = 240;
        bDebug = false;
        camToScreenScale = ofGetWidth()/(float)cwidth;
        camFrameCount = 0;
        
        ofSetVerticalSync( true );
        //ofSetFrameRate( 60 );        

        #ifdef _USE_LIVE_VIDEO
            vidGrabber.setVerbose(true);
            vidGrabber.initGrabber(cwidth,cheight);
        #else
            vidPlayer.loadMovie("fingers.mov");
            vidPlayer.play();
        #endif
            
        colorImg.allocate(cwidth,cheight);
        img.allocate(cwidth,cheight);
        afterAcquiringImg.allocate(cwidth,cheight);
        afterCalibratingImg.allocate(cwidth,cheight);
        afterFilteringImg.allocate(cwidth,cheight);
        
        filter.allocate( cwidth, cheight );    
    
        //contourFinder.calibrator.loadSettings();
        blobTracker.setListener( this );
        
        ofHideCursor();
        
        //call setup in user app code
        setup();
    }
    


    
    virtual void _update( const void* sender, Poco::EventArgs& event ) {
        bool bNewFrame = false;
        
        #ifdef _USE_LIVE_VIDEO
           vidGrabber.grabFrame();
           bNewFrame = vidGrabber.isFrameNew();
        #else
            vidPlayer.idleMovie();
            bNewFrame = vidPlayer.isFrameNew();
        #endif
        
        if (bNewFrame){
            if( bDebug ) {
                if( (camFrameCount % 10) == 0 ) {
                    camFps = 10000.0/(ofGetElapsedTimeMillis() - camFrameStartTime);
                    camFrameStartTime = ofGetElapsedTimeMillis();
                }
                dspStartTime = ofGetElapsedTimeMillis();
            }
            
            #ifdef _USE_LIVE_VIDEO
                colorImg.setFromPixels(vidGrabber.getPixels(), cwidth,cheight);
            #else
                colorImg.setFromPixels(vidPlayer.getPixels(), cwidth,cheight);
            #endif
            
            img = colorImg;
            if( bDebug ) { afterAcquiringImg = img; }
            //calibrator.process( img );
            //if( bDebug ) { afterCalibratingImg = img; }            
            filter.process( img );
            if( bDebug ) { afterFilteringImg = img; }

            //findContures( img, minSize, maxSize, nMax, inner contours yes/no )
            contourFinder.findContours( img, 10,20000, 10, false );
            blobTracker.trackBlobs( contourFinder.blobs );
            
            if( bDebug ) {
                dspTime = ofGetElapsedTimeMillis() - dspStartTime;
                camFrameCount++;
            }
        }


        
        //call update in user app code
        update();
    
    }
    
    
    
    virtual void _draw( const void* sender, Poco::EventArgs& event ) {
        ofSetColor( 0xffffff );
        
        if( bDebug ) {
            afterAcquiringImg.draw( 20,200 );
            afterFilteringImg.draw( 360,200 );
            
            filter.floatBgImg.draw( 700,200 );            
            filter.grayBgImg.draw( 700,480 );            
            
            blobTracker.draw( 20,200 );
            
            ofDrawBitmapString( ofToString(dspTime) + "ms dsp", 
                                20, ofGetHeight()-60 ); 
            ofDrawBitmapString( ofToString(camFps) + "fps (cam)", 
                                20, ofGetHeight()-40 ); 
            ofDrawBitmapString( ofToString(ofGetFrameRate(), 2) + "fps", 
                                20, ofGetHeight()-20 );                                       
        }
        
        //call draw in user app code
        draw();
    }
    
    
    
    virtual void _exit( const void* sender, Poco::EventArgs& event ) {
        ofShowCursor();
    }
    
    
    
    virtual void _keyPressed( const void* sender, ofKeyEvent& event ) {
        //calibrator.keyPressed( key );
        filter.keyPressed( event.key );
        //contourFinder.keyPressed( key );
        //blobTracker.keyPressed( key );
        
        if( event.key == 'd' ) {
            ofxTouchSetDebug( !bDebug );
        }
        
        //call keyPressed in user app code
        keyPressed( event.key );
    }
    
    virtual void _keyReleased( const void* sender, ofKeyEvent& event ) {
        //call keyReleased in user app code
        keyReleased( event.key );
    }




    virtual void _mouseMoved( const void* sender, ofMouseEvent& event ) { 
        mouseMoved( event.x, event.y );
    }
    virtual void _mouseDragged( const void* sender, ofMouseEvent& event ) { 
        mouseDragged( event.x, event.y, event.button );
    }
    virtual void _mousePressed( const void* sender, ofMouseEvent& event ) {
        mousePressed( event.x, event.y, event.button );
    }
    virtual void _mouseReleased( const void* sender, ofMouseEvent& event ) {
        mouseReleased();
    }


    
    virtual void blobMoved( int x, int y, int id, int order ) {
        fingerDragged( x,y, id, order );    
    }   
    virtual void blobOn( int x, int y, int id, int order ) {
        fingerPressed( x,y, id, order );
    }
    virtual void blobOff( int x, int y, int id, int order ) {
        fingerReleased( x,y, id, order );    
    }
    
    
    // to be overwritten by subclass
    virtual void fingerDragged( int x, int y, int id, int order ) {}
    virtual void fingerPressed( int x, int y, int id, int order ) {}    
    virtual void fingerReleased( int x, int y, int id, int order ) {}
    
    
    
    virtual void ofxTouchSetDebug( bool _bDebug ) {
        bDebug = _bDebug;
        if( bDebug ) {
            ofShowCursor();
        } else {
            ofHideCursor();
        }
    }
    
    
    
    /*
    void drawCentroids( int x, int y, int width, int height ) {
        glPushMatrix();
        glTranslatef( x, y, 0 );
        glScalef( width/(float)cwidth, 
                  height/(float)cheight, 1 );
        
        for( int i = 0; i < contourFinder.nBlobs; i++ ) {
            glBegin( GL_POINTS );
            glVertex2f( contourFinder.blobs[i].centroid.x, 
                        contourFinder.blobs[i].centroid.y );
            glEnd();
        }
        
        glPopMatrix(); 
    }
    


    void drawContours() {
        for( int i=0; i<fingers.size(); ++i ) {
            fingers[i].drawConture();
        }
    }



    void drawNumber() {
        for( int i=0; i<fingers.size(); ++i ) {
        
            std::ostringstream order;
            order << i;
            ofDrawBitmapString( order.str(), fingers[i].box.x-10, 
                                                 fingers[i].box.y-10 );

            std::ostringstream id;
            id << fingers[i].id;
            ofDrawBitmapString( id.str(), fingers[i].box.x+fingers[i].box.width+10, 
                                          fingers[i].box.y+fingers[i].box.height+10 );
        }
    }
    */
    
    
    
    float ofRangemap(float r1min, float r1max, float r2min, float r2max, float r1val) {
      /**
      *                     r1val
      *    |- - - - -|--------x----|
      *    0       r1min       \  r1max
      *                         \
      *    |- - - - - -|---------x-------|
      *    0         r2min      return  r2max
      */
      r1val = CLAMP(r1val, r1min, r1max);
      return (r1val - r1min) * ((r2max - r2min)/(r1max - r1min)) + r2min;
    }
    
    
    
    
    
    
  private:
  
    int camFps;
    int camFrameCount;
    int camFrameStartTime;
    int dspTime;
    int dspStartTime;   

};

#endif
