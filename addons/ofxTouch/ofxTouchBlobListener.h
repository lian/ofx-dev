#ifndef OFX_TOUCHBLOBLISTENER
#define OFX_TOUCHBLOBLISTENER


class ofxTouchBlobListener {
  public:
  
    virtual void blobMoved( int x, int y, int id, int order ) = 0;    
    virtual void blobOn( int x, int y, int id, int order ) = 0;
    virtual void blobOff( int x, int y, int id, int order ) = 0;
    
};


#endif