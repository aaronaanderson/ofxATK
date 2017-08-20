//
//  AllPassFilter.hpp
//
//  Created by Aaron Anderson on 8/11/17.
//
//

#ifndef AllPassFilter_hpp
#define AllPassFilter_hpp

#include <stdio.h>
#include "TapInTapOut.hpp"

class AllPassFilter{
    
public:
    AllPassFilter(float initMaxDelay = 1000, float initDelay= 1, float initGainCoef = 1.0){
        delayLine = new TapIn(initMaxDelay);
        delayTime = initDelay;
        delayLineAccess = new TapOut(delayLine, delayTime);
        gainCoef = initGainCoef;
    }
    
    inline float filter(float input){
        float delay = delayLineAccess->getSample();
        //algorithm from EarLevel.com
        //note I did not have the tools to properly test this at the time
        //the effect is hard to hear on its own, but I believe this to be correct
        currentSample = ((delay+(input*-gainCoef))*gainCoef) + input;
        delayLine->feed(currentSample);
        return currentSample;
    }
    float getSample(){
        return currentSample;
    }
    void setGainCoef(float newGainCoef){
        gainCoef = newGainCoef;
    }
    void setDelayTime(float newDelayTime){
        delayTime = newDelayTime;
        delayLineAccess->setTime(delayTime);
    }
    
private:
    TapIn* delayLine;
    TapOut* delayLineAccess;
    float currentSample;
    float delayTime;
    float gainCoef;
};

#endif /* AllPassFilter_hpp */
