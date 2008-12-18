
#ifndef ofx_objLoader_h_
#define ofx_objLoader_h_

#include "ofMain.h"

#include <fstream>
#include <iostream>
#include <deque>
using namespace std;


/**
OBJ 3D geometry file import and gl rendering, the hands-off way.
@author jtnimoy
@code
ofxObjLoader myCube;
myCube.loadFile("cube.obj");
myCube.outlineFaces(); //if you want to draw it wireframe
// or
myCube.fillFaces(); //if you want to draw it solid
// or
@endcode

last updated 1-aug-06

still needs to be implemented:
	- texture coordinates
	- faces with vertex counts greater than 255.
	- test the obj output of 3d apps other than blender.
references:
	http://orion.math.iastate.edu/burkardt/data/obj/obj_format.txt
*/


/**
   holds the information for a single face in an OBJ geometry file.
*/
class objFace{
public:
  /**
     number of points in this face seperated by space.
  */
  int count;

  /**
     could be "%i/%i/%i" or "%i/%i" or number, and possibly "%i"
	 @todo there should really be support for other types.
  */
  int type;

  /**
     vertices contained in the face
  */
  long vertices[4];

  /**
     normals of that vertex (optional - see ::type)
  */
  long normals[4];

  /**
     texture coord of that vertex (optional - see ::type)
  */
  long texCoords[4];

};

/**
   Just an private internal convenience class for OBJ. Would be nice
   to port OBJ to JPoint and have one less class.
*/
class objVertex{
public:
  objVertex();
  objVertex(float x,float y,float z);
  float x;
  float y;
  float z;
};


/**
   import 3D geometry from a file and draw it on your screen in 2 lines of code.
   @author jtnimoy
*/
class ofxObjLoader{
 public:

  ofxObjLoader(char file[]); ///< instantiate a new OBJ object and have it import geometry from a 3D OBJ file.
  ofxObjLoader(); ///< empty constructor if you just want to populate your very own mesh chunk.

  ~ofxObjLoader();

  deque<objFace> faces; ///< list of faces
  deque<objVertex> vertices; ///< list of verts
  deque<objVertex> normals; ///< list of normals
  deque<objVertex> texCoords; ///< list of texture coordinates
  bool verbose; ///< whether or not to complain about parsing issues to stderr.
  void loadFile(char[]);//alias for open frameworks

  void outlineFaces(); ///< outline the faces like a mesh wireframe.
  void fillFaces(); ///< fill each face with triangle geometry.
  void pointVertices(); ///< render a point cloud.
  objVertex getVertex(int i); ///< get a specific internal vertex at a given place.

 private:
  void renderFace(int i); ///< render a single face, given an in-file ID number.
  void ignoreRestOfLine(ifstream *f); ///< parse til the next carraige return.
  void complain(char *s);
};

#endif
