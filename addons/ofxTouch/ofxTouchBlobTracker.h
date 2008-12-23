/*
* ofCvBlobTracker.h
* by stefanix
* Thanks to touchlib for the best fit algorithm!
*
* This class tracks blobs between frames.
* Most importantly it assignes persistent id to new blobs, correlates
* them between frames and removes them as blobs dissappear. It also
* compensates for ghost frames in which blobs momentarily dissappear.
*
* Based on the trackning it fires events when blobs come into existence,
* move around, and disappear. The object which receives the callbacks
* can be specified with setListener().
*
*/


#ifndef OFX_TOUCH_BLOBTRACKER
#define OFX_TOUCH_BLOBTRACKER

#include <map>
#include <vector>
#include "ofMain.h"
#include "ofxTouchTrackedBlob.h"
#include "ofxTouchBlobListener.h"




class ofxTouchBlobTracker {


  public:
  
    vector<ofxTouchTrackedBlob>  blobs;    
    
    
    ofxTouchBlobTracker();
    void setListener( ofxTouchBlobListener* _listener );
    void trackBlobs( const vector<ofxTouchBlob>& blobs );
    int findOrder( int id );  // order by which the present 
                              // blobs came into existence
    ofxTouchTrackedBlob& getById( int id );  // returns a reference to the
                                         // corresponding blob in blobs vector
    void draw( float x, float y );  // draws all blobs



  protected:
  
    int currentID;
    int extraIDs;
    int numcheck;
    
    ofxTouchBlobListener* listener;

    int reject_distance_threshold;
    int ghost_frames;
    float minimumDisplacementThreshold;

    vector<vector<int> > matrix;
    vector<int> ids;
    vector<vector<ofxTouchTrackedBlob> > history;
    
    
    void doBlobOn( const ofxTouchTrackedBlob& b );    
    void doBlobMoved( const ofxTouchTrackedBlob& b );    
    void doBlobOff( const ofxTouchTrackedBlob& b );    
    
    inline void permute( int k );
    inline bool checkValid( int start );
    inline bool checkValidNew( int start );    
};



#endif

