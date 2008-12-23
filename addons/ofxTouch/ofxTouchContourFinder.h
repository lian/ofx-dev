/*
* ofxTouchContourFinder.h
*
* Finds white blobs in binary images and identifies 
* centroid, bounding box, area, length and polygonal contour
* The result is placed in a vector of ofCvBlob objects. 
*
*/

#ifndef OFX_TOUCH_CONTOURFINDER
#define OFX_TOUCH_CONTOURFINDER


#include "ofMain.h"
#include "ofxCvMain.h"
#include "ofxTouchBlob.h"


#define  OFX_TOUCH_MAX_CONTOURS   128         // alther this if you think you will 
                                              // be looking for more....
#define  OFX_TOUCH_MAX_CONTOUR_LENGTH   1024  // alther this if you think your 
                                              // contours will be longer than this


class ofxTouchContourFinder {

  public:
		
    vector<ofxTouchBlob> blobs;
    
    
    ofxTouchContourFinder();
    ~ofxTouchContourFinder();
    void findContours( ofxCvGrayscaleImage& input,
                       int minArea, int maxArea,
                       int nConsidered, bool bFindHoles );
    void draw( float x, float y );
    
    
  protected:
  
    ofxCvGrayscaleImage  inputCopy;
    CvMemStorage*  contour_storage;
    CvMemStorage*  storage;
    CvMoments*  myMoments;

    int nCvSeqsFound;
    CvSeq*  cvSeqBlobs[OFX_TOUCH_MAX_CONTOURS];
  
  
    void reset();  
    
};



#endif
