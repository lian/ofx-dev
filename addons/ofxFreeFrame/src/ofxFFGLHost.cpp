#include "ofxFFGLHost.h"

//----------------------------------------------------------
ofxFFGLHost::ofxFFGLHost() {
    inputPixels = NULL;
	outputPixels = NULL;
	outputPixelsPow2 = NULL;
    
    // init gl extensions
    glExtensions.Initialize();
    if (glExtensions.EXT_framebuffer_object == 0) {
        printf("ERROR: FBO support not detected, cannot continue!\n");
        return;
    }
    
    // this seems necessary to render FF plugins...
    textureTarget = GL_TEXTURE_2D;
}

//----------------------------------------------------------
ofxFFGLHost::~ofxFFGLHost() {
    /*vector<ofxFFGLPlugin>::iterator curr;
	// go through all the plugins
    for (curr = plugins.begin(); curr != plugins.end(); curr++) {
        //delete &curr;
        //plugins.erase(curr);
    }
    //plugins.clear();*/
    
    delete [] inputPixels;
    delete [] outputPixels;
    delete [] outputPixelsPow2;
}

//----------------------------------------------------------
void ofxFFGLHost::allocate(int w, int h, int internalGlDataType){
    // allocate the GPU texture
    
    //---------------------------------------------------------------------------------------------
    // begin ofTexture::allocate(...)
    
	// 	can pass in anything (320x240) (10x5)
	// 	here we make it power of 2 for opengl (512x256), (16x8)
    
	//if (GLEE_ARB_texture_rectangle){
	//	tex_w = w;
	//	tex_h = h;
	//} else {
    tex_w = ofNextPow2(w);
    tex_h = ofNextPow2(h);
	//}
    
	//if (GLEE_ARB_texture_rectangle){
	//	tex_t = w;
	//	tex_u = h;
	//} else {
    tex_t = 1.0f;
    tex_u = 1.0f;
	//}
    
    // attempt to free the previous bound texture, if we can:
	clear();
    
    glGenTextures(1, (GLuint *)textureName);   // could be more then one, but for now, just one
    
	glEnable(textureTarget);
    
    glBindTexture(textureTarget, (GLuint)textureName[0]);
    glTexImage2D(textureTarget, 0, internalGlDataType, tex_w, tex_h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0);  // init to black...
    glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
	glDisable(textureTarget);
    
	width = w;
	height = h;
	bFlipTexture = false;
    
    // end ofTexture::allocate(...)
    //---------------------------------------------------------------------------------------------
    
    // allocate CPU memory
    if (internalGlDataType == GL_LUMINANCE) {
        // 8-bit A
        inputPixels = new unsigned char[w*h];
		outputPixels = new unsigned char[w*h];
		outputPixelsPow2 = new unsigned char[tex_w*tex_h];
    } else if (internalGlDataType == GL_RGB) {
        // 24-bit RGB
        inputPixels = new unsigned char[w*h*3];
		outputPixels = new unsigned char[w*h*3];
		outputPixelsPow2 = new unsigned char[tex_w*tex_h*3];
    } else if (internalGlDataType == GL_RGBA) {
        // 32-bit RGBA
        inputPixels = new unsigned char[w*h*4];
		outputPixels = new unsigned char[w*h*4];
		outputPixelsPow2 = new unsigned char[tex_w*tex_h*4];
    } else {
        printf("ERROR: GL data type not recognized.\n");
        return;
    }
    
    totalPixels = tex_w*tex_h*3;
	crapPixels = (tex_w-width)*3;
    
    // init the inputTexture struct
    FFGLTextureStruct &t = inputTexture;
    t.Handle = (GLuint)textureName[0];
    t.Width = w;
    t.Height = h;  
    t.HardwareWidth = tex_w;
    t.HardwareHeight = tex_h;
    
    if (inputTexture.Handle == 0 || inputPixels == NULL) {
        printf("ERROR allocating texture.\n");
        return;
    }
    
    // init the fboViewport struct
    fboViewport.x = 0;
    fboViewport.y = 0;
    fboViewport.width = width;
    fboViewport.height = height;
}

//----------------------------------------------------------
void ofxFFGLHost::loadData(unsigned char* data, int w, int h, int glDataType) {
    inputPixels = data;
    
    //---------------------------------------------------------------------------------------------
    // begin ofTexture::loadData(...)
    
    //	can we allow for uploads bigger then texture and
    //	just take as much as the texture can?
    //
    //	ie:
    //	int uploadW = MIN(w, tex_w);
    //	int uploadH = MIN(h, tex_h);
    //  but with a "step" size of w?
    // 	check "glTexSubImage2D"
    
    if ( w > tex_w || h > tex_h) {
        printf("image data too big for allocated texture. not uploading... \n");
        return;
    }
    
    width 	= w;
    height 	= h;
    
    //compute new tex co-ords based on the ratio of data's w, h to texture w,h;
    //if (GLEE_ARB_texture_rectangle){
    //    tex_t = w;
    //    tex_u = h;
    //} else {
    tex_t = (float)(w) / (float)tex_w;
    tex_u = (float)(h) / (float)tex_h;
    //}
    
    // 	ok this is an ultra annoying bug :
    // 	opengl texels and linear filtering -
    // 	when we have a sub-image, and we scale it
    // 	we can clamp the border pixels to the border,
    //  but the borders of the sub image get mixed with
    //  neighboring pixels...
    //  grr...
    //
    //  the best solution would be to pad out the image
    // 	being uploaded with 2 pixels on all sides, and
    //  recompute tex_t coordinates..
    //  another option is a gl_arb non pow 2 textures...
    //  the current hack is to alter the tex_t, tex_u calcs, but
    //  that makes the image slightly off...
    //  this is currently being done in draw...
    //
    // 	we need a good solution for this..
    //
    //  http://www.opengl.org/discussion_boards/ubb/ultimatebb.php?ubb=get_topic;f=3;t=014770#000001
    //  http://www.opengl.org/discussion_boards/ubb/ultimatebb.php?ubb=get_topic;f=3;t=014770#000001
    
    //------------------------ likely, we are uploading continuous data
    GLint prevAlignment;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // update the texture image:
    glEnable(textureTarget);
    glBindTexture(textureTarget, inputTexture.Handle);
    glTexSubImage2D(textureTarget,0,0,0,w,h,glDataType,GL_UNSIGNED_BYTE,data);
    glDisable(textureTarget);
    
    //------------------------ back to normal.
    glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);    
    
    bFlipTexture = false;
    
    // end ofTexture::loadData(...)
    //---------------------------------------------------------------------------------------------
}

//----------------------------------------------------------
void ofxFFGLHost::process() {
    float elapsedTime = ofGetElapsedTimef();
    
    // go through all the plugins
    nextTexture = inputTexture;
	for (int i=0; i < plugins.size(); i++) {
        plugins[i].setTime(elapsedTime);
        if (plugins[i].isActive()) {
            // process the plugin
            // use the resulting texture of the previous operation
            nextTexture = plugins[i].process(nextTexture, &fboViewport, &glExtensions);
        }
    }
}

//----------------------------------------------------------
void ofxFFGLHost::draw(float x, float y, float w, float h) {
    textureName[0] = nextTexture.Handle;
    ofTextureBak::draw(x, y, w, h);
}

//----------------------------------------------------------
unsigned char* ofxFFGLHost::getPixels() {
    glBindTexture(GL_TEXTURE_2D, nextTexture.Handle);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, outputPixelsPow2);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// only grab the relevant pixels
	int currY = 0;
	int i=0; int j=0;
	while (j < totalPixels) {
		outputPixels[i] = outputPixelsPow2[j];
		i++; j++;
		
		currY++;
		if (currY >= width*3) {
			// the rest of the line is crap, skip it
			currY = 0;
			j += crapPixels;
		}
	}
	
	return outputPixels;
}

//----------------------------------------------------------
ofxFFGLPlugin ofxFFGLHost::loadPlugin(const char* filename) {
    // create new instance
    ofxFFGLPlugin p;
    
    p.load(filename, &fboViewport, &glExtensions);
    
    // add the plugin to the list
	plugins.push_back(p);
    
    return p;
}

//----------------------------------------------------------
ofxFFGLPlugin ofxFFGLHost::getPlugin(int i) {
    return plugins[i];
}

//----------------------------------------------------------
void ofxFFGLHost::setPluginActive(int i, bool val) {
    if (plugins.size() > i)
        plugins[i].setActive(val);
}

//----------------------------------------------------------
void ofxFFGLHost::setPluginFloatParameter(int i, int j, float val) {
    if (plugins.size() > i)
        plugins[i].setFloatParameter(j, val);
}

