#pragma once

#include "ofMain.h"
#include "ofxATK.hpp"
#include "ofxGui.h"

class SimpleGrainStream{
    
public:
    SimpleGrainStream(){
        currentSample = 0;
        //80ms Grain
        windowSize = 80 * 0.001 * ATKSettings::sampleRate;
        windowPos = 0;
        sineGen = new WTSquare(440);
        impulse = new ImpulseGenerator(8.0);
    }
    void process(){
        impulse->process();
        sineGen->process();
        
        if(impulse->getSample() == 1){//reset on impulse
            windowPos = 0;//reset window
            float octave = ofRandom (5, 12);
            frequency = pow(2, octave);//random freq distributed with perceptual linearity
            sineGen->setFreq(frequency);
        }
        windowPos++;
        if(windowPos >= windowSize){windowPos = windowSize;}
        
        amplitude = hannWindow(windowPos/float(windowSize));
        
        currentSample = sineGen->getSample() * amplitude;
    }
    
    float getSample(){
        return currentSample;
    }
private:
    float frequency;
    float currentSample;
    float amplitude;
    ImpulseGenerator* impulse;
    unsigned int windowSize, windowPos;
    WTSquare* sineGen;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();
    void audioOut(float* buffer, int bufferSize, int nChannels);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    Reverb* reverb;
    SimpleGrainStream* grainStream;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider absorptionFreq;
    ofxFloatSlider absorption;
    ofxFloatSlider dryWet;
    ofxFloatSlider preDelay;
    
};
