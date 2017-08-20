//
//  RecordAudio.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/15/17.
//
//

#ifndef RecordAudio_hpp
#define RecordAudio_hpp

#include <stdio.h>
#include "SoundFile.hpp"

//use the SoundFile class to store a recording in ram, make it playable, and make it saveable
//TODO

class Recorder{
    
public:
    
    ~Recorder();
    Recorder(){
        
    }
    
    void setPath(string path);
    
    void start();
    void pause();
    void stop();
    
private:
    
    SoundFile storage;
    
};

#endif /* RecordAudio_hpp */
