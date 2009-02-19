/**
 * File:          $RCSfile: openGL_texture.h,v $
 * Module:        Display images using Open GL
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.17 $
 * Last edited:   $Date: 2006/07/27 12:04:27 $
 * Author:        $Author: nicolas $

 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _GAN_OPENGL_TEXTURE_H
#define _GAN_OPENGL_TEXTURE_H

#include <gandalf/image/image_defs.h>

#ifdef HAVE_OPENGL

#ifdef WIN32
        #include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#ifdef HAVE_OPENGL_EXT
#include <GL/glext.h>
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageDisplay
 * \{
 */

/**
 * \brief Structure holding information on OpenGL textures
 */
typedef struct OpenGLTextureStruct
{
   int iTextureTileSize, iNumberOfTilesV, iNumberOfTilesH, iNumberOfTiles;
   GLuint *agluiTexture;

  
   Gan_Vector2_i *av2iTilePosition;
   GLenum eTextureMode;

#ifdef HAVE_OPENGL_EXT
#ifdef GL_ARB_shader_objects
   GLhandleARB PHandle;
   GLuint *agluiBuffer;
#endif
#endif /* #ifdef HAVE_OPENGL_EXT */

   Gan_Bool bEnableBlending;
} Gan_OpenGLTextureStruct;

#if defined(HAVE_OPENGL_EXT) && defined(GL_ARB_shader_objects) && defined(GL_ARB_multitexture) && defined(GL_ARB_pixel_buffer_object)
#ifdef GCC_MAC
typedef void (* PFNGLACTIVETEXTUREPROC) (GLenum);
typedef GLhandleARB (* PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void (* PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB **string, const GLint *length);
typedef void (* PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
typedef GLhandleARB (* PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef void (* PFNGLATTACHOBJECTARBPROC) (GLhandleARB containerObj, GLhandleARB obj);
typedef void (* PFNGLLINKPROGRAMARBPROC) (GLhandleARB programObj);
typedef void (* PFNGLUSEPROGRAMOBJECTARBPROC) (GLhandleARB programObj);
typedef void (* PFNGLUNIFORM1IARBPROC) (GLint location, GLint v0);
typedef void (* PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint *params);
typedef void (* PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
typedef GLint (* PFNGLGETUNIFORMLOCATIONARBPROC) (GLhandleARB programObj, const GLcharARB *name);
typedef void (* PFNGLUNIFORM3FARBPROC) (GLint location, GLfloat v0,GLfloat v1, GLfloat v2);
typedef void (* PFNGLUNIFORM4FARBPROC) (GLint location, GLfloat v0,GLfloat v1, GLfloat v2, GLfloat v3);
// special structure for PBO
typedef void (* PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint * buffers );
typedef void (* PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (* PFNGLBUFFERDATAARBPROC) (GLenum target,GLsizei size,const GLvoid * data,GLenum usage);
typedef void (* PFNGLBUFFESUBRDATAARBPROC) (GLenum target,GLint offset,GLsizei size,const GLvoid * data);

typedef void (* PFNGLDELETEBUFFERSARBPROC)(GLsizei n, const GLuint* ids);
typedef void (* PFNGLMAPBUFFERARBPROC) (GLenum target, GLenum access);
typedef GLboolean (* PFNGLUNMAPBUFFERARBPROC) (GLenum target);
// stct for FBO
typedef void (* PFNGLGENFRAMEBUFFERSEXTPROC) ( GLsizei n, GLuint *framebuffers );
typedef void (* PFNGLBINDFRAMEBUFFEREXTPROC) ( GLenum target, GLuint framebuffer );
typedef GLenum (* PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)( GLenum target );
typedef void (* PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
typedef void (* PFNGLDRAWBUFFERSARBPROC) (GLsizei size, const GLenum * buffers);
//render buffers
typedef void (* PFNGLGENRENDERBUFFERSEXTPROC) ( GLsizei n, GLuint *renderbuffers );
typedef void (* PFNGLBINDRENDERBUFFEREXTPROC) ( GLenum target, GLuint renderbuffer );
typedef void (* PFNGLRENDERBUFFERSTORAGEEXTPROC) (  GLenum target, GLenum type, GLsizei width, GLsizei Height);
typedef void (* PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)( GLenum target1, GLenum attachment, GLenum target2, GLuint renderbuffer);

#endif

typedef struct _Gan_GLExt_Function_Pointers
{
   int setup;
   int error;

   PFNGLCOMPILESHADERARBPROC				fCompileShaderARB;
   PFNGLUNIFORM1IARBPROC					fUniform1iARB;
   PFNGLGETUNIFORMLOCATIONARBPROC			fGetUniformLocationARB;
   PFNGLACTIVETEXTUREPROC					fActiveTexture;
   PFNGLUSEPROGRAMOBJECTARBPROC				fUseProgramObjectARB;
   PFNGLLINKPROGRAMARBPROC					fLinkProgramARB;
   PFNGLATTACHOBJECTARBPROC					fAttachObjectARB;
   PFNGLGETINFOLOGARBPROC					fGetInfoLogARB;
   PFNGLGETOBJECTPARAMETERIVARBPROC			fGetObjectParameterivARB;
   PFNGLSHADERSOURCEARBPROC					fShaderSourceARB;
   PFNGLCREATESHADEROBJECTARBPROC			fCreateShaderObjectARB;
   PFNGLCREATEPROGRAMOBJECTARBPROC			fCreateProgramObjectARB;
   PFNGLUNIFORM3FARBPROC					fUniform3fARB;
   PFNGLUNIFORM4FARBPROC					fUniform4fARB;
   //features for PBO
   PFNGLGENBUFFERSARBPROC					fGenBuffersARB;
   PFNGLBINDBUFFERARBPROC					fBindBufferARB;
   PFNGLBUFFERDATAARBPROC					fBufferDataARB;
   PFNGLBUFFERSUBDATAARBPROC				fBufferSubDataARB;
   PFNGLDELETEBUFFERSARBPROC				fDeleteBuffersARB;
   PFNGLMAPBUFFERARBPROC					fMapBufferARB;
   PFNGLUNMAPBUFFERARBPROC					fUnmapBufferARB;
   //stct for FBO
   PFNGLGENFRAMEBUFFERSEXTPROC				fGenFramebuffersEXT;
   PFNGLBINDFRAMEBUFFEREXTPROC				fBindFramebufferEXT;
   PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC		fCheckFramebufferStatusEXT;
   PFNGLFRAMEBUFFERTEXTURE2DEXTPROC			fFramebufferTexture2DEXT;
   PFNGLDRAWBUFFERSARBPROC					fDrawBuffersARB;
   //renderbuffer
   PFNGLGENRENDERBUFFERSEXTPROC				fGenRenderbuffersEXT ;
   PFNGLBINDRENDERBUFFEREXTPROC				fBindRenderbufferEXT;
   PFNGLRENDERBUFFERSTORAGEEXTPROC			fRenderbufferStorageEXT;
   PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC		fFramebufferRenderbufferEXT;


   
} Gan_GLExt_Function_Pointers;

GANDALF_API void gan_initialise_glext_func_ptrs( Gan_GLExt_Function_Pointers* pExtFnPtrs);
/* #if defined(GL_ARB_pixel_buffer_object) */

/* GLsizeiptr OffsetLimitImage2D( __GLpixelStoreMode *pixelStoreMode, */
/*                                      GLsizei width, GLsizei height, */
/*                                      GLenum format,GLenum type, */
/*                                      const GLvoid* userdata); */
/* #endif */

#endif

GANDALF_API Gan_Bool gan_build_openGL_textures_for_image ( Gan_Image *image, Gan_OpenGLTextureStruct *pOGLTexStruct );
GANDALF_API void     gan_free_openGL_textures_for_image ( Gan_OpenGLTextureStruct *pOGLTexStruct );
GANDALF_API Gan_Bool gan_render_openGL_textures_for_image ( Gan_OpenGLTextureStruct *pOGLTexStruct );
GANDALF_API Gan_Bool gan_readback_openGL_image_from_framebuffer ( Gan_OpenGLTextureStruct *pOGLTexStruct, Gan_Image *pgiImage  );



/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifdef HAVE_OPENGL */

#endif /* #ifndef _GAN_OPENGL_TEXTURE_H */
