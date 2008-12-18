#include "ofxObjLoader.h"

ofxObjLoader::ofxObjLoader(){
  verbose=false;
}


ofxObjLoader::ofxObjLoader(char file[]){
  ofxObjLoader();
  loadFile(file);
}


void ofxObjLoader::loadFile(char file[]){

  string newFileName = ofToDataPath(file);
  //validate the file name
  if(strlen(file)==0){
    complain("filename string was empty");
    return;
  }

  //make sure the file exists on the disk
  ifstream existanceChecker(newFileName.c_str());
  if(!existanceChecker.is_open()){
    complain("file not found");
    return;
  }
  existanceChecker.close();


  // we will now slowly parse through the file f
  ifstream f;
  f.open(newFileName.c_str(),iostream::binary);
  while(f.good()){

    //get the first token on this line. it's a command
    char objCommand[256];
    f.getline(objCommand,256,' ');

    if(!strcmp(objCommand,"v")){
      vertices.push_back(objVertex());
      f >> vertices.back().x;
      f >> vertices.back().y;
      f >> vertices.back().z;

      ignoreRestOfLine(&f);

    }else if(!strcmp(objCommand,"#")){//comment
      ignoreRestOfLine(&f);

    }else if(!strcmp(objCommand,"vt")){
      texCoords.push_back(objVertex());
      f >> texCoords.back().x;
      f >> texCoords.back().y;
      f >> texCoords.back().z;
      ignoreRestOfLine(&f);

    }else if(!strcmp(objCommand,"vn")){
      normals.push_back(objVertex());
      f >> normals.back().x;
      f >> normals.back().y;
      f >> normals.back().z;
      ignoreRestOfLine(&f);


    }else if(!strcmp(objCommand,"f") || !strcmp(objCommand,"fo")){
      char x[256];
      int strlen_x;
      faces.push_back(objFace());

      /**
	    get the number of vertices in this face and store it in the face struct.
      */
      int oldpos = f.tellg(); //push file ptr
      f.getline(x,256);
      strlen_x=strlen(x);
      faces.back().count = 1;
      for(int i=0;i<strlen_x;i++){
	    if(x[i]==' '||x[i]=='\t')faces.back().count++;
      }
      f.seekg(oldpos);//pop file ptr

      /**
	     get the number of forward slashes per line in order to categorise.
      */
      oldpos = f.tellg(); //push file ptr
      f.getline(x,256);
      strlen_x=strlen(x);
      faces.back().type = 1;
      for(int i=0;i<strlen_x;i++){
	    if(x[i]=='/')faces.back().type++;
	    else if(x[i]==' '||x[i]=='\t')break;//only count the first one.
      }
      f.seekg(oldpos);//pop file ptr

      /**
	   validate vertex size to make sure this is a type of face-spec
	   we know how to parse which is only 2, 3, and 4
      */
      if(faces.back().count>4 ){
	    complain("Unrecognized face vertex count.");
	    ignoreRestOfLine(&f);
	    continue;
      }


      /**
	   validate vertex.type - the  data-depth. ie. how many numbers per chunk.
      */
      if(faces.back().type!=3  && faces.back().type!=2 && faces.back().type!=1 ){
	    complain("Unrecognized face vertex type.");
	    ignoreRestOfLine(&f);
	    continue;
      }

      /**
	     loop through and collect the appropriate data into the arrays.
      */
      for(int thisVertexID=0;thisVertexID<faces.back().count;thisVertexID++){
	    if(faces.back().count>=thisVertexID+1){

	    //depending on the syntax of the face vertex chunk, parse accordingly
	    if(faces.back().type==3){
	      // %i/%i/%i

	      //collect the geometric vertex
	      f.getline(x,256,'/');
	      faces.back().vertices[thisVertexID] = strtol(x,NULL,10);

	      //collect the texture vertex
	      f.getline(x,256,'/');
	      faces.back().texCoords[thisVertexID] = strtol(x,NULL,10);

	      //collect the vertex normal, but beware of the end-of-line
	      if(faces.back().count==thisVertexID+1)f.getline(x,256);
	      else f.getline(x,256,' ');
	      faces.back().normals[thisVertexID] = strtol(x,NULL,10);




	  }else if(faces.back().type==2){
	    // %i/%i

	    //collect the geometric vertex
	    f.getline(x,256,'/');
	    faces.back().vertices[thisVertexID] = strtol(x,NULL,10);

	    //collect the texture vertex, but beware of the end-of-line
	    if(faces.back().count==thisVertexID+1)f.getline(x,256);
	    else f.getline(x,256,' ');
	    faces.back().texCoords[thisVertexID] = strtol(x,NULL,10);

	  }else if(faces.back().type==1){
	    // %i

	    //collect the geometric vertex, but beware of the end-of-line
	    if(faces.back().count==thisVertexID+1)f.getline(x,256);
	    else f.getline(x,256,' ');
	    faces.back().vertices[thisVertexID] = strtol(x,NULL,10);
	  }

	}

      }

    }else if(strlen(objCommand)==0){
    }else{
      if(objCommand[0]!='#'){
		char s[256];
		sprintf(s,"command token not parsed: %s",objCommand);
		complain(s);
	   }
      ignoreRestOfLine(&f);
    }
  }
  f.close();

}

ofxObjLoader::~ofxObjLoader(){

}


objVertex ofxObjLoader::getVertex(int i){
  if(i<vertices.size())return vertices[i];
  else return vertices[0];
}



void ofxObjLoader::renderFace(int i){
  /**
     draw the verts
  */

  for(int ii=0;ii<faces[i].count;ii++){
	if(faces[i].type>3){
	  glTexCoord2f(texCoords[faces[i].texCoords[ii]-1].x,
		   texCoords[faces[i].texCoords[ii]-1].y);
	}

	if(faces[i].type>2){
	  glNormal3f(normals[faces[i].normals[ii]-1].x,
		 normals[faces[i].normals[ii]-1].y,
		 normals[faces[i].normals[ii]-1].z);
	}

	int index = faces[i].vertices[ii]-1;
	float x=vertices[index].x;
	float y=vertices[index].y;
	float z=vertices[index].z;
	glVertex3f(x,y,z);
  }
}


void ofxObjLoader::fillFaces(){
#if defined(__DARWIN__)
  glEnable(GL_RESCALE_NORMAL);
#endif
  for(int i=0;i<faces.size();i++){
    glBegin(GL_TRIANGLE_FAN);
    renderFace(i);
    glEnd();
  }
}



void ofxObjLoader::outlineFaces(){
  for(int i=0;i<faces.size();i++){
    glBegin(GL_LINE_LOOP);
    renderFace(i);
    glEnd();
  }
}


void ofxObjLoader::pointVertices(){
  for(int i=0;i<faces.size();i++){
    glBegin(GL_POINTS);
    renderFace(i);
    glEnd();
  }
}


void ofxObjLoader::ignoreRestOfLine(ifstream *f){
  char buff[256];
  f->getline(buff,256);
  //ok, now skip empty lines as well.
  if(f->peek()=='\n'||f->peek()=='\r')ignoreRestOfLine(f);
}

void ofxObjLoader::complain(char *s){
  if(verbose)fprintf(stderr,"ofxObjLoader: %s\n",s);
}


objVertex::objVertex(float xx,float yy,float zz){
	x=xx;
	y=yy;
	z=zz;
}

objVertex::objVertex(){
	x=0;
	y=0;
	z=0;
}
