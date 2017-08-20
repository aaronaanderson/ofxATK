//
//  ATKSettings.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/9/17.
//
//

#ifndef ATKSettings_hpp
#define ATKSettings_hpp

#include <stdio.h>

class ATKSettings{
    
public:
    static double sampleRate;
    static int bufferSize;
    void setup(int _sampleRate, int _bufferSize){
        ATKSettings::sampleRate = _sampleRate;
        ATKSettings::bufferSize = _bufferSize;
    };
    
private:
    ATKSettings(){
        
    }
};
#endif /* ATKSettings_hpp */
