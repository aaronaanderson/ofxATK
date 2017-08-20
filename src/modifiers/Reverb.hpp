//
//  Reverb.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#ifndef Reverb_hpp
#define Reverb_hpp

#include <stdio.h>
#include "TapInTapOut.hpp"
#include "CombFilter.hpp"
#include "AllPassFilter.hpp"
#include "Filters.hpp"
#include "ofMain.h"

//a very simple shroeder-style digital reverb.
//I may add more sophisticated reverbs in the future
//in addition to improving this to the Moore style

/*This reverb only has 3 ingredients: comb filters, allpass filters, and a delay line.
 Before starting the reverb class, it is a good idea to extend the CombFilter class to include
 a lowpass filter to aproximate the coloration of a hall
 */

class LPCF : public CombFilter{
    
public:
    LPCF(float initMaxDelay = 1000, float initDelay= 1, float initFeedBack =0.9, float cutOffFreq = 1000){
        delayMax = initMaxDelay;
        delayTime = initDelay;
        delayLine = new TapIn(delayMax);
        delayLineAccess = new TapOut(delayLine, delayTime);
        feedBack = initFeedBack;
        lpfFrequency = cutOffFreq;
        lpf = new LowPass(lpfFrequency);
    }
    
    float filter(float input){
        float delay = delayLineAccess->getSample();
        float filteredDelay = lpf->filter(delay);
        delayLine->feed(input + (filteredDelay*feedBack));
        currentSample = input + delay;
        return currentSample;
    }
    void setFreq(float newCutOff){
        lpfFrequency = newCutOff;
        lpf->setFreq(lpfFrequency);
    }
    
private:
    LowPass* lpf;
    float lpfFrequency;
};

class Reverb{
    
public:
    
    Reverb(float absorption = 0.01, float absorptionFreq = 5000, float mix = 0.7, float initPreDelay = 40){
        feedBack = 1.0 - ofClamp(absorption, 0.0, 1.0);
        cutOffFreq = absorptionFreq;
        dryWetMix = 1.0 - ofClamp(mix, 0.0, 1.0);
        preDelay = initPreDelay;
        delayLine = new TapIn(4000);
        for(int i = 0; i < numEarlyReflections; i++){
            earlyReflections[i] = new TapOut(delayLine, reflectionTimeList[i] + preDelay);
        }
        for(int i = 0; i < 4; i++){
            combFilters[i] = new LPCF(1000,combDelayTimes[i]+preDelay, feedBack, cutOffFreq);
            
        }
        for(int i = 0; i < 2; i++){
            allPassFilters[i] = new AllPassFilter(1000, allPassDelayTimes[i] + preDelay, 0.7);
        }
    }
    
    void process(float input);//in CPP
    
    float getSample(){
        return currentSample;
    }
    void setCutOff(float newCutOff){
        cutOffFreq = newCutOff;
        for(int i = 0; i < 4; i++){
            combFilters[i]->setFreq(cutOffFreq);
        }
    }
    void setDryWet(float newDryWet){
        dryWetMix = newDryWet;
    }
    void setAbsorption(float newAbsorption){
        feedBack = 1 - ofClamp(newAbsorption, 0.0, 1.0);
        for(int i = 0; i < 4; i++){
            combFilters[i]->setFeedBack(feedBack);
        }
    }
    void setPreDelay(float newPreDelay);
    
private:
    float feedBack;
    float cutOffFreq;
    float dryWetMix;
    float currentSample;
    float preDelay;
    TapIn* delayLine;
    static const int numEarlyReflections = 16;
    TapOut* earlyReflections[numEarlyReflections];
    float reflectionTimeList[numEarlyReflections] = {4.3, 21.5, 22.5, 26.8, 27, 29.8, 45.8, 48.8, 57.2, 58.7, 59.5, 61.2, 70.7, 70.8, 72.6, 74.1};
    float reflectionAmpList[numEarlyReflections] = {0.841, 0.504, 0.491, 0.379, 0.38, 0.346, 0.289, 0.272, 0.192, 0.193, 0.217, 0.181, 0.18, 0.181, 0.176, 0.142};
    LPCF* combFilters[4];
    float combDelayTimes[4] = {29.7, 37.1, 41.1, 43.7};
    AllPassFilter* allPassFilters[2];
    float allPassDelayTimes[2] = {5, 1.7};
};

#endif /* Reverb_hpp */
