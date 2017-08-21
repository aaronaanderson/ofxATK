
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxATK.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp, public ofxMidiListener {//important change if using ofxMIDI
    
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
    void mouseReleased();
    
    //handle MIDI events
    void newMidiMessage(ofxMidiMessage& eventArgs);
    stringstream text;
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    
    
    WTSine* carrier;
    WTSine* modulator;
    CTEnvelope* ampEnv;
    CTEnvelope* indexEnv;//a common FM synth practice is to control the index via an envelope
    SmoothValue frequency, amplitude;
    int mostRecentNote;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider indexMax;SmoothValue indexSmooth;
    ofxFloatSlider ratio;SmoothValue ratioSmooth;
};
