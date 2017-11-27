//
//  Meters.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/16/17.
//
//

#ifndef Meters_hpp
#define Meters_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Smoother.hpp"

//-----------------------------------------------------------------------meters
class CircleMeter {
    
public:
    void setup(ofVec2f _location, float _radius, int sampleLength);
    void setup(float x, float y, float radius, int sampleLength);
    
    void feedMeter(float input);
    void update();
    void draw();
    
    void clearClip() {
        clipped = false;
    }
    void setResolution(int _resolution) {
        if (_resolution > 2) {
            resolution = _resolution;
        }else{
            _resolution = 2;
        }
    }
    
private:
    
    SmoothValue rms;
    ofVec2f location;
    float radius;
    bool clipped;
    int counter;
    int numToAverage;
    float accumulatedSamples;
    double numToAverageRecip;
    
    int resolution;//resolution of circle
    
};


//-----standard meter

class Meter {
    
public:
    

    Meter(ofVec2f _location, int _width, int _height, int sampleLength){
        clipped = false;
        counter = 0;
        location = _location;
        width = _width;
        height = _height;
        
        if (sampleLength > 20) {
            numToAverage = sampleLength;
        }
        else {
            numToAverage = 20;
        }
        
        if (width > height) {
            mode = HORIZONTAL;
        }else {
            mode = VERTICAL;
        }
        
        numToAverageRecip = 1 / (double)numToAverage;
        rms.smoother = new ParameterSmoother(400, ofGetFrameRate());
    }
    
    void feedMeter(float input);
    void update();
    void draw();
    
    void clearClip() {
        clipped = false;
    }
    
private:
    enum layout{
        VERTICAL,
        HORIZONTAL
    };

    SmoothValue rms;
    ofVec2f location;
    bool clipped;
    int counter;
    int numToAverage;
    float accumulatedSamples;
    double numToAverageRecip;
    
    int width, height;
    int mode;
};
#endif /* Meters_hpp */
