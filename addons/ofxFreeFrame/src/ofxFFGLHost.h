#ifndef _OFX_FFGL_HOST
#define _OFX_FFGL_HOST

#include <ofMain.h>
#include <ofTextureBak.h>

#include "ofxFFGLPlugin.h"
#include <vector>
using namespace std;

class ofxFFGLHost : public ofTextureBak {	
    public:
                                ofxFFGLHost();
                                ~ofxFFGLHost();
        
        void                    allocate(int w, int h, int internalGlDataType);
        
        void                    loadData(unsigned char* data, int w, int h, int glDataType); 
        void                    process();
        void                    draw(float x, float y, float w, float h);
        unsigned char*          getPixels();
    
        ofxFFGLPlugin           loadPlugin(const char* filename);
        ofxFFGLPlugin           getPlugin(int i);
        void                    setPluginActive(int i, bool val);
        void                    setPluginFloatParameter(int i, int j, float val);
        
    protected:
        unsigned char*          inputPixels;
        unsigned char*          outputPixels;
        unsigned char*          outputPixelsPow2;
        int                     totalPixels;
        int                     crapPixels;
            
        vector<ofxFFGLPlugin>   plugins;
        
        FFGLTextureStruct       inputTexture;
        FFGLTextureStruct       nextTexture;
        
        // OSX supports many more opengl extension directly, by including
        // <Opengl/gl_ext.h> - to be more portable to other platforms
        // (like Windows, *ahem*), this class (FFGLExtensions) is used
        // to provide a defined subset of the GL extensions to all the implementations
        // of FFGL plugins / hosts in the FFGL SDK. 
        FFGLExtensions          glExtensions;
        
        // the viewport used when rendering into the FBO        
        FFGLViewportStruct      fboViewport;  
};

#endif