//
//  TapInTapOut.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 8/10/17.
//
//

#ifndef TapInTapOut_hpp
#define TapInTapOut_hpp

#include <stdio.h>
#include "ATKSettings.hpp"

class TapIn{
    
public:
    
    float* buffer;//pointer to beginning of buffer
    int writeIndex;//keep track of needle head
    int size;//in samples
    TapIn(float bufferSizeMS){
        static const int _size = bufferSizeMS*0.001*ATKSettings::sampleRate;
        buffer = new float[_size];//allocate enough space for the buffer
        writeIndex = 0;//initialize the write Index
        for(int i = 0; i < size; i++){buffer[i] = 0; }//zero the buffer
        size = _size;    }
    
    void feed(float sample){//give the tapIn audio
        buffer[writeIndex] = sample;//store that sample
        writeIndex++;//progress the index
        if(writeIndex>=size){writeIndex = 0;}//border check
    }
};

class TapOut{
    
public:
    
    int readPoint;
    int size;
    float* ref;
    TapIn* inputReference;
    
    TapOut(TapIn* inRef, float time_ms){
        ref = inRef->buffer;
        size = inRef->size;
        readPoint = size-(time_ms*0.001*ATKSettings::sampleRate)-1;
        inputReference = inRef;
    }
    
    float getSample(){
        float temp = ref[readPoint];
        readPoint++;
        if(readPoint >= size){readPoint = 0;}
        return temp;
    }
    
    void setTime(float newTimeMS){
        int temp = newTimeMS*0.001*ATKSettings::sampleRate;
        readPoint = inputReference->writeIndex - temp;
        if(readPoint < 0){readPoint += size;}
    }
    
};

#endif /* TapInTapOut_hpp */
