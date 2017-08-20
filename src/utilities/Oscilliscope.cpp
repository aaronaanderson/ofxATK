//
//  Oscilliscope.cpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 7/17/17.
//
//

#include "Oscilliscope.hpp"

void Oscilliscope::input(float inputSample){
    
    if(!isPaused){
        
        buffer += inputSample;
        sppIndex++;
        if(sppIndex >= samplesPerPixel){
            displayArray[displayIndex] = (buffer*invSPP);//stored the inverse to avoid division
            sppIndex = 0;buffer = 0;//clear for next pixel
            displayIndex--;
            if(displayIndex < 0){displayIndex = width-1;}
        }
    }
}

void Oscilliscope::update(){
    line.clear();
    for(int i = 0; i < displayArray.size(); i++){
        float vertX = i+x;
        float vertY = ofMap(displayArray[i], lowestVal, highestVal, height + y, y);
        line.addVertex(vertX, vertY);
    }
}

void Oscilliscope::draw(){
    
    ofSetColor(120);
    ofDrawRectangle(x, y, width, height);
    ofSetColor(0, 355, 0);ofSetLineWidth(1.0);
    line.draw();

}
