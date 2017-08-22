//
//  BaseOscillator.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 8/1/17.
//
//

#ifndef BaseOscillator_hpp
#define BaseOscillator_hpp

#include <stdio.h>
#include "ATKSettings.hpp"
#include "ofMain.h"

class BaseOscillator{
    
public:
    
    BaseOscillator(){
        frequency = 440;
        amplitude = 1.0;
        phase = 0;
        setFreq(frequency);
    }
    
    BaseOscillator(float initFreq){
        frequency = initFreq;
        amplitude = 1.0;
        phase = 0;
        setFreq(frequency);
    }
    
    inline void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = frequency/ATKSettings::sampleRate;
    }
    void setAmp(float newAmp){
        amplitude = newAmp;
    }
    
    void setPhase(float newPhase){
        phase = newPhase;
    }
    
    void setup(float freq, float amp, double newPhase){
        frequency = freq;
        amplitude = amp;
        phase = newPhase;
    }
    
    float getSample(){
        return currentSample;
    }
    
    virtual void process(){};
    
    float getFreq(){
        return frequency;
    }
    float getAmp(){
        return amplitude;
    }
    
protected:
    
    float frequency, amplitude;
    double phase, phaseInc;
    float currentSample;
    
};

#endif /* BaseOscillator_hpp */
