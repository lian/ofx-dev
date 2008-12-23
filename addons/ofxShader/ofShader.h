#ifndef _OF_SHADER
#define _OF_SHADER


#include "ofMain.h"



//		---------------------------------------
// 		very useful info here:
// 		http://www.evl.uic.edu/aej/594/



/*
		// how to get "compiled" ok then use it:
		
		GLint compileStatus;
		glGetObjectParameterivARB( shader, GL_COMPILE_STATUS, &compileStatus );
		glGetObjectParameterivARB( program, GL_INFO_LOG_LENGTH, &infoLogLen );
		infoLog = new GLchar[infoLogLen+1];
		glGetProgramInfoLogARB(program, infoLogLen, NULL, infoLog );
		infoLog[infoLogLen] = '\0';
		fprintf( stderr, "Info Log:\n%s\n", infoLog );	
		
*/

class ofShader{
	
	public:
		
		void 	loadShader(char * shaderName);	
		void 	loadShader(char * fragmentShaderName, char * vertexShaderName);	
		
		void 	unload();
		void 	setShaderActive(bool bActive);
		///-------------------------------------------------------------------------------
		//| Setters 
		
		void 	setUniform (char * name, float v1);
		void 	setUniform (char * name, float v1, float v2);
		void 	setUniform (char * name, float v1, float v2, float v3);
		void 	setUniform (char * name, float v1, float v2, float v3, float v4);
		
		void 	setUniform (char * name, int v1);
		void 	setUniform (char * name, int v1, int v2);
		void 	setUniform (char * name, int v1, int v2, int v3);
		void 	setUniform (char * name, int v1, int v2, int v3, int v4);
		
		void	setAttribute( char * name, float v1);
		void	setAttribute( char * name, float v1, float v2);
		void	setAttribute( char * name, float v1, float v2, float v3);
		void	setAttribute( char * name, float v1, float v2, float v3, float v4);
		
		void	setAttribute( char * name, short v1);
		void	setAttribute( char * name, short v1, short v2);
		void	setAttribute( char * name, short v1, short v2, short v3);
		void	setAttribute( char * name, short v1, short v2, short v3, short v4);
		
		void	setAttribute( char * name, double v1);
		void	setAttribute( char * name, double v1, double v2);
		void	setAttribute( char * name, double v1, double v2, double v3);
		void	setAttribute( char * name, double v1, double v2, double v3, double v4);
		
		
		///-------------------------------------------------------------------------------
		//| Getters
		
		/* the getters are interesting since they return values into a pointer. So pass them
		   in a pointer and they will take the reference and write to that. Pretty efficient
		   but quite painful to use.
		*/
		
		void getActiveVertexAttribute(const char * name, GLfloat * returnValue);
		
		void	printActiveUniforms();
		void	printActiveAttributes();
		
		GLhandleARB 	vertexShader;
		GLhandleARB 	fragmentShader;
		GLhandleARB 	shader;
		
		bool			bLoaded;
};

#endif	

