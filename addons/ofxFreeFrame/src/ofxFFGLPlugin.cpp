#include "ofxFFGLPlugin.h"

//----------------------------------------------------------
ofxFFGLPlugin::ofxFFGLPlugin() {
    active = false;
}

//----------------------------------------------------------
ofxFFGLPlugin::~ofxFFGLPlugin() {
    // XXXBUG Gets called at the beginning (probably when ofxFFGLHost::loadPlugin(...) returns
    // XXXBUG Uncommenting the following 2 lines fucks everything up
    //ffPlugin->DeInstantiateGL();
    //ffPlugin->Unload();
}

//----------------------------------------------------------
bool ofxFFGLPlugin::load(const char* filename, FFGLViewportStruct* viewport, FFGLExtensions* extensions) {
    // load FFGL plugin
    ffPlugin = FFGLPluginInstance::New();

#ifdef TARGET_WIN32
    string path = ofToDataPath(filename);
    printf("ofxFFGLplugin Win32 : Loading ... %s\n",path.c_str());
#endif

#ifdef TARGET_OSX
    string path = ofToDataPath(filename)+".bundle/Contents/MacOS/"+filename;
    printf("ofxFFGLplugin OSX : Loading ... %s\n",path.c_str());
#endif

#ifdef TARGET_LINUX
    string path = ofToDataPath(filename);//+".bundle/Contents/Linux/"+filename;
    printf("ofxFFGLplugin Linux : Loading ... %s\n",path.c_str());
#endif

    if (ffPlugin->Load(path.c_str()) == FF_FAIL) {
        printf("ERROR opening plugin %s. File not found?\n", path.c_str());
        return false;
    }

    // allocate FBO
    if (!fbo.Create(viewport->width, viewport->height, *extensions)) {
        printf("ERROR initializing FBO for plugin %s.\n", filename);
        return false;
    }

    // instantiate GL for plugin
    if (ffPlugin->InstantiateGL(viewport) != FF_SUCCESS) {
        printf("ERROR instantiating GL for plugin %s.\n", filename);
        return false;
    }

    return true;
}

//----------------------------------------------------------
FFGLTextureStruct ofxFFGLPlugin::process(FFGLTextureStruct inputTexture, FFGLViewportStruct* viewport, FFGLExtensions* extensions) {
    // activate the FBO as our render target
    if (!fbo.BindAsRenderTarget(*extensions)) {
        printf("ERROR binding FBO as render target.\n");
        return inputTexture;
    }

    //set the gl viewport to equal the size of the FBO
    glViewport(viewport->x, viewport->y, viewport->width, viewport->height);

    // make sure all the matrices are reset
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // clear the depth and color buffers
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // prepare the structure used to call the plugin's ProcessOpenGL method
    ProcessOpenGLStructTag processStruct;

    //create the array of FFGLTextureStruct* to be passed to the plugin (only one though...)
    FFGLTextureStruct* inputTextures[1];
    inputTextures[0] = &inputTexture;

    // provide the 1 input texture we allocated above
    processStruct.numInputTextures = 1;
    processStruct.inputTextures = inputTextures;

    // specify our FBO's handle in the ProcessOpenGLStructTag
    processStruct.HostFBO = fbo.GetFBOHandle();

    // call the plugin's ProcessOpenGL
    if (ffPlugin->CallProcessOpenGL(processStruct) != FF_SUCCESS) {
        // the plugin call failed
        printf("ERROR running ProcessOpenGL.\n");
        return inputTexture;
    }

    // deactivate rendering to the fbo
    // (this re-activates rendering to the window)
    fbo.UnbindAsRenderTarget(*extensions);

    // return the output texture
    return fbo.GetTextureInfo();
}

//----------------------------------------------------------
void ofxFFGLPlugin::setTime(float elapsedTime) {
    ffPlugin->SetTime(elapsedTime);
}

//----------------------------------------------------------
void ofxFFGLPlugin::setFloatParameter(int paramNum, float value) {
    ffPlugin->SetFloatParameter(paramNum, value);
}

//----------------------------------------------------------
void ofxFFGLPlugin::setActive(bool val) {
    active = val;
}

//----------------------------------------------------------
bool ofxFFGLPlugin::isActive() {
    return active;
}

//----------------------------------------------------------
GLuint ofxFFGLPlugin::getFBOHandle() {
    return fbo.GetFBOHandle();
}
