//
//  SoundPlayer.hpp
//  examples-soundFilePlayer
//


/*
 references a SoundFile object and offers various playback options
 
 */

#ifndef SoundPlayer_hpp
#define SoundPlayer_hpp

#include <stdio.h>
#include "SoundFile.hpp"

class SoundPlayer{
    
public:
    
    SoundPlayer(SoundFile* _reference, float startPosition = 1, bool initLoopEnabled = false){
        reference = _reference;
        interpolation = LINEAR;
        phase = startPosition;
        phaseInc = 0;
        
        isPlaying = false;
        autoDuckTime = 20;//ms
        loopEnabled = initLoopEnabled;
        loopMode =  STANDARD;
    }
    
    void play();
    void play(float speed);
    void setSpeed(float speed);
    void setLocation(float location);//0 - 1;
    
    void process();//for consistency
    float getSample(){
        return currentSample;
    }
    
    void draw();//draw the current position over soundbuffer drawing
    
    void loop(bool newLoopEnabled){
        loopEnabled = newLoopEnabled;
    }
    bool getLoopEnabled(){
        return loopEnabled;
    }
    int getLoopMode(){
        return loopMode;
    }
    void setLoopMode(int newLoopMode){
        loopMode = newLoopMode;
    }
    
    void setLoopEnabled(bool newLE){
        loopEnabled = newLE;
    }
    
private:
    SoundFile* reference;
    bool loopEnabled, isPlaying;
    int loopMode;
    enum loopModes{
        STANDARD,//begining to end, immediately back to beginning
        PALINDROME,//beginning to end to beginning to end etc
        AUTODUCK //le quack (auto-crossfade from end to beginning or beginning to end)
    };
    float autoDuckTime;
    float phase, phaseInc;
    float currentSample;
    int interpolation;
    enum interpolationTypes{
        NONE,
        LINEAR,
        CUBIC
    };
    
};
#endif /* SoundPlayer_hpp */
