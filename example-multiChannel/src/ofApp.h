#pragma once

#include "ofMain.h"
#include "ofxATK.hpp"

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
		
    //create storage for the frames of audio
    //(a frame is a collection of all simultaneous samples)
    StFrame stereoFrame;
    QuadFrame quadFrame;
    Five1Frame fiveOneFrame;
    OctFrame octFrame;
    
    TPhasor* phasor;//we'll use this on all except stereo
    TSine* sinGen;//we'll use this to pan for stereo
    
    //Let's store the meters in arrays for convenience
    Meter* stMeters[2];
    Meter* quadMeters[4];
    Meter* fiveOneMeters[6];
    Meter* octMeters[8];
};
