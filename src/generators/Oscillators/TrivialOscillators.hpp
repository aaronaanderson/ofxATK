//
//  TrivialOscillators.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#ifndef TrivialOscillators_hpp
#define TrivialOscillators_hpp

#include <stdio.h>
#include "BaseOscillator.hpp"

#endif /* TrivialOscillators_hpp */


class TSine : public BaseOscillator{
    
public:
    
    TSine(){
        frequency = 440;
        phase = 0;
        amplitude = 1.0;
        setFreq(frequency);
    }
    
    
    TSine(float initFreq) : BaseOscillator(initFreq){
        phase = 0;
        amplitude = 1.0;
        setFreq(initFreq);
    }
    
    inline void process(){
        currentSample = sin(phase)*amplitude;
        phase += phaseInc;
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = (TWO_PI*frequency)/ATKSettings::sampleRate;
    }
    
};

class TSawtooth : public BaseOscillator{
    
public:
    TSawtooth(float initFreq) : BaseOscillator(initFreq){
        phase = 0;
        amplitude = 1.0;
        setFreq(initFreq);//this sets the phaseInc
        currentSample = 0;
    }
    
    void process(){
        phase += phaseInc;
        while(phase > 1.0){//use while in case frequency is insanely highh (above SR)
            phase -= 1.0;
        }
        while(phase < 0.0){//to ensure that negative frequencies will work
            phase += 1.0;
        }
        
        currentSample = ((phase*2.f)-1.f) * amplitude;
    }

};

class TPhasor : public TSawtooth{//same thing as sawtooth, but unipolar
    
public:

    TPhasor(float initFreq) : TSawtooth(initFreq){
        phase = 0;
        amplitude = 1.0;
        setFreq(initFreq);//this sets the phaseInc
        currentSample = 0;
    }
    void process(){
        phase += phaseInc;
        while(phase > 1.0){//use while in case frequency is insanely highh (above SR)
            phase -= 1.0;
        }
        while(phase < 0.0){//to ensure that negative frequencies will work
            phase += 1.0;
        }
        currentSample = phase * amplitude;
    }
    
};

class TTriangle : public TSawtooth{
    
public:
    
    TTriangle(float initFreq) : TSawtooth(initFreq){
        phase = 0;
        amplitude = 1.0;
        setFreq(initFreq);
    }
    
    inline float getSample(){
        float tri = 2 * fabs(currentSample) - 1;//manipulate sawtooth to triangle
        return tri*amplitude;
    }
};

class TSquare : public BaseOscillator{
    
public:
    
    TSquare(float initFreq) : BaseOscillator(initFreq){
        phase = 0;
        amplitude = 1.0;
        setFreq(initFreq);
        dutyCycle = 0.5;
    }
    
    inline void process(){
        phase += phaseInc;
        while(phase > 1.0){
            phase -= 1;
        }
        while(phase < 0){
            phase += 1.0;
        }
        
        if(phase > dutyCycle){
            currentSample = 1.0 * amplitude;
        }else{
            currentSample = -1.0 * amplitude;
        }
        
    }
    
    void setDuty(float newDutyCycle){
        dutyCycle = newDutyCycle;
    }
    
private:
    float dutyCycle;
};


