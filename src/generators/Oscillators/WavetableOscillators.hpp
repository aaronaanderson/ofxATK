//
//  WavetableOscillators.hpp
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef WavetableOscillators_hpp
#define WavetableOscillators_hpp

#include <stdio.h>
#include "BaseOscillator.hpp"
#include "WavetableGeneration.hpp"
#include "Interpolation.hpp"


//-------------------------------------------------------------------
class WTSawtooth : public BaseOscillator{
    
public:
    WTSawtooth(){
        setFreq(440);
        amplitude = 1.0;
    }
    
    WTSawtooth(float initFreq){
        setFreq(initFreq);
        amplitude = 1.0;
    }
    
    void process(){
        currentOctave = whichOctave(frequency);
        float lowOct = linearInterp(sawTable->table[int(currentOctave)][(int)phase], sawTable->table[int(currentOctave)][int(phase+1)], phase);
        float highOct = linearInterp(sawTable->table[int(fmin(currentOctave+1, 9))][(int)phase], sawTable->table[int(fmin(currentOctave+1, 9))][int(phase+1)], phase);
        currentSample = linearInterp(lowOct, highOct, currentOctave);
        currentSample *= amplitude;
        phase += phaseInc;
        if(phase >= sawTable->getTableSize()-1){phase -= (sawTable->getTableSize()-1);}
        if(phase <= 0){phase = sawTable->getTableSize()-1;}
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = newFreq/sawTable->getFundamentalFreq();
    }
    
private:
    SawTable* sawTable = SawTable::getInstance();
    float currentOctave;
    
    float whichOctave(float _freq){//what tables should be drawn from
        if(_freq>sawTable->getLowFreqList()[9]){
            currentOctave = 9;
            return 9.0;
        }
        if(_freq <= sawTable->getLowFreqList()[0]){
            currentOctave = 0;
            return 0.0;
        }
        int index = 0;
        while(_freq > sawTable->getLowFreqList()[index]){
            if( _freq < sawTable->getLowFreqList()[index+1]){
                return index + ((_freq/sawTable->getLowFreqList()[index])-1.0);//return the position between tables.
            }else{
                index++;
            }
        }
    }
};

//-------------------------------------------------------------------
class WTSquare : public BaseOscillator{
    
public:
    WTSquare(){
        setFreq(440);
        amplitude = 1.0;
    }
    
    WTSquare(float initFreq){
        setFreq(initFreq);
        amplitude = 1.0;
    }
    
    void process(){
        currentOctave = whichOctave(frequency);
        float lowOct = linearInterp(squareTable->table[int(currentOctave)][(int)phase], squareTable->table[int(currentOctave)][int(phase+1)], phase);
        float highOct = linearInterp(squareTable->table[int(fmin(currentOctave+1, 9))][(int)phase], squareTable->table[int(fmin(currentOctave+1, 9))][int(phase+1)], phase);
        currentSample = linearInterp(lowOct, highOct, currentOctave);
        currentSample *= amplitude;
        phase += phaseInc;
        if(phase >= squareTable->getTableSize()-1){phase -= (squareTable->getTableSize()-1);}
        if(phase <= 0){phase = squareTable->getTableSize()-1;}
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = newFreq/squareTable->getFundamentalFreq();
    }
    
private:
    SquareTable* squareTable = SquareTable::getInstance();
    float currentOctave;
    
    float whichOctave(float _freq){//what tables should be drawn from
        if(_freq>squareTable->getLowFreqList()[9]){
            currentOctave = 9;
            return 9.0;
        }
        if(_freq <= squareTable->getLowFreqList()[0]){
            currentOctave = 0;
            return 0.0;
        }
        int index = 0;
        while(_freq > squareTable->getLowFreqList()[index]){
            if( _freq < squareTable->getLowFreqList()[index+1]){
                return index + ((_freq/squareTable->getLowFreqList()[index])-1.0);//return the position between tables.
            }else{
                index++;
            }
        }
    }
};

//-------------------------------------------------------------------
class WTTriangle : public BaseOscillator{
    
public:
    WTTriangle(){
        setFreq(440);
        amplitude = 1.0;
    }
    
    WTTriangle(float initFreq){
        setFreq(initFreq);
        amplitude = 1.0;
    }
    
    void process(){
        currentOctave = whichOctave(frequency);
        float lowOct = linearInterp(triangleTable->table[int(currentOctave)][(int)phase], triangleTable->table[int(currentOctave)][int(phase+1)], phase);
        float highOct = linearInterp(triangleTable->table[int(fmin(currentOctave+1, 9))][(int)phase], triangleTable->table[int(fmin(currentOctave+1, 9))][int(phase+1)], phase);
        currentSample = linearInterp(lowOct, highOct, currentOctave);
        currentSample *= amplitude;
        phase += phaseInc;
        if(phase >= triangleTable->getTableSize()-1){phase -= (triangleTable->getTableSize()-1);}
        if(phase <= 0){phase = triangleTable->getTableSize()-1;}
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = newFreq/triangleTable->getFundamentalFreq();
    }
    
private:
    TriangleTable* triangleTable = TriangleTable::getInstance();
    float currentOctave;
    
    float whichOctave(float _freq){//what tables should be drawn from
        if(_freq>triangleTable->getLowFreqList()[9]){
            currentOctave = 9;
            return 9.0;
        }
        if(_freq <= triangleTable->getLowFreqList()[0]){
            currentOctave = 0;
            return 0.0;
        }
        int index = 0;
        while(_freq > triangleTable->getLowFreqList()[index]){
            if( _freq < triangleTable->getLowFreqList()[index+1]){
                return index + ((_freq/triangleTable->getLowFreqList()[index])-1.0);//return the position between tables.
            }else{
                index++;
            }
        }
    }
};

class WTSine : public BaseOscillator{
    
public:
    WTSine(){
        setFreq(440);
        amplitude = 1.0;
    }
    
    WTSine(float initFreq){
        setFreq(initFreq);
        amplitude = 1.0;
    }
    
    void process(){
        currentSample = linearInterp(sineTable->table[int(phase)], sineTable->table[int(phase+1)], phase);
        currentSample *= amplitude;
        phase += phaseInc;
        if(phase >= sineTable->getTableSize()-1){phase -= (sineTable->getTableSize()-1);}
        if(phase <= 0){phase = sineTable->getTableSize()-1;}
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = newFreq/(double)sineTable->getFundamentalFreq();
    }
    
private:
    SineTable* sineTable = SineTable::getInstance();

};

class WTCosine : public BaseOscillator{
public:
    WTCosine(){
        setFreq(440);
        amplitude = 1.0;
        quarterTableSize = sineTable->getTableSize()*0.25;
    }
    
    WTCosine(float initFreq){
        setFreq(initFreq);
        amplitude = 1.0;
        quarterTableSize = sineTable->getTableSize()*0.25;
    }
    
    void process(){
        float adjustedPhase = fmod(phase+quarterTableSize, sineTable->getTableSize());
        currentSample = linearInterp(sineTable->table[int(adjustedPhase)], sineTable->table[int(adjustedPhase + 1)], phase);
        currentSample *= amplitude;
        phase += phaseInc;
        if(phase >= sineTable->getTableSize()-1){phase -= (sineTable->getTableSize());}
        if(phase <= 0){phase += sineTable->getTableSize();}
    }
    
    void setFreq(float newFreq){
        frequency = newFreq;
        phaseInc = frequency/(double)sineTable->getFundamentalFreq();
    }
    
private:
    SineTable* sineTable = SineTable::getInstance();
    float quarterTableSize;
    
};

#endif /* WavetableOscillators_hpp */
