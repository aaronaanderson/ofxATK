//
//  CombFilter.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 8/11/17.
//
//

#ifndef CombFilter_hpp
#define CombFilter_hpp

#include <stdio.h>
#include "TapInTapOut.hpp"
#include "ofMain.h"

class CombFilter{
    
public:

    CombFilter(float initMaxDelay = 1000, float initDelay= 1, float initFeedBack =0.9){
        delayMax = initMaxDelay;
        delayTime = initDelay;
        delayLine = new TapIn(delayMax);
        delayLineAccess = new TapOut(delayLine, delayTime);
        feedBack = initFeedBack;
    }
    
    void setFeedBack(float newFeedBack){
        feedBack = ofClamp(newFeedBack, 0.0, 1.0);
    }
    void setDelayTime(float newDelayTime){
        delayTime = ofClamp(newDelayTime, 0, delayMax);
        delayLineAccess->setTime(delayTime);
    }
    
    inline float filter(float input){
        float delay = delayLineAccess->getSample();
        delayLine->feed(input + (delay*feedBack));
        currentSample = input + delay;
        return currentSample;
    }
    
    float getSample(){
        return currentSample;
    }
    
protected:
    TapIn* delayLine;
    TapOut* delayLineAccess;
    
    float delayMax, delayTime;
    float currentSample;
    float feedBack;
};

#endif /* CombFilter_hpp */
