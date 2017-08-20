//
//  SoundPlayer.cpp
//
//  Created by Aaron Anderson on 8/15/17.
//
//

/*
 references a SoundFile object and offers various playback options

 */
#include "SoundPlayer.hpp"

//--------------------------------------------------------------
void SoundPlayer::play(){
    phaseInc = reference->getSFSR()/ATKSettings::sampleRate;
    isPlaying = true;
}
//--------------------------------------------------------------
void SoundPlayer::play(float speed){
    phaseInc = (reference->getSFSR()*speed)/ATKSettings::sampleRate;
    isPlaying = true;
    cout << ATKSettings::sampleRate << " " <<  reference->getSFSR() << endl;
}
//--------------------------------------------------------------
void SoundPlayer::setSpeed(float speed){
    phaseInc = (reference->getSFSR()*speed)/ATKSettings::sampleRate;
}
//--------------------------------------------------------------
void SoundPlayer::setLocation(float location){
    if(location > 1 || location < 0){
        phase = 0;
        ofLog(OF_LOG_WARNING, "location must be between 0 and 1");
    }else{
        phase = reference->getSize() * location;
    }
}
//--------------------------------------------------------------
void SoundPlayer::process(){
    if(isPlaying){
        
        switch(interpolation){
            case LINEAR:
                if(loopMode == AUTODUCK){
                    //TODO
                }else{
                    currentSample = linearInterp(reference->getBuffer()[int(phase)], reference->getBuffer()[int(phase)+1], phase);
                }
                break;
            case CUBIC:
                //TODO
            {//need to use the curly since making a new variable
                float* bffrPtr = reference->getBuffer();//need to use this 4 times, so save some space
                currentSample = cubicInterp(bffrPtr[int(phase-1)], bffrPtr[int(phase)], bffrPtr[int(phase+1)],bffrPtr[int(phase+2)],phase);
            }
                break;
            case NONE:
                if(loopMode == AUTODUCK){
                    //TODO
                }else{
                    currentSample = reference->getBuffer()[int(phase)];
                }
                break;
            default:
                ofLog(OF_LOG_WARNING, "something wrong with interp mode");
        }
        phase += phaseInc;//phaseInc can be negative
        
        if(loopEnabled){
            switch(loopMode){
                case STANDARD:
                    if(phase >= reference->getSize()+1){//wwrap if playing forward
                        phase -= reference->getSize();
                    }
                    if(phase <= 1){//wrap if playing backwards
                        phase += reference->getSize();
                    }
                    break;
                case PALINDROME:
                    if(phase >= reference->getSize()+1){//if end is reached
                        phaseInc *= -1.f;//reverse direction
                    }
                    if(phase < 1){//needs attention, this should be 1 (the real start sample)
                        //^^it's fine now but will break when cubic interp
                        phaseInc *= -1.f;
                    }
                    break;
                case AUTODUCK:
                    //cross fade to the appropriate spot in the beginning
                    //TODO
                    break;
            }
        }else{//if not looping
            if(phase >= reference->getSize()){
                phase = 0; isPlaying = false;
            }
        }
        
        
    }else{//if not playing
        currentSample = 0;
    }
}

void SoundPlayer::draw(){
    ofSetColor(ofColor(255));
    ofSetLineWidth(1.5);
    float xPos = (phase/float(reference->getSize())) * reference->getWidth()+reference->getX();
    ofDrawLine(xPos, reference->getY(), xPos, reference->getHeight() + reference->getY());
}
