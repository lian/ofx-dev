/* 
	# based on post entries: http://www.openframeworks.cc/forum/viewtopic.php?t=1413
	# memo - Posted: Thu Dec 11, 2008 12:30 am
*/
#ifndef OFX_MEMO_UTILS_H
#define OFX_MEMO_UTILS_H


// // return sign of the number 
// int ofSign(float n) { 
//    return n < 0 ? -1 : n > 0 : 1 : 0; 
// } 

// checks to see if number is in range 
bool ofInRange(float t, float min, float max) { 
   return t>=min && t<=max; 
} 


// clamp a number 
// i use clamp instead of constrain cos easier to type :P 
// and its clamp in glsl 
float ofClamp(float x, float min, float max) { 
   return x < min ? min : x > max ? max : x; 
} 


float ofClamp(float x, float max) { 
   return ofClamp(x, -max, max); 
} 


// // smooth normalized number 
// // with hermite interpolation 
// // only really works if t is 0...1 but best not to clamp here 
// float ofSmooth(t) { 
//    return  t * t * (3 – 2 * t); 
// } 


// // clamp a number between min, max 
// // and smooth with hermite interpolation 
// float ofSmoothClamp(t, min, max) { 
//    float clamped = ofClamp(t, min, max); 
//    float normed  = ofNorm(clamped, min, max); 
//    float smoothed = ofSmooth(normed); 
//    return ofLerp(min, max, smoothed); 
// } 


// square of distance between two points 
// cos checking distance against square is a lot faster than doing squareroot when you dont need it 
float ofDist2(float x1, float y1, float x2, float y2) { 
   float dx = x2 - x1; 
   float dy = y2 - y1; 
   return dx*dx + dy*dy; 
} 

// float ofDist2(float x1, float y1, float z1, float x2, float y2, float z3) { 
//    float dx = x2 - x1; 
//    float dy = y2 - y1; 
//    float dz = z2 - z1; 
//    return dx*dx + dy*dy + dz*dz; 
// }

#endif
