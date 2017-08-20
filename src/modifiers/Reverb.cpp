//
//  Reverb.cpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#include "Reverb.hpp"

void Reverb::process(float input){
    

    delayLine->feed(input);
    
    //add the early reflections
    float reflectionAccumulation = 0;
    for(int i = 0; i < numEarlyReflections;i++){
        reflectionAccumulation += earlyReflections[i]->getSample()*reflectionAmpList[i];
    }
    
    
    //use the 4 comb filters in paralell
    
    float combAccumulation = 0;
    for(int i = 0; i < 4; i++){
        combAccumulation += combFilters[i]->filter(input);
    }
    
    //use the 2 allpass filters in series
    for(int i = 0; i < 2; i++){
        combAccumulation = allPassFilters[i]->filter(combAccumulation);
    }
    
    //add the parts together
    float wet = reflectionAccumulation + combAccumulation;
    currentSample = (wet*dryWetMix) + (input * (1-dryWetMix));
    //note that combAccumulation also includes the allpass process

}

void Reverb::setPreDelay(float newPreDelay){
    preDelay = newPreDelay;
    for(int i = 0; i < numEarlyReflections; i++){
        earlyReflections[i]->setTime(reflectionTimeList[i]+ preDelay);
    }
    for(int i = 0; i < 4; i++){
        combFilters[i]->setDelayTime(combDelayTimes[i] + preDelay);
    }
    for(int i = 0; i < 2; i++){
        allPassFilters[i]->setDelayTime(allPassDelayTimes[i] + preDelay);
    }
}
