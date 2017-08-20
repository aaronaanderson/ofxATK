//
//  Meters.cpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/16/17.
//
//

#include "Meters.hpp"


//--------------------------------------------------------
void CircleMeter::setup(ofVec2f _location, float _radius, int sampleLength) {
    clipped = false;
    counter = 0;
    location = _location;
    radius = _radius;
    resolution = 30;
    
    if (sampleLength > 100) {
        numToAverage = sampleLength;
    }else{
        numToAverage = 100;
    }
    
    numToAverageRecip = 1 / (double)numToAverage;
    
    rms.smoother = new ParameterSmoother(50, 60);
    
}
void CircleMeter::setup(float x, float y, float _radius, int sampleLength) {
    clipped = false;
    counter = 0;
    location.x = x;
    location.y = y;
    radius = _radius;
    resolution = 30;
    
    if (sampleLength > 100) {
        numToAverage = sampleLength;
    }
    else {
        numToAverage = 100;
    }
    numToAverageRecip = 1 / (double)numToAverage;
    
    rms.smoother = new ParameterSmoother(50, 60);
}

void CircleMeter::feedMeter(float input) {
    
    if (input >= 0.99) {
        clipped = true;
    }
    if (input > 0) {
        accumulatedSamples += input;
    }else {
        accumulatedSamples += input * -1;
    }
    counter++;
    if (counter >= numToAverage) {
        rms.targetValue = accumulatedSamples * numToAverageRecip;
        accumulatedSamples = 0;
        counter = 0;
    }
}
void CircleMeter::update() {
    rms.currentValue = rms.smoother->process(rms.targetValue);
}

void CircleMeter::draw() {
    
    ofSetCircleResolution(resolution);
    if (clipped) {
        ofSetColor(200, 20, 20);
        ofDrawCircle(location, radius*1.08);
    }
    ofSetColor(0);
    ofDrawCircle(location, radius);
    ofSetColor(20, 200, 20);
    ofDrawCircle(location, rms.currentValue*radius);
}

//--------------------------------------------------------
void Meter::setup(ofVec2f _location, int _width, int _height, int sampleLength) {
    clipped = false;
    counter = 0;
    location = _location;
    width = _width;
    height = _height;
    
    if (sampleLength > 100) {
        numToAverage = sampleLength;
    }
    else {
        numToAverage = 100;
    }
    
    if (width > height) {
        mode = HORIZONTAL;
    }else {
        mode = VERTICAL;
    }
    
    numToAverageRecip = 1 / (double)numToAverage;
    rms.smoother = new ParameterSmoother(400, ofGetFrameRate());
}

void Meter::feedMeter(float input) {
    
    if (fabs(input) >= 0.99) {
        clipped = true;
    }
    
    accumulatedSamples += fabs(input);
    
    counter++;
    if (counter >= numToAverage) {
        rms.targetValue = (accumulatedSamples * numToAverageRecip);
        
        accumulatedSamples = 0;
        counter = 0;
    }
}
void Meter::update() {
    rms.currentValue = rms.smoother->process(rms.targetValue);
}

void Meter::draw() {
    switch (mode) {
        case VERTICAL:
            ofSetColor(0);
            ofDrawRectangle(location.x, location.y, width, height);
            if (clipped) {
                ofSetColor(200, 20, 20);
                ofDrawRectangle(location.x, location.y, width, height*0.05);
            }
            ofSetColor(20, 200, 20);
            ofDrawRectangle(location.x, location.y + height - (rms.currentValue*height), width, (height*rms.currentValue));
            break;
        case HORIZONTAL:
            ofSetColor(0);
            ofDrawRectangle(location.x, location.y, width, height);
            if (clipped) {
                ofSetColor(200, 20, 20);
                ofDrawRectangle(location.x + width, location.y, width*0.05, height);
            }
            ofSetColor(20, 200, 20);
            ofDrawRectangle(location.x, location.y, ofMap(20*log10(rms.currentValue),-90, 0, 0, width) , height);
            break;
        default:
            break;
    }
    
}
