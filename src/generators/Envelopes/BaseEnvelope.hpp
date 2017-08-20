//
//  BaseEnvelope.hpp
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef BaseEnvelope_hpp
#define BaseEnvelope_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ATKSettings.hpp"

//abstract class
//there will be a variety of envelopes taht will need a lot of the same features
class BaseEnvelope{
    
public:
    
    float getValue(){
        return currentValue;
    }
    
    void setGate(int newGate){
        int prev = gate;//save the previous gate
        gate = newGate;//assign the new gate
        if(gate == 1 && prev == 0){state = ATTACK;}//transition from 0 to 1
        if(gate == 0 && prev == 1){state = RELEASE;}//transition from 1 to 0
    }
    
    int getState(){
        return state;
    }
protected:
    double attackTime;
    double decayTime;
    float sustainLevel;
    double releaseTime;
    float currentValue;

    int type;
    int gate;
    int state;
    
    bool legato;
    
    enum modeTypes{
        ANALOG,
        DIGITAL,
        LINEAR
    };
    
    enum envelopeTypes{
        AR,
        AD,
        ASR,
        ADSR,
        AHDSR
    };
    
    enum states{
        OFF,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE,
        SHUTDOWN//for non-legato mode
    };
    
    
    
    
};

#endif /* BaseEnvelope_hpp */
