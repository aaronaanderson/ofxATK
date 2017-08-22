//
//  CREnvelope.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef CREnvelope_hpp
#define CREnvelope_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ATKSettings.hpp"
#include "BaseEnvelope.hpp"

class CREnvelope : public BaseEnvelope{
    
    double attackOffset, attackCoef, attackTCO;
    double decayOffset, decayCoef, decayTCO;

    double releaseOffset, releaseCoef, releaseTCO;
    float currentValue;
    int mode;//analog or digital
    int eType;
    int gate;
    
    
    bool legato;
    
    void setMode(unsigned int mode){
        switch(mode){
            case ANALOG:
                attackTCO = exp(-1.5);
                decayTCO = exp(-4.95);
                releaseTCO = decayTCO;
                break;
            case DIGITAL:
                attackTCO = 0.99999;
                decayTCO = exp(-11.05);//page297
                releaseTCO = decayTCO;
                break;
        }
    }
    
    void calcCoef(int type, float time){
        
        double numSamples = ATKSettings::sampleRate * (time*0.001);//it would have to be casted as double anyway
        cout << type << " " << numSamples << endl;
        switch(type){
            case ATTACK:
                attackCoef = exp(-log((1.0+attackTCO)/attackTCO)/numSamples);
                attackOffset = (1.0 + attackTCO)*(1.0-attackCoef);
                break;
            case DECAY:
                decayCoef = exp(-log((1.0+attackTCO)/attackTCO)/numSamples);
                decayOffset = (sustainLevel - decayTCO)*(1.0-decayCoef);
                break;
            case RELEASE:
                releaseCoef = exp(-log((1.0+attackTCO)/attackTCO)/numSamples);
                releaseOffset = -releaseTCO*(1.0-releaseCoef);
                break;
            default:
                ofLog(OF_LOG_WARNING, "coef not calculated, not a proper type");
                break;
        }
    }
    
    int state;
    
public:
    
    

    
    CREnvelope(){
        state = OFF;
        eType = ADSR;
        attackTime = 200;
        decayTime = 50;
        sustainLevel = 0.01;
        releaseTime = 400;
        currentValue = 0;
        mode = ANALOG;
        setMode(mode);
        calcCoef(ATTACK, attackTime);
        calcCoef(DECAY, decayTime);
        calcCoef(RELEASE, releaseTime);
    }
    
    CREnvelope(envelopeTypes eT){
        eType = eT;
    }
    
    inline void process(){
        switch(eType){
            case ADSR:
                
                break;
            case AR:
                
                break;
            case AD:
                
                break;
            case ASR:
                
                break;
            case AHDSR:
                
                break;
                
            default:
                ofLog(OF_LOG_WARNING, "no such envelope type");
                
        }
        switch(state){
            case OFF:
                currentValue = 0;
                break;
            case ATTACK:
                currentValue = attackOffset + currentValue * attackCoef;
                //check if ready for next state
                if(currentValue >= 1.0){
                    currentValue = 1.0;
                    state = DECAY;
                }
                break;
            case DECAY:
                currentValue = decayOffset + currentValue * decayCoef;
                if(currentValue <= sustainLevel){
                    currentValue = sustainLevel;
                    state = SUSTAIN;
                }
                
                break;
            case SUSTAIN:
                currentValue = sustainLevel;
                break;
                
            case RELEASE:
                currentValue = releaseOffset + currentValue * releaseCoef;
                if(currentValue <= 0.0){
                    currentValue = 0;
                    state = OFF;
                }
                break;
        }
    }
    
    float getValue(){
        return currentValue;
    }
    inline void setAttack(float timeMS){
        attackTime = timeMS;
        calcCoef(ATTACK, attackTime);
    }
    inline void setDecay(float timeMS){
        decayTime = timeMS;
        calcCoef(DECAY, decayTime);
    }
    inline void setSustain(float level){
        sustainLevel = level;
    }
    inline void setRelease(float timeMS){
        releaseTime = timeMS;
        calcCoef(RELEASE, releaseTime);
    }
    int getState(){
        return state;
    }
    
    
    inline void setADSR(float a, float d, float s, float r){
        attackTime = a;
        calcCoef(ATTACK, attackTime);
        decayTime = d;
        sustainLevel = s;
        calcCoef(DECAY, decayTime);
        releaseTime = r;
        calcCoef(RELEASE, releaseTime);
    }
    
};



#endif /* CREnvelope_hpp */
