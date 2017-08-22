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
    float reflectionTimeList[numEarlyReflections] = {4.3f, 21.5f, 22.5f, 26.8f, 27.f, 29.8f, 45.8f, 48.8f, 57.2f, 58.7f, 59.5f, 61.2f, 70.7f, 70.8f, 72.6f, 74.1f};
    float reflectionAmpList[numEarlyReflections] = {0.841f, 0.504f, 0.491f, 0.379f, 0.38f, 0.346f, 0.289f, 0.272f, 0.192f, 0.193f, 0.217f, 0.181f, 0.18f, 0.181f, 0.176f, 0.142f};
    LPCF* combFilters[4];
    float combDelayTimes[4] = {29.7f, 37.1f, 41.1f, 43.7f};
    AllPassFilter* allPassFilters[2];
    float allPassDelayTimes[2] = {5.f, 1.7f};
};

#endif /* Reverb_hpp */
