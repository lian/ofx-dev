#include "ofShader.h"


char *textFileRead(char *fn);		// some memory allocation happens here
									// be careful...  please don't call load shader 
									// repeatedly !!!!! (you have been warned)



//---------------------------------------------------------------
void ofShader::loadShader(char * fragmentName, char * vertexName){
	
	
	bLoaded = false;	
	
	if (GLEE_ARB_shader_objects){
		
		// ---------------------------------- (a) load in the shaders
		char *vs = NULL,*fs = NULL;
		vs = textFileRead(vertexName);
		fs = textFileRead(fragmentName);
		
		vertexShader = (GLhandleARB)glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = (GLhandleARB)glCreateShader(GL_FRAGMENT_SHADER);
		
		GLint length = strlen(vs);
		glShaderSourceARB(vertexShader, 1, (const char**)&vs, &length);
		length = strlen(fs);
		glShaderSourceARB(fragmentShader, 1, (const char**)&fs, &length);
		
		char infobuffer[1000];
		GLsizei infobufferlen = 0;
		
		// ----------------------------------- (b) compile the shaders
		// try to compile "vertex shader"
		glCompileShaderARB(vertexShader);
		
		//please add compile status check in:
		GLint compileStatus = 0;
		glGetObjectParameterivARB( vertexShader, GL_COMPILE_STATUS, &compileStatus );
		if(compileStatus > 0) {
			printf("vertexShader compiled \n");
		} else if (compileStatus == 1) {
			printf("!! vertexShader compilation issues, status : %i !!\n", compileStatus );
		}
		
		
		glGetInfoLogARB(vertexShader, 999, &infobufferlen, infobuffer);
		if (infobufferlen != 0){
			infobuffer[infobufferlen] = 0;
			printf("vertexShader reports: %s \n", infobuffer);
			return;
		}
		
		// ------------------------------------
		// try to compile "fragment shader"
		glCompileShaderARB(fragmentShader);
		
		

		glGetObjectParameterivARB( fragmentShader, GL_COMPILE_STATUS, &compileStatus );
		if(compileStatus > 0) {
			printf("fragmentShader compiled \n");
		} else if (compileStatus == 1) {
			printf("!! fragmentShader compilation issues, status : %i !!\n", compileStatus );
		}		
		
		glGetInfoLogARB(fragmentShader, 999, &infobufferlen, infobuffer);
		if (infobufferlen != 0){
			infobuffer[infobufferlen] = 0;
			printf("fragmentShader reports: %s \n", infobuffer);
			return;
		}
		
		// ----------------------------------- (c) link the shaders
		shader = glCreateProgramObjectARB();
		glAttachObjectARB(shader,vertexShader);
		glAttachObjectARB(shader,fragmentShader);
		glLinkProgramARB(shader);
		
		
		bLoaded = true;
			
	} else {
	
		printf("sorry, it looks like you can't run 'ARB_shader_objects' \n please check the capabilites of your graphics card (http://www.ozone3d.net/gpu_caps_viewer/) \n");
	
	}


}
		
//---------------------------------------------------------------
void ofShader::loadShader(char * shaderName){
	bLoaded = false;
	char fragmentName[1024];
	char vertexName[1024];
	
	char path[255];
	strcpy(path, ofToDataPath(shaderName).c_str()); //this adds the right path to the data folder no matter what OS 
													//you might be using.
	
	sprintf(fragmentName,"%s.frag", path);
	sprintf(vertexName, "%s.vert", path);
	loadShader(fragmentName, vertexName);
}



//---------------------------------------------------------------
void ofShader::unload(){
	
	if (vertexShader){
		glDetachObjectARB(shader,vertexShader);
		glDeleteObjectARB(vertexShader);
		vertexShader = NULL;
	}
	
	if (fragmentShader){
		glDetachObjectARB(shader,fragmentShader);
		glDeleteObjectARB(fragmentShader);
		fragmentShader = NULL;
	}
	
	if (shader){
		glDeleteObjectARB(shader);
		shader = NULL;
	}
	
}

//---------------------------------------------------------------

void ofShader::setShaderActive(bool bActive){
	if (GLEE_ARB_shader_objects && bLoaded == true){
		if (bActive == true){
			glUseProgramObjectARB(shader);
		} else {
			glUseProgramObjectARB(0);
		}
	}
}
/*
//________________________.
//							\__________________.
// FLOAT										\__________________.
//																	\___________________.
//______________________________________________________________________________________\__________________.
*/
void ofShader::setUniform (char * name, float v1) {
	if(bLoaded ){
		glUniform1fARB(glGetUniformLocationARB(shader, name), v1);
	}
}

void ofShader::setUniform (char * name, float v1, float v2){
	if (bLoaded ){
		glUniform2fARB(glGetUniformLocationARB(shader, name), v1, v2);
	}
}

void ofShader::setUniform (char * name, float v1, float v2, float v3){
	if (bLoaded	){
		glUniform3fARB(glGetUniformLocationARB(shader, name), v1, v2, v3);
	}
}

void ofShader::setUniform (char * name, float v1, float v2, float v3, float v4){
	if (bLoaded ){
		glUniform4fARB(glGetUniformLocationARB(shader, name), v1, v2, v3, v4);
	}
}

/*
//_________________________.
//							\__________________.
// INT											\__________________.
//																	\___________________.
//_______________________________________________________________________________________\__________________.
*/
void ofShader::setUniform (char * name, int v1){
	if (bLoaded ){
		glUniform1iARB(glGetUniformLocationARB(shader, name), v1);
	}
}

void ofShader::setUniform (char * name, int v1, int v2){
	if (bLoaded ){
		glUniform2iARB(glGetUniformLocationARB(shader, name), v1, v2);
	}
}

void ofShader::setUniform (char * name, int v1, int v2, int v3){
	if (bLoaded ){
		glUniform3iARB(glGetUniformLocationARB(shader, name), v1, v2, v3);
	}
}

void ofShader::setUniform (char * name, int v1, int v2, int v3, int v4){
	if (bLoaded ){
		glUniform4iARB(glGetUniformLocationARB(shader, name), v1, v2, v3, v4);
	}
}

/*
 //________________________.
 //							\__________________.
 // FLOAT		ATTRIB							\__________________.
 //																	\___________________.
 //______________________________________________________________________________________\__________________.
 */
void ofShader::setAttribute (char * name, float v1) {
	if(bLoaded ){
		glVertexAttrib1f(glGetAttribLocation((GLuint)shader, name), v1);
	}
}

void ofShader::setAttribute (char * name, float v1, float v2){
	if (bLoaded ){
		glVertexAttrib2f(glGetAttribLocation((GLuint)shader, name), v1, v2);
	}
}

void ofShader::setAttribute (char * name, float v1, float v2, float v3){
	if (bLoaded	){
		glVertexAttrib3f(glGetAttribLocation((GLuint)shader, name), v1, v2, v3);
	}
}

void ofShader::setAttribute (char * name, float v1, float v2, float v3, float v4){
	if (bLoaded ){
		glVertexAttrib4f(glGetAttribLocation((GLuint)shader, name), v1, v2, v3, v4);
	}
}

/*
 //_________________________.
 //							\__________________.
 // Short				ATTRIB					\__________________.
 //																	\___________________.
 //_______________________________________________________________________________________\__________________.
 */
void ofShader::setAttribute (char * name, short v1){
	if (bLoaded ){
		glVertexAttrib1s(glGetAttribLocation((GLuint)shader, name), v1);
	}
}

void ofShader::setAttribute (char * name, short v1, short v2){
	if (bLoaded ){
		glVertexAttrib2s(glGetAttribLocation((GLuint)shader, name), v1, v2);
	}
}

void ofShader::setAttribute (char * name, short v1, short v2, short v3){
	if (bLoaded ){
		glVertexAttrib3s(glGetAttribLocation((GLuint)shader, name), v1, v2, v3);
	}
}

void ofShader::setAttribute (char * name, short v1, short v2, short v3, short v4){
	if (bLoaded ){
		glVertexAttrib4s(glGetAttribLocation((GLuint)shader, name), v1, v2, v3, v4);
	}
}

/*
 //_________________________.
 //							\__________________.
 // DOUBLE				ATTRIB					\__________________.
 //																	\___________________.
 //_______________________________________________________________________________________\__________________.
 */
void ofShader::setAttribute (char * name, double v1){
	if (bLoaded ){
		glVertexAttrib1s(glGetAttribLocation((GLuint)shader, name), v1);
	}
}

void ofShader::setAttribute (char * name, double v1, double v2){
	if (bLoaded ){
		glVertexAttrib2s(glGetAttribLocation((GLuint)shader, name), v1, v2);
	}
}

void ofShader::setAttribute (char * name, double v1, double v2, double v3){
	if (bLoaded ){
		glVertexAttrib3s(glGetAttribLocation((GLuint)shader, name), v1, v2, v3);
	}
}

void ofShader::setAttribute (char * name, double v1, double v2, double v3, double v4){
	if (bLoaded ){
		glVertexAttrib4s(glGetAttribLocation((GLuint)shader, name), v1, v2, v3, v4);
	}
}


/* getting the shit from attribs. standard C is:

void glGetVertexAttribfv(	GLuint  	index,
							GLenum  	pname,
							GLfloat * 	params);

let's try to accomodate it.

Getting Attrib location:

GLint glGetAttribLocation(	GLuint  	program,
							const GLchar * 	name);
*/

void ofShader::getActiveVertexAttribute(const char * name, GLfloat * returnValue) {
	GLint loc = glGetAttribLocation((GLuint) shader, name);
	//GLint numAttributes = 0;
	//glGetProgramiv( (GLuint)shader, GL_ACTIVE_ATTRIBUTES, &numAttributes );
	//printf("numAttributes: %i\n", numAttributes);
	
	//GLint attributeMaxLength = 0;
	//glGetProgramiv( (GLuint)shader, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeMaxLength );
	//printf("attributeMaxLength: %i\n", attributeMaxLength);
	
	//GLint count = -1;
	//GLenum type = 0;
	//GLchar* attributeName = new GLchar[attributeMaxLength];
	//for ( GLint i = 0; i < numAttributes; ++i )
	//{
		//GLsizei length;
		//glGetActiveAttrib( (GLuint)shader, loc-1, attributeMaxLength, &length, &count, &type, returnValue); 
		//glGetVertexAttribfv(loc, GL_CURRENT_VERTEX_ATTRIB, returnValue);
		
		/*for(int j = 0; j < length; j++) {
			printf("%c", attributeName[j]);
		}
		printf("\n");
	}*/
	printf("----------------------\n");
	//delete [] attributeName;
}
	


/*//----------------------------------------------------------------------------------------------------------
*/
void ofShader::printActiveUniforms() {
	//GLint location = glGetUniformLocation((GLuint)shader, name);
	// now find it in the list of uniforms to get type and size
	GLint numUniforms = 0;
	glGetProgramiv( (GLuint)shader, GL_ACTIVE_UNIFORMS, &numUniforms );
	printf("numUniforms: %i\n", numUniforms);
	
	GLint uniformMaxLength = 0;
	glGetProgramiv( (GLuint)shader, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength );
	printf("uniformMaxLength: %i\n", uniformMaxLength);
	
	GLint count = -1;
	GLenum type = 0;
	GLchar* uniformName = new GLchar[uniformMaxLength];
	for ( GLint i = 0; i < numUniforms; ++i )
	{
		GLsizei length;
		glGetActiveUniform( (GLuint)shader, i, uniformMaxLength, &length, &count, &type, uniformName); 
	
		for(int j = 0; j < length; j++) {
			printf("%c", uniformName[j]);
		}
		printf(" @ index %i\n", glGetUniformLocation((GLuint)shader, uniformName));
	}
	printf("----------------------\n");
	delete [] uniformName;
}

void ofShader::printActiveAttributes() {
	//GLint location = glGetUniformLocation((GLuint)shader, name);
	// now find it in the list of uniforms to get type and size
	GLint numAttributes = 0;
	glGetProgramiv( (GLuint)shader, GL_ACTIVE_ATTRIBUTES, &numAttributes );
	printf("numAttributes: %i\n", numAttributes);
	
	GLint attributeMaxLength = 0;
	glGetProgramiv( (GLuint)shader, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeMaxLength );
	printf("attributeMaxLength: %i\n", attributeMaxLength);
	
	GLint count = -1;
	GLenum type = 0;
	GLchar* attributeName = new GLchar[attributeMaxLength];
	for ( GLint i = 0; i < numAttributes; ++i )
	{
		GLsizei length;
		glGetActiveAttrib( (GLuint)shader, i, attributeMaxLength, &length, &count, &type, attributeName); 
		
		for(int j = 0; j < length; j++) {
			printf("%c", attributeName[j]);
		}
		printf(" @ index %i\n", glGetAttribLocation((GLuint)shader, attributeName));
	}
	printf("----------------------\n");
	delete [] attributeName;
}


//---------------------------------------------------------
// below is from: www.lighthouse3d.com
// you may use these functions freely. they are provided as is, and no warranties, either implicit, or explicit are given
//---------------------------------------------------------

char *textFileRead(char *fn) {

	FILE *fp;
	char *content 	= 	NULL;
	int count		=	0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");
		if (fp != NULL) {
		
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	
	return content;
}
