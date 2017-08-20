//
//  ImpulseGenerators.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 8/3/17.
//
//

#ifndef ImpulseGenerators_hpp
#define ImpulseGenerators_hpp

#include <stdio.h>
#include "ATKSettings.hpp"
#include "BaseOscillator.hpp"
#include <random>

/*
this is an impulse generator;
it reports a "1" n times per second;
otherwise, it reports a zero;
this is periodic. This is commonly used
to trigger grains in granular synthesis

Additionally, this impulse generator features 
 "Burst Masking" - a term coined by Curtis Roads
 in "Microsound". 
 
 The periodicity can be smeared by adjust the 
 "Pulse Deviation" parameter. If pulse deviation is set
 to 0, the impulses are emmitted periodically. if set to 1.0, 
 the impulses are emmitted aperiodically while mainting the same 
 average frequency
 
 */

class ImpulseGenerator : public  BaseOscillator{
    
public:
    ImpulseGenerator(){
        frequency = 1;
        phase = 0;
        phaseInc = frequency/ATKSettings::sampleRate;
        currentSample = 0;
        burstMasking = 0;
        pulseDeviation = 0;
    }
    
    ImpulseGenerator(float startFreq){
        frequency = startFreq;
        phase = 0;
        phaseInc = frequency/ATKSettings::sampleRate;
        currentSample = 0;
        burstMasking = 0;
        pulseDeviation = 0;
        nextTarget = 1.0 + ofRandom(-pulseDeviation, pulseDeviation);
    }
    
    void process(){
        phase += phaseInc;
        if(phase >= nextTarget){
            if(burstMasked){
                currentSample = 0;
            }else{
                currentSample = 1;
            }
            phase -= nextTarget;
            nextTarget = 1.0 + ofRandom(-pulseDeviation, pulseDeviation);
            burstMasked = (ofRandom(1.0) < burstMasking) ? true : false;
        }else if(phase >= 0.0){
            currentSample = 0;
        }else if(phase <= 0){//better plan for negative frequencies
            currentSample = 1;
            phase += nextTarget;
            nextTarget = 1.0 + ofRandom(-pulseDeviation, pulseDeviation);
            nextTarget = 1.0 + ofRandom(-pulseDeviation, pulseDeviation);
            burstMasked = (ofRandom(1.0) < burstMasking) ? true : false;
        }
    }
    
    float getSample(){
        return currentSample;
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = frequency/ATKSettings::sampleRate;
    }
    void setPulseDeviation(float newDev){
        pulseDeviation = newDev;
    }
    void setBurstMasking(float newBM){
        burstMasking = newBM;
    }
    
private:
    float frequency;
    float phase, phaseInc;//loose use of this term
    float currentSample;
    float pulseDeviation;//0.0 to 1.0
    float burstMasking;//0.0 to 1.0 inspired by Curtis Roads
    bool burstMasked;
    float nextTarget;//1 + pulseDeviation;
};

//----------------------------------------------
//aperiodic impulse generator-------------------
//----------------------------------------------
//This is also commonly used to tigger grains or
//other events. This method would be suited for
//creating a stream of grains while avoiding a
//senes of periodicity in the cloud of grains
//----------------------------------------------

//TODO

#endif /* ImpulseGenerators_hpp */
