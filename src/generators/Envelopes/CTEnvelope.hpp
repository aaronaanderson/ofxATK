//
//  CTEnvelope.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef CTEnvelope_hpp
#define CTEnvelope_hpp

#include <stdio.h>
#include "BaseEnvelope.hpp"

class CTEnvelope : public BaseEnvelope{
    
public:
    /** with default construction **/
    CTEnvelope(){
        attackTime = 100;
        setInc(ATTACK);
        decayTime = 20;
        sustainLevel = 0.7;
        releaseTime = 150;
        setInc(DECAY);
        setInc(RELEASE);
        
        currentValue = 0.0;
        legato = false;
        state = OFF;
        gate = 0;
        type = ADSR;
    }
    CTEnvelope(float iAttack, float iDecay, float iSustain, float iRelease){
        attackTime = iAttack;
        decayTime = iDecay;
        sustainLevel = iSustain;
        releaseTime = iRelease;
        setInc(ATTACK);
        setInc(DECAY);
        setInc(RELEASE);
        
        currentValue = 0.0;
        legato = false;
        state = OFF;
        gate = 0;
        type = ADSR;
    }
    
    void process(){
        switch(type){
            case ADSR://standard
                switch(state){
                    case ATTACK:
                        currentValue += attackInc;
                        if(currentValue >= 1.0){
                            currentValue = 1.0;
                            state = DECAY;
                        }
                        break;
                    case DECAY:
                        currentValue -= decayInc;
                        if(currentValue <= sustainLevel){
                            currentValue = sustainLevel;
                            state = SUSTAIN;
                        }
                        break;
                    case SUSTAIN:
                        //no need to do anything here
                        break;
                    case RELEASE:
                        currentValue -= releaseInc;
                        if(currentValue <= 0.0){
                            currentValue = 0;
                            state = OFF;
                        }
                        break;
                    case OFF:
                        break;
                   // default:
                        //cout << "error in adsr logic" << endl;
                }
                
                break;//end ADSR;
            case AR:
                switch(state){
                    case ATTACK:
                        currentValue += attackInc;
                        if(currentValue >= 1.0){
                            currentValue = 1.0;
                            state = DECAY;
                        }
                        break;
                    case DECAY:
                        currentValue -= decayInc;
                        if(currentValue <= 0.0){
                            currentValue = 0.0;
                            state = OFF;
                        }
                }
           // default:
                //cout << "type not yet available" << endl;
        }
        
    }
    
    void setAttack(float newAttackTime){
        attackTime = newAttackTime;
        setInc(ATTACK);
    }
    void setDecay(float newDecayTime){
        decayTime = newDecayTime;
        setInc(DECAY);
    }
    void setSustain(float newSustainLevel){
        sustainLevel = ofClamp(newSustainLevel, 0.0, 1.0);
        setInc(DECAY);
        setInc(RELEASE);
    }
    void setRelease(float newReleaseTime){
        releaseTime = newReleaseTime;
        setInc(RELEASE);
    }

    
private:
    
    float attackInc, decayInc, releaseInc;//increments and decrements for linear progression
    
    void setInc(int i){
        switch(i){
            case ATTACK:
                attackInc = 1/(ATKSettings::sampleRate*(attackTime*0.001));
               // cout<< "attack inc: " << attackInc <<endl;
                break;
            case DECAY:
                decayInc = (1.f-sustainLevel)/(ATKSettings::sampleRate*(decayTime*0.001));
                //cout << "decay inc: " << decayInc << endl;
                break;
            case RELEASE:
                releaseInc = sustainLevel/(ATKSettings::sampleRate*(releaseTime*0.001));
                break;
           // default:
               // cout << "no such state, or state does not have an increment value" << endl;
        }
    }
    
};

#endif /* CTEnvelope_hpp */
