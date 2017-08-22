//
//  Noise.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/16/17.
//
//

#ifndef Noise_hpp
#define Noise_hpp

#include <stdio.h>
#include "ofMain.h"

//--------------------
//white noise is just here for completion sake. It's silly to use this class
class WhiteNoise{
    
public:
    ~WhiteNoise();
    WhiteNoise(){
        
    }
    
    float getSample(){
        return ofRandom(-1.0, 1.0);
    }
    void process(){
        //nothing to do here
    }
    
};

//--------------------
//implementing Gardner's generator with McCartney's improvements
class PinkNoise {
    
public:
    //~PinkNoise();
    PinkNoise(){
        for(int i = 0; i < 16; i++){
            table0[0] = ofRandom(-1.0, 1.0);
        }
        for(int i = 0; i < 8; i++){
            table1[i] = ofRandom(-1.0, 1.0);
        }
        for(int i = 0; i < 4; i++){
            table2[i] = ofRandom(-1.0, 1.0);
        }
        for(int i = 0; i < 2; i++){
            table3[i] = ofRandom(-1.0, 1.0);
        }
        table4[0] = ofRandom(-1.0, 1.0);
        previousValue = 0;
        currentSample = 0;
    }
    
    void process();
    float getSample();
    
private:
    float table0[16];
    float table1[8];
    float table2[4];
    float table3[2];
    float table4[1];
    //there are 31 table entries
    /*
     x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|
      x | x | x | x | x | x | x | x
        x   |   x   |   x   |   x
            x       |       x
                    x
     
     This can be thought of in terms of a step sequencer. Each
     tick the sequencer increments one value. The value at that location 
     is replaced with a new random sample. The sum of all values is the result. 
     */
    
    unsigned int x;
    int findTable(int index);
    int findEntry(int table, int index);
    float tableSum();
    float currentSample;
    float previousValue;

};

//--------------------
class BrownNoise{
    
public:
   // ~BrownNoise();
    BrownNoise(){
        largeVal = 0;
        currentSample = 0;
        jumpMax = 1.0;
    };
    
    BrownNoise(float jumpMax){
        largeVal = 0;
        currentSample = 0;
        
    }
    
    inline void process(){
        
        while(true){
            float r = ofRandom(-jumpMax, jumpMax);
            largeVal += r;
            if( largeVal < -16.f || largeVal >= 16.f){
                largeVal -= r;
            }
            else {
                currentSample = largeVal * 0.0625f;
                break;
            }
        }
    }
    
    float getSample(){
        return currentSample;
    }
    
    void setJumpMax(float newJumpMax){
        jumpMax = newJumpMax;
    }
    
private:
    float currentSample;
    float largeVal;//used to interact more freely with -1, 1 borders;
    float jumpMax;
};
#endif /* Noise_hpp */
