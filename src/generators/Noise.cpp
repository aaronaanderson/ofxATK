//
//  Noise.cpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/16/17.
//
//

#include "Noise.hpp"


int PinkNoise::findTable(int index){
    
    if(index%2 == 0){
        return 0;
    }else if((index+1)%4 == 0){
        return 1;
    }else if((index + 3)%8 == 0){
        return 2;
    }else if((index + 7)%16 == 0){
        return 3;
    }else if(index == 15){//there is only one in this table
        return 4;
    }
    return 0;
}

int PinkNoise::findEntry(int table, int index){
    
    switch(table){
        case 0:
            return index/2.f;
            break;
        case 1:
            return (index-1)/4.f;
            break;
        case 2:
            return (index-3)/8.f;
            break;
            
        case 3:
            return (index-7)/16.f;
            break;
            
        case 4:
            return 0;
            break;
        default:
            ofLog(OF_LOG_WARNING, "issue with table in Pink Noise");
	    return 0;
    }
}

void PinkNoise::process(){
    int table = findTable(x);
    int index = findEntry(table, x);
    float oldValue, newValue;
    switch(table){
        case 0:
            oldValue = table0[index];
            newValue = ofRandom(-1.0, 1.0);
            table0[index] = newValue;
            break;
        case 1:
            oldValue = table1[index];
            newValue = ofRandom(-1.0, 1.0);
            table1[index] = newValue;
            break;
        case 2:
            oldValue = table2[index];
            newValue = ofRandom(-1.0, 1.0);
            table2[index] = newValue;
            break;
        case 3:
            oldValue = table3[index];
            newValue = ofRandom(-1.0, 1.0);
            table3[index] = newValue;
            break;
        case 4:
            oldValue = table4[index];
            newValue = ofRandom(-1.0, 1.0);
            table4[index] = newValue;
            break;
        default:
            ofLog(OF_LOG_WARNING, "invalid table in Pink Noise");
    }
    float difference = newValue - oldValue;
    currentSample = previousValue + difference;
    previousValue = currentSample;
    //currentSample += ofRandom(-1.0, 1.0);
}

float PinkNoise::getSample(){
    return currentSample;
}
