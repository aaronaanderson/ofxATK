//
//  Miscellaneous.hpp
//  envelopes_example
//
//  Created by Aaron Anderson on 8/9/17.
//
//

#ifndef Miscellaneous_hpp
#define Miscellaneous_hpp

#include <stdio.h>
#include "math.h"

inline float mtof(float midiVal){
    return 440*(pow(2, (midiVal-69)/12.f));
}

//this is wrong TODO
//inline float vtoa(float midiVel){
//    return 40*log(midiVel/127.f);
//}

inline float noteToSpeed(float midiNote){// assumes middle C as normal speed (1.0);
    float distanceFromMiddleC = (midiNote-60)/12.f;
    return pow(2, distanceFromMiddleC);
}

#endif /* Miscellaneous_hpp */

