//
//  Spectroscope.cpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#include "Spectroscope.hpp"

void Spectroscope::update(){
    //  *   fft.fft(input.data(), re.data(), im.data());
    //  *   fft.ifft(output.data(), re.data(), im.data());
   // fft.fft(inBuffer, );
    
    fft.fft(inBuffer.data(), real.data(), imaginary.data());
    fft.ifft(outBuffer.data(), real.data(), imaginary.data());
    //  *   fft.fft(input.data(), re.data(), im.data());
    //  *   fft.ifft(output.data(), re.data(), im.data());
    
    line.clear();
    line.curveTo(ofPoint(x, y+height));
    float xInc = width/(float(numSegments)-1); float xPos = 0;
    for(int i = 0; i < numSegments;i++){
       // int freqY = ofMap(curvedX[i], x, width+20, 5, real.size());
        int freqY = ofMap(xPos, 0, width, 2, real.size());
        int tempY = height-(calcMagnitude(freqY));
        line.curveTo(ofPoint(xPos+x,tempY+y));
        xPos += xInc;
    }
    line.curveTo(ofPoint(width+x, height+y));
    
    for(int i = 0; i < img.getHeight(); i++){
        int freqY = ofMap(i, 0, img.getHeight(), real.size()-1, 0);
        float magnitude;
        if(linear){
            magnitude = calcMagnitude(freqY);
        }else{
            magnitude = calcMagnitude(curvedIndices[freqY]);
        }
//        float magnitude = linearInterp(calcMagnitude((int)curvedIndices[freqY]), calcMagnitude(int(curvedIndices[freqY]+1)), curvedIndices[freqY]);
        ofColor c;
        c.setHsb(ofMap(i, 0, img.getHeight(), 133, 240), 200,(magnitude*inversefftSize)*1000);
        img.setColor(imgIndex, i, c);
    }
    //cout << calcMagnitude(5) << endl;
    imgIndex++;if(imgIndex>=img.getWidth()){imgIndex=0;}
    img.update();
    
}

void Spectroscope::draw(){
    
    //ofSetColor(150);
    //ofDrawRectangle(x, y, width, height);

    ofSetColor(255);
    img.draw(x, y, width, height);
    ofSetColor(255, 180); ofSetLineWidth(3);
   // line.draw();
//    for(int i = 0; i < numSegments; i++){
//        ofDrawCircle(curvedX[i], height+y, 5);
//    }
}

void Spectroscope::input(float inputSample){
    inBuffer[writeIndex] = inputSample;
    writeIndex++; if(writeIndex>=inBuffer.size()){writeIndex = 0;}
}

float Spectroscope::calcMagnitude(int bin){
    return sqrt((real[bin]*real[bin])+(imaginary[bin]*imaginary[bin]));
}
