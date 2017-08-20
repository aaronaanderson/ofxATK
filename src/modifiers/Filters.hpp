//
//  Filters.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#ifndef Filters_hpp
#define Filters_hpp

#include <stdio.h>
#include "ATKSettings.hpp"
#include "ofMain.h"

//Second-order Butterworth filter as described in "The Audio Programming Book" pg 484
//this is super expensive computationally; no effort done to minimalize cost

//ATTENTION: Band Reject filter is broken at the moment

class Butterworth{
public:
    Butterworth(){
        mode = BR;
        prevIn = prevPrevIn = 0.0;
        prevOut = prevPrevOut = 0.0;
        bandwidth = 120;
        cutoff = 1000;
        calculateCoeff();
    }
    
    float filter(float input){
        
        switch(mode){
            case LP:
                currentSample = calculateOutput(input);
                transferValues(input);
                return currentSample;
                break;
            case HP:
                currentSample = calculateOutput(input);
                transferValues(input);
                return currentSample;
                break;
            case BP:
                currentSample = calculateOutput(input);
                transferValues(input);
                return currentSample;
                break;
            case BR:
                currentSample = calculateOutput(input);
                transferValues(input);
                return currentSample;
                break;
        }
    }
    
    void setBandwidth(float newBandwidth){
        bandwidth = newBandwidth;
        if(mode == BP || mode == BR){
            calculateCoeff();
        }
    }
    void setCutoff(float newCutoff){
        cutoff = newCutoff;
        calculateCoeff();
    }
    
private:
    int mode;
    enum modes{
        LP,//low pass
        HP,//high pass
        BP,//bandpass
        BR//band reject
    };
    
    float bandwidth, cutoff;
    float prevPrevIn, prevIn, currentSample;
    float prevPrevOut, prevOut;
    float lambda, phi, lambdaSquared;
    float a0, a1, a2, b1, b2;//coefficients
    
    void transferValues(float input){//have to do this a lot, so let's jsut make it a function
        prevPrevOut = prevOut;
        prevOut = currentSample;
        prevPrevIn = prevIn;
        prevIn = input;
    }
    float calculateOutput(float input){
        return (a0 * input) + (a1*prevIn) + (a2*prevPrevIn) -
        (b1*prevOut) - (b2*prevPrevOut);
    }
    
    void calculateCoeff(){
        switch(mode){
            case LP:
                lambda = 1/tan((PI*cutoff)/ATKSettings::sampleRate);
                lambdaSquared = (lambda*lambda);
                //phi not needed in this mode
                a0 = 1/(1 + (2*lambda) + (lambdaSquared));
                a1 = a0*2;
                a2 = a0;
                b1 = (2*a0)*(1-(lambdaSquared));
                b2 = a0 * ( 1 - (2*lambda) + lambdaSquared);//oop?
                break;
            case HP:
                lambda = tan((PI*cutoff)/ATKSettings::sampleRate);
                lambdaSquared = (lambda*lambda);
                //phi not needed in this mode
                a0 = 1/(1 + (2*lambda) + (lambdaSquared));
                a1 = a0*2;
                a2 = a0;
                b1 = (2*a0)*(lambdaSquared-1);
                b2 = a0 * ( 1 - (2*lambda) + lambdaSquared);//oop?
                break;
            case BP:
                lambda = 1/tan((PI * bandwidth)/ATKSettings::sampleRate);
                lambdaSquared = (lambda*lambda);
                phi = 2 * cos((TWO_PI * cutoff)/ATKSettings::sampleRate);
                a0 = 1/(1.f + lambda);
                a1 = 0;
                a2 = a1 * -1.f;
                b1 = (-1.f * lambda * phi * a0);
                b2 = a0 * (lambda -1);
                break;
            case BR:
                lambda = tan((PI * bandwidth)/ATKSettings::sampleRate);
                lambdaSquared = (lambda*lambda);
                phi = 2 * cos((TWO_PI * cutoff)/ATKSettings::sampleRate);
                a0 = 1/(1.f + lambda);
                a1 = (-1.f * phi * a0);
                a2 = a0;
                b1 = (-1.f * lambda * phi * a0);
                b2 = a0 * (lambda - 1.f);
                break;
        }
    }
};

//--HighPass and LowPass were based on the code and description
//of The Audio Programming Book pages 485-6

//simplie single-purpose filter
class HighPass{
public:
    HighPass(float initFreq = 1000){
        cutOff = initFreq;
        previousSample = 0;
        cosTheta = 2.0 - cos((TWO_PI*cutOff)/ATKSettings::sampleRate);
        coef = cosTheta - sqrt((cosTheta*cosTheta)-1.0);
        cout << "coef: " << coef << endl;
    }
    
    inline float filter(float input){
        currentSample = (input*(1.0-coef)) - (previousSample * coef);
        previousSample = currentSample;
        return currentSample;
    }
    void setFreq(float newCutOff){
        cutOff = newCutOff;
        cosTheta = 2.0 - cos((TWO_PI*cutOff)/ATKSettings::sampleRate);
        coef = sqrt((cosTheta*cosTheta)-1.0) - cosTheta;
    }
private:
    float cutOff;
    double coef, cosTheta;
    float previousSample, currentSample;
};

//simplest low pass filter possible. 1 pole IIR
class LowPass{
public:
    LowPass(float initFreq = 1000){
        cutOff = initFreq;
        previousSample = 0;
        cosTheta = 2.0 - cos((TWO_PI*cutOff)/ATKSettings::sampleRate);
        coef = sqrt((cosTheta*cosTheta)-1.0) - cosTheta;
        cout << "coef: " << coef << endl;
    }
    
    inline float filter(float input){
        currentSample = (input*(1.0+coef)) - (previousSample * coef);
        previousSample = currentSample;
        return currentSample;
    }
    void setFreq(float newCutOff){
        cutOff = newCutOff;
        cosTheta = 2.0 - cos((TWO_PI*cutOff)/ATKSettings::sampleRate);
        coef = sqrt((cosTheta*cosTheta)-1.0) - cosTheta;
    }
private:
    float cutOff;
    double coef, cosTheta;
    float previousSample, currentSample;
};

#endif /* Filters_hpp */
