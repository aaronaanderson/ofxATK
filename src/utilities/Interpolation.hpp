//
//  Interpolation.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/16/17.
//
//

#ifndef Interpolation_hpp
#define Interpolation_hpp

#include <stdio.h>
#include "math.h"

inline float linearInterp(float x0, float x1, float y0, float y1, float x){
    
    if (x1 == x0) { return 0; }//avoid divideBy0
    float scalar = (x - x0) / (x1 - x0);//gather normalized position between two x values
    
    float result = (y0*scalar) + (y1*(1 - scalar));
    
    return result;
}

//a small form version that assumes x locations are integers and neighbors
inline float linearInterp(float y0, float y1, float x) {//this version assumes integer x values
    float scalar = x - (int)x;//how far away are we from y0?
    return (y0*(1-scalar)) + (y1*(scalar));
}

//this is considerably more expensive than linear
inline float cubicInterp(float y0, float y1, float y2, float y3, float xPos){
    float x = xPos - int(xPos); // how far between points x1 and x2?
    float a = (-0.5*y0) + (1.5*y1) - (1.5*y2) + (0.5 * y3);
    float b = (y0) - (2.5*y1) + (2 * y2) - (0.5*y3);
    float c = (-0.5*y0) + (0.5*y2);
    float d = y1;
    return (a*pow(x, 3)) + (b*pow(x, 2)) + (c*x) + d;
};

#endif /* Interpolation_hpp */
