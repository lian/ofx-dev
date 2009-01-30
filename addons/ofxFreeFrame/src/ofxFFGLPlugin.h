#ifndef _OFX_FFGL_PLUGIN
#define _OFX_FFGL_PLUGIN

#include <ofMain.h>
#include "FFGLFBO.h"
#include "FFGLPluginInstance.h"

class ofxFFGLPlugin {
    public:
                            ofxFFGLPlugin();
                            ~ofxFFGLPlugin();
        
        bool                load(const char* filename, FFGLViewportStruct* viewport, FFGLExtensions* extensions);
        FFGLTextureStruct   process(FFGLTextureStruct inputTexture, FFGLViewportStruct* viewport, FFGLExtensions* extensions);  
    
        void                setTime(float elapsedTime);
        void                setFloatParameter(int paramNum, float value);
        void                setActive(bool val);
        bool                isActive();
        GLuint              getFBOHandle();
        
    private:
    
        bool                active;
        FFGLPluginInstance* ffPlugin;
        FFGLFBO             fbo;
};

#endif
