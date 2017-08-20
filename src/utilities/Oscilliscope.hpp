//
//  Oscilliscope.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#ifndef Oscilliscope_hpp
#define Oscilliscope_hpp

#include <stdio.h>
#include "ofMain.h"

class Oscilliscope{
    
public:
    ~Oscilliscope();
    Oscilliscope(){
        lowestVal = -1.0;
        highestVal = 1.0;
        width = height = 400;x = y = 0;
        displayArray.resize(height, 0.0);
        displayIndex = width-1;
        buffer = 0;//single sample buffer, no need to store all SPP
        sppIndex = 0;
        samplesPerPixel = 8;
        invSPP = 1/float(samplesPerPixel);
        readyForFrame = true;
    }
    
    void setRange(float low, float high){
        lowestVal = low;
        highestVal = high;
    }
    void setSamplesPerPixel(unsigned int spp){
        samplesPerPixel = spp;
        invSPP = 1/float(spp);//only calc this once
    }
    void resize(int newWidth, int newHeight){
        width = newWidth; height = newHeight;
        displayArray.resize(width, 0.0);
        displayIndex = 0; sppIndex = 0; buffer = 0;
    }
    void position(int newX, int newY){
        x = newX; y = newY;
    }
    
    void input(float inputSample);
    void update();
    void draw();
    
    void pause(){isPaused = true;}
    void resume(){isPaused = false;}
    
private:
    
    
    float lowestVal, highestVal;
    unsigned int samplesPerPixel; float invSPP;
    float x,y,width,height;
    
    vector<float> displayArray;
    int displayIndex;
    
    float buffer;//store the average of samples per pixel
    unsigned int sppIndex;
    
    ofPolyline line;
    
    bool isPaused;
    bool readyForFrame;//don't animate, just show the full width's worth of averages when
    //new frame is ready
};

#endif /* Oscilliscope_hpp */
