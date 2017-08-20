//
//  Spectroscope.hpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/17/17.
//
//

#ifndef Spectroscope_hpp
#define Spectroscope_hpp

#include <stdio.h>
#include "AudioFFT.h"
#include "ofMain.h"
#include "Interpolation.hpp"

class Spectroscope{
    
public:
    ~Spectroscope();
    Spectroscope(){
        fft.init(fftSize);
        inBuffer.resize(fftSize, 0.0f);
        real.resize(fft.ComplexSize(fftSize));
        imaginary.resize(fft.ComplexSize(fftSize));
        outBuffer.resize(fftSize);
        x = 20;y = 20;
        width = 600;
        height = 400;
        writeIndex = 0;
        
        img.allocate(width, height, OF_IMAGE_COLOR);
        
        for(int i = 0; i < img.getPixels().size();i++){
            img.getPixels()[i] = 0;
        }
//        for(int i = 0; i < img.g
//            img.getPixels()[i] = 0;
//        }
        imgIndex = 0;
        numSegments = width/20;
        //calcCurves();
        //cout << imaginary.size() << endl;
        calcCurves();
        linear = true;
    };
    
    void input(float inputSample);
    void update();
    void draw();
    void setMode(bool curve){
        linear = curve;
    }
    bool getMode(){
        return linear;
    }
    void setLocation(float newX, float newY){
        x = newX; y = newY;
    }
    void setSize(float newWidth, float newHeight){
        width = newWidth;
        height = newHeight;
    }
    
private:
    const unsigned int fftSize = 256; // Needs to be power of 2!
    const float inversefftSize = 1/(float)fftSize;
    vector<float> inBuffer;
    vector<float> real;
    vector<float> imaginary;
    vector<float> outBuffer;
    audiofft::AudioFFT fft;//fast fourier transform
    float calcMagnitude(int bin);
    
    unsigned int writeIndex;
    
    ofImage img;
    unsigned int imgIndex;
    
    //--------for drawing
    float x,y,width,height;
    ofPolyline line;
    unsigned int numSegments;
    
    bool linear;
    
    vector<float> curvedIndices; //as floats if interpolation is desired
    void calcCurves(){
        cout << real.size() << endl;
        curvedIndices.resize(real.size());
        //2 to the power of x = curvedIndices.size, solve for x
        double x = log10(curvedIndices.size())/log10(2);
        cout << "linearRange " << x << endl;
        //the range is between x and 0. find linear increment portion
        double dec = x/(curvedIndices.size());
        cout << "decVal " << dec << endl;
        for(int i = curvedIndices.size()-1; i >= 0; i--){
            curvedIndices[i] = pow(2, x) - 1.0;
            x -= dec;
            cout << curvedIndices[i] << endl;
        }
    }
    
    
};


#endif /* Spectroscope_hpp */
