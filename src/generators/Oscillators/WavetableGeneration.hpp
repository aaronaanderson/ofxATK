//
//  WavetableGeneration.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef WavetableGeneration_hpp
#define WavetableGeneration_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ATKSettings.hpp"
#define NUMTABLES 10
#define TABLESIZE 2048


//I'm using a singleton class here. I think it is appropriate. This will
//allow only one instance of the wavetable to be generated no matter how
//many wt oscillators are created. If you are reading this and know a better
//way, please feel free to contact me!


//-------------------------------------------------------------------
class SawTable{
private://not necessary, private by default. just highlighting this point.
    
    static SawTable* _instance;
    float* lowestFreqList = new float[NUMTABLES];//lowest frequency useful for each octave
    
    float currentLow = 20;//lowest octave's lowest frequency
    float nyquist = 20000;
    float tableFundamentalFreq = ATKSettings::sampleRate/float(TABLESIZE);
    SawTable();//private constructor
    
public:
    //a function to get the sawtable instance.
    //if it has already been constructed, just return it
    //if it has not been constructed, construct then return
    float table[NUMTABLES][TABLESIZE];
    
    static SawTable* getInstance(){
        if(_instance == nullptr){
            _instance = new SawTable();
        }
        return _instance;
    }
    
    float getFundamentalFreq(){
        return tableFundamentalFreq;
    }
    
    float* getLowFreqList(){
        return lowestFreqList;
    }
    
    int getTableSize(){
        return TABLESIZE;
    }
    
};

//-------------------------------------------------------------------
class SquareTable{
private://not necessary, private by default. just highlighting this point.
    
    static SquareTable* _instance;
    float* lowestFreqList = new float[NUMTABLES];//lowest frequency useful for each octave
    
    float currentLow = 20;//lowest octave's lowest frequency
    float nyquist = 20000;
    float tableFundamentalFreq = ATKSettings::sampleRate/float(TABLESIZE);
    SquareTable();//private constructor
    
public:
    //a function to get the sawtable instance.
    //if it has already been constructed, just return it
    //if it has not been constructed, construct then return
    float table[NUMTABLES][TABLESIZE];
    
    static SquareTable* getInstance(){
        if(_instance == nullptr){
            _instance = new SquareTable();
        }
        return _instance;
    }
    
    float getFundamentalFreq(){
        return tableFundamentalFreq;
    }
    
    float* getLowFreqList(){
        return lowestFreqList;
    }
    
    int getTableSize(){
        return TABLESIZE;
    }
    
};

//-------------------------------------------------------------------
class TriangleTable{
private://not necessary, private by default. just highlighting this point.
    
    static TriangleTable* _instance;
    float* lowestFreqList = new float[NUMTABLES];//lowest frequency useful for each octave
    
    float currentLow = 20;//lowest octave's lowest frequency
    float nyquist = 20000;
    float tableFundamentalFreq = ATKSettings::sampleRate/float(TABLESIZE);
    TriangleTable();//private constructor
    
public:
    //a function to get the sawtable instance.
    //if it has already been constructed, just return it
    //if it has not been constructed, construct then return
    float table[NUMTABLES][TABLESIZE];
    
    static TriangleTable* getInstance(){
        if(_instance == nullptr){
            _instance = new TriangleTable();
        }
        return _instance;
    }
    
    float getFundamentalFreq(){
        return tableFundamentalFreq;
    }
    
    float* getLowFreqList(){
        return lowestFreqList;
    }
    
    int getTableSize(){
        return TABLESIZE;
    }
    
};

//-------------------------------------------------------------------
class SineTable{//this one is simpler, just one octave
private://not necessary, private by default. just highlighting this point.
    
    static SineTable* _instance;
    float tableFundamentalFreq = ATKSettings::sampleRate/float(TABLESIZE);
    SineTable();//private constructor
    
public:
    //a function to get the sawtable instance.
    //if it has already been constructed, just return it
    //if it has not been constructed, construct then return
    float table[TABLESIZE];
    
    static SineTable* getInstance(){
        if(_instance == nullptr){
            _instance = new SineTable();
        }
        return _instance;
    }
    
    float getFundamentalFreq(){
        return tableFundamentalFreq;
    }
    
    int getTableSize(){
        return TABLESIZE;
    }
    
};
#endif /* WavetableGeneration_hpp */
