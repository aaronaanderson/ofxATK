//
//  WavetableGeneration.cpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#include "WavetableGeneration.hpp"

SawTable::SawTable(){
    //keep tabs on the lowest frequency for each octave
    for(int i = 0; i < NUMTABLES; i++){//set for each octave
        lowestFreqList[i] = currentLow;
        currentLow *= 2.f;//jump to the next octave
    }
    //generate the harmonics for each sample of each table;
    for(int i = 0; i < NUMTABLES; i++){
        for(int j = 0; j < TABLESIZE; j++){
            float numHarmonics = 1;
            table[i][j] = 0;
            while(lowestFreqList[i]*numHarmonics < nyquist){//Add harmonics until
                //nyquist is reached
                float theta = (j*TWO_PI*numHarmonics)/float(TABLESIZE-1);
                table[i][j] += sin(theta) * (-1/float(numHarmonics));
                numHarmonics +=1;
            }
        }
    }
    
    //normalize the tables-----------------------------------------
    for(int i = 0; i < NUMTABLES; i++){
        //find the largest ignoring polarity
        float largestValue = 0;
        for(int j = 0; j < TABLESIZE; j++){
            if(fabs(table[i][j]) > largestValue){
                largestValue = fabs(table[i][j]);
            }
        }
        float scalarValue = 1/float(largestValue);//calculate the adjustment value
        //multiply the adjustment
        for(int j = 0; j < TABLESIZE; j++){
            table[i][j] *= scalarValue;
        }
    }
}
SawTable* SawTable::_instance = nullptr;


//------------------------------------------------
SquareTable::SquareTable(){
    //keep tabs on the lowest frequency for each octave
    for(int i = 0; i < NUMTABLES; i++){//set for each octave
        lowestFreqList[i] = currentLow;
        currentLow *= 2.f;//jump to the next octave
    }
    
    //generate the harmonics for each sample of each table;
    for(int i = 0; i < NUMTABLES; i++){
        for(int j = 0; j < TABLESIZE; j++){
            float numHarmonics = 1;
            table[i][j] = 0;
            while(lowestFreqList[i]*numHarmonics < nyquist){
                float theta = (j*TWO_PI*numHarmonics)/float(TABLESIZE-1);
                table[i][j] += sin(theta) * (1/float(numHarmonics));
                numHarmonics +=2;
            }
        }
    }
    
    //normalize the tables-----------------------------------------
    for(int i = 0; i < NUMTABLES; i++){
        //find the largest ignoring polarity
        float largestValue = 0;
        for(int j = 0; j < TABLESIZE; j++){
            if(fabs(table[i][j]) > largestValue){
                largestValue = fabs(table[i][j]);
            }
        }
        float scalarValue = 1/float(largestValue);//calculate the adjustment value
        //multiply the adjustment
        for(int j = 0; j < TABLESIZE; j++){
            table[i][j] *= scalarValue;
        }
    }
}
SquareTable* SquareTable::_instance = nullptr;


//------------------------------------------------
TriangleTable::TriangleTable(){
    //keep tabs on the lowest frequency for each octave
    for(int i = 0; i < NUMTABLES; i++){//set for each octave
        lowestFreqList[i] = currentLow;
        currentLow *= 2.f;//jump to the next octave
    }
    
    //generate the harmonics for each sample of each table;
    for(int i = 0; i < NUMTABLES; i++){
        for(int j = 0; j < TABLESIZE; j++){
            float numHarmonics = 1;
            table[i][j] = 0;
            while(lowestFreqList[i]*numHarmonics < nyquist){
                float theta = (j*TWO_PI*numHarmonics)/float(TABLESIZE-1);
                table[i][j] += cos(theta) * (1/float(numHarmonics*numHarmonics));
                numHarmonics +=2;
            }
        }
    }
    
    //normalize the tables-----------------------------------------
    for(int i = 0; i < NUMTABLES; i++){
        //find the largest ignoring polarity
        float largestValue = 0;
        for(int j = 0; j < TABLESIZE; j++){
            if(fabs(table[i][j]) > largestValue){
                largestValue = fabs(table[i][j]);
            }
        }
        float scalarValue = 1/float(largestValue);//calculate the adjustment value
        //multiply the adjustment
        for(int j = 0; j < TABLESIZE; j++){
            table[i][j] *= scalarValue;
        }
    }
}
TriangleTable* TriangleTable::_instance = nullptr;

//------------------------------------------------
SineTable::SineTable(){

    for(int j = 0; j < TABLESIZE; j++){
        float numHarmonics = 1;
        float theta = ofMap(j, 0, TABLESIZE-1, 0, TWO_PI);
        table[j] = sin(theta);
    }
    // no need to normalize
}
SineTable* SineTable::_instance = nullptr;
