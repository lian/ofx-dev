

#ifndef _OF_VEC3f
#define _OF_VEC3f

#include "ofConstants.h"



class ofVec3f{
public:
	
	
	
	ofVec3f( 	const float _x = 0.0f, 
           	const float _y = 0.0f, 
           	const float _z = 0.0f )
        { x = _x;  y = _y;  z = _z; }
	ofVec3f( const ofVec3f &vec )  
        { x = vec.x;  y = vec.y;  z = vec.z; }
    //virtual ~ofVec3f() 
    //    { }
    
    // DATA MEMBERS
    /////////////////

    float x;
    float y;
    float z;
    
    // FUNCTION MEMEBERS
    //==================
    
    void set( 	float _x, float _y, float _z )
        { x= _x; y =_y;  z=_z; }
        void set( const ofVec3f &vec )
       { x = vec.x;  y = vec.y;  z = vec.z; }

    // Accessor
    float &operator[]( const int &i )           // [0], [1], [2] return x, y, z
        { switch(i) {
          case 0:  return x;
          case 1:  return y;
          case 2:  return z;
          default: return x; } }

    // Vector Addition
    ofVec3f operator+( const ofVec3f & vec ) const  // returns this + vec
        { return ofVec3f(x+vec.x, y+vec.y, z+vec.z); } 
    ofVec3f &operator+=( const ofVec3f & vec )      // this += vec
        { x+=vec.x; y+=vec.y; z+=vec.z;
          return *this; } 

    // Vector Subtraction
    ofVec3f operator-() const                     // returns -this
        { return ofVec3f(-x, -y, -z); } 
    ofVec3f operator-( const ofVec3f & vec ) const  // returns this - vec
        { return ofVec3f(x-vec.x, y-vec.y, z-vec.z); } 
    ofVec3f &operator-=( const ofVec3f & vec )      // this -= vec
        { x-=vec.x; y-=vec.y; z-=vec.z;
          return *this; } 

    // Scaling Multiplication
    ofVec3f operator*( const float f ) const      // returns this * f
        { return ofVec3f(x*f, y*f, z*f); } 
    friend ofVec3f operator*( const float f, const ofVec3f &vec )  // returns f * this
        { return ofVec3f(vec.x*f, vec.y*f, vec.z*f); } 
    ofVec3f &operator*=( const float f )          // this *= f
        { x*=f; y*=f; z*=f;
          return *this; } 

    // Scaling Division
    ofVec3f operator/( const float f ) const      // returns this / f
        { return ofVec3f(x/f, y/f, z/f); } 
    ofVec3f &operator/=( const float f )          // this /= f
        { x/=f; y/=f; z/=f;
          return *this; } 

    // Vector Multiplication
    ofVec3f operator*( const ofVec3f & vec ) const  // !WARNING (MEMBERWISE): returns this.? * vec.?
        { return ofVec3f(x*vec.x, y*vec.y, z*vec.z); } 
    ofVec3f &operator*=( const ofVec3f & vec )      // !WARNING (MEMBERWISE): this.? *= vec.?
        { x*=vec.x; y*=vec.y; z*=vec.z;
          return *this; } 

    // Vector Division
    ofVec3f operator/( const ofVec3f & vec ) const  // !WARNING (MEMBERWISE): returns this.? / vec.?
        { return ofVec3f(x/vec.x, y/vec.y, z/vec.z); } 
    ofVec3f &operator/=( const ofVec3f & vec )      // !WARNING (MEMBERWISE): this.? /= vec.?
        { x/=vec.x; y/=vec.y; z/=vec.z;
          return *this; } 

    // Dot Product
    float dot( const ofVec3f & vec ) const        // returns dot value of this and vec
        { return x*vec.x + y*vec.y + z*vec.z; } 
    
    // Cross Product
    ofVec3f cross( const ofVec3f & vec ) const      // returns cross product of this and vec
        { return ofVec3f(y*vec.z - z*vec.y, 
                       z*vec.x - x*vec.z, 
                       x*vec.y - y*vec.x); } 


    // Length
    float length() const                // returns length
        { return (float)sqrt(x*x + y*y + z*z); } 
    
    // Normalize
    ofVec3f &normalize()                  // normalizes this
        { float f=length();
          x/=f; y/=f; z/=f;
          return *this; } 
    ofVec3f norm_value() const            // returns normalized value, does not modify this
        { float f=length();
          return ofVec3f(x/f, y/f, z/f); } 


 	void rotate(float val) {
	    // Floats are not precise enough, so doubles are used for the calculations
	    double cosval=cos(val);
	    double sinval=sin(val);
	    double tmpx=x*cosval - y*sinval;
	    double tmpy=x*sinval + y*cosval;

	    x=(float)tmpx;
	    y=(float)tmpy;
  }


	/*
    // a vector through a matrix
    ofVec3f operator* (const Matrix& mat) const
    {
      ofVec3f ret;
      ret.x = x*mat.mat[0][0] + y*mat.mat[1][0] + z*mat.mat[2][0] + mat.mat[3][0];
      ret.y = x*mat.mat[0][1] + y*mat.mat[1][1] + z*mat.mat[2][1] + mat.mat[3][1];
     
      return ret;
    }

    // a vector through a matrix
    void operator*=(const Matrix& mat)
    {
      ofVec3f vec = *this;
      x = vec.x*mat.mat[0][0] + vec.y*mat.mat[1][0] + vec.z*mat.mat[2][0] + mat.mat[3][0];
      y = vec.x*mat.mat[0][1] + vec.y*mat.mat[1][1] + vec.z*mat.mat[2][1] + mat.mat[3][1];
      z = vec.x*mat.mat[0][2] + vec.y*mat.mat[1][2] + vec.z*mat.mat[2][2] + mat.mat[3][2];
    }
	*/
};

#endif
