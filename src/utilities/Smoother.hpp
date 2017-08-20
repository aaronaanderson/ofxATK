//
//  Smoother.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/16/17.
//
//

#ifndef Smoother_hpp
#define Smoother_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ATKSettings.hpp"

class ParameterSmoother {
    
public:
    
    ParameterSmoother(float smoothingTimeMS, int sampleRate) {
        smoothingTime = smoothingTimeMS;
        a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * sampleRate));
        b = 1.0 - a;
        z = 0.0;
    }
    ParameterSmoother(float smoothingTimeMS){
        smoothingTime = smoothingTimeMS;
        a = exp(-TWO_PI / (smoothingTimeMS * 0.001 * ATKSettings::sampleRate));
        b = 1.0 - a;
        z = 0.0;
    }
    
    inline float process(float input) {
        z = (input * b) + (z * a);
        return z;
    }
    
    inline void setTime(float newSmoothingTime){
        //do a safety check since this is expensive; no need to recalculate if not changed
        if(smoothingTime != newSmoothingTime){
            smoothingTime = newSmoothingTime;
            a = exp(-TWO_PI / (smoothingTime * 0.001 * ATKSettings::sampleRate));
            b = 1.0 - a;
            z = 0.0;
        }
    }
    
private:
    float smoothingTime;
    float a;
    float b;
    float z;
};

struct SmoothValue {
    float targetValue;
    float currentValue;
    ParameterSmoother* smoother;
};
#endif /* Smoother_hpp */
