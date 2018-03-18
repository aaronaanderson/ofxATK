#pragma once

#include "ofMain.h"
#include "ofxATK.hpp"
#include "ofxGui.h"

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
		
    
    CTEnvelope* envelope;
    
    WTSquare* squareWave;
    SmoothValue frequency;
    
    int currentNote;//this is used to avoid a previous note off canceling the current note
    
    //gui-----
    ofxPanel gui;
    ofxFloatSlider attackSlider;
    ofxFloatSlider decaySlider;
    ofxFloatSlider sustainSlider;
    ofxFloatSlider releaseSlider;
    
    ofxFloatSlider portamento;//may as well 
    
};
