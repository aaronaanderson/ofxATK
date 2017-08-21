#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sinGen = new TSine(0.3);//autopanner for stereo
    phasor = new TPhasor(0.3);//autopanner for all other methods
    
    
    //setting up meters since I do not have multichannel systems available
    for(int i = 0; i < 2; i++){
        stMeters[i] = new Meter(ofVec2f(20 + (i*25), 20), 20, 100, 100);
    }
    for(int i = 0; i < 4; i++){
        quadMeters[i] = new Meter(ofVec2f(20 + (i*25), 130), 20, 100, 100);
    }
    for(int i = 0; i < 6; i++){
        fiveOneMeters[i] = new Meter(ofVec2f(20 + (i*25), 240), 20, 100, 100);
    }
    for(int i = 0; i < 8; i++){
        octMeters[i] = new Meter(ofVec2f(20 + (i*25), 350), 20, 100, 100);
    }
    
    
    //sound stream setup. Be sure to comment out the functions you are not using
    ofSoundStreamSetup(2, 0, 48000, 512, 4);
    //ofSoundStreamSetup(4, 0, 48000, 512, 4);//quad setup
    //ofSoundStreamSetup(6, 0, 48000, 512, 4);//5.1 setup
    //ofSoundStreamSetup(8, 0, 48000, 512, 4);//octophonic setup
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < 2; i++){
        stMeters[i]->update();
    }
    for(int i = 0; i < 4; i++){
        quadMeters[i]->update();
    }
    for(int i = 0; i < 6; i++){
        fiveOneMeters[i]->update();
    }
    for(int i = 0; i < 8; i++){
        octMeters[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < 2; i++){
        stMeters[i]->draw();
    }
    ofSetColor(0);
    ofDrawBitmapString("Stereo", 70, 30);
    for(int i = 0; i < 4; i++){
        quadMeters[i]->draw();
    }
    ofSetColor(0);
    ofDrawBitmapString("Quad", 130, 140);
    for(int i = 0; i < 6; i++){
        fiveOneMeters[i]->draw();
    }
    ofSetColor(0);
    ofDrawBitmapString("5.1 (L:R:C:LFE:LS:RS)", 180, 250);
    for(int i = 0; i < 8; i++){
        octMeters[i]->draw();
    }
    ofSetColor(0);
    ofDrawBitmapString("octophonic", 230, 360);
    
    //visualization for location
    ofDrawCircle(ofMap(sinGen->getSample(), -1, 1, 0, ofGetWidth()), ofGetHeight()-50, 20);
    ofDrawCircle(ofMap(phasor->getSample(), 0, 1, 0, ofGetWidth()), ofGetHeight()-25, 20);
}

//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        //we'll use two sources to place the sound in space. For the stereo panner,
        //we'll use a trivial sine wave oscillator. Unlike the other panners, the stereo
        //panner takes a -1 to 1 range as input. The rest distribute the sound clockwise
        //starting at 0 for the front left speaker.
        
        //stereo panner location
        sinGen->process();
        
        //all other panner location
        phasor->process();
        
        //need some arbitrary input
        float currentSample = ofRandom(-0.7, 0.7);//just using noise as a source;
        
        //pan the mono source to stereo
        stereoFrame = stPan(currentSample, sinGen->getSample());
        //update the meters
        stMeters[0]->feedMeter(stereoFrame.left);
        stMeters[1]->feedMeter(stereoFrame.right);
        
        //pan the mono source
        quadFrame = quadPan(currentSample, phasor->getSample()*4);
        //feed the meters
        quadMeters[0]->feedMeter(quadFrame.fL);
        quadMeters[1]->feedMeter(quadFrame.fR);
        quadMeters[2]->feedMeter(quadFrame.rR);
        quadMeters[3]->feedMeter(quadFrame.rL);
        
        //mono to 5.1 frame
        fiveOneFrame = f1Pan(currentSample, phasor->getSample()*5);
        //float subMix = 0.4;//the 5.1 panner has an optional argument for LFE mix
        //fiveOneFrame = f1Pan(currentSample, phasor->getSample()*5, subMix);
        //feed the meters. Ordering is strange but it is convention.
        fiveOneMeters[0]->feedMeter(fiveOneFrame.fL);
        fiveOneMeters[1]->feedMeter(fiveOneFrame.fR);
        fiveOneMeters[2]->feedMeter(fiveOneFrame.fC);
        fiveOneMeters[3]->feedMeter(fiveOneFrame.lfe);
        fiveOneMeters[4]->feedMeter(fiveOneFrame.rL);
        fiveOneMeters[5]->feedMeter(fiveOneFrame.rR);
        
        //mono to octaphonic frame
        octFrame = octPan(currentSample, phasor->getSample()*8);
        //feed meters
        octMeters[0]->feedMeter(octFrame.one);
        octMeters[1]->feedMeter(octFrame.two);
        octMeters[2]->feedMeter(octFrame.three);
        octMeters[3]->feedMeter(octFrame.four);
        octMeters[4]->feedMeter(octFrame.five);
        octMeters[5]->feedMeter(octFrame.six);
        octMeters[6]->feedMeter(octFrame.seven);
        octMeters[7]->feedMeter(octFrame.eight);
        
        //-----------------stereo output
        buffer[i*nChannels+0] = stereoFrame.left;
        buffer[i*nChannels+1] = stereoFrame.right;
        
        //only attempt to output > stereo if you have the hardware...or just enjoy the errors.
        
        //-----------------quad output
        /*
        buffer[i*nChannels+0] = quadFrame.fL;
        buffer[i*nChannels+1] = quadFrame.fR;
        buffer[i*nChannels+2] = quadFrame.rR;
        buffer[i*nChannels+3] = quadFrame.rL;
          */
        //-----------------5.1 output
        /*
        buffer[i*nChannels+0] = fiveOneFrame.fL;
        buffer[i*nChannels+1] = fiveOneFrame.fR;
        buffer[i*nChannels+2] = fiveOneFrame.fC;
        buffer[i*nChannels+3] = fiveOneFrame.lfe;
        buffer[i*nChannels+4] = fiveOneFrame.rR;
        buffer[i*nChannels+5] = fiveOneFrame.rL;
        */
        //----------------octophonic output
        /*
        buffer[i*nChannels+0] = octFrame.one;
        buffer[i*nChannels+1] = octFrame.two;
        buffer[i*nChannels+2] = octFrame.three;
        buffer[i*nChannels+3] = octFrame.four;
        buffer[i*nChannels+4] = octFrame.five;
        buffer[i*nChannels+5] = octFrame.six;
        buffer[i*nChannels+6] = octFrame.seven;
        buffer[i*nChannels+7] = octFrame.eight;
         */
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}
