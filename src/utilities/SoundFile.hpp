//
//  SoundFile.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/15/17.
//
//

#ifndef SoundFile_hpp
#define SoundFile_hpp

#include <stdio.h>
#include <ofMain.h>
#include <ofxPortSF.hpp>
#include <ATKSettings.hpp>
#include <Interpolation.hpp>

class SoundFile{
    
public:
    ~SoundFile();
    SoundFile(){
        drawResolution = 45;
    }
    
    SoundFile(string path){
        drawResolution = 45;
        cellSizes.resize(drawResolution);
        SoundFile::load(path);
    }
    
    void resize(unsigned int sizeInSamps);
    
    void clear();
    void erase();
    void draw();
    void draw(int x, int y, int width, int height);
    
    void load();
    void load(string dataPath);
    
    void normalize();
    void normalize(float level);
    
    double getSFSR(){
        return soundFileSampleRate;
    }
    unsigned int getSize(){
        return size;
    }

    float* getBuffer(){
        return buffer.data();
    }
    void setDrawPosition(int newX, int newY){
        x = newX; y = newY;
    }
    void setDrawSize(int newWidth, int newHeight){
        width = newWidth; height = newHeight;
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }
    float getWidth(){
        return width;
    }
    float getHeight(){
        return height;
    }
    
private:
    
    vector<float> buffer;
    unsigned int size;
    unsigned int realSize;//adjusted for interp
    double soundFileSampleRate;
    
    
    //Used for loading sound
    PSF_PROPS soundFileProperties;//will be auto-populated when file loaded
    long framesRead, totalFramesRead;//framesread used to check if there are still more frames in file
    int ifd = -1;//identification for the sound file, used by the library
    float* frame = NULL;//location of currently read frame
    vector<float> soundFile;//actual stored sound file
    
    //used to play sound
    double phase, phaseInc;
    bool isPlaying;
    float currentSample;
    float channels;//cast as float since will need to be anyway.
    
    //used to display sound file
    float x, y, width, height;
    int drawResolution;
    vector<float> cellSizes;//stores the RMS of audio
};
#endif /* SoundFile_hpp */
