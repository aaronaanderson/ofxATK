#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    grainStream = new SimpleGrainStream();
    reverb = new Reverb();
    
    
    gui.setup();
    gui.add(preDelay.setup("Pre-delay", 20, 0, 200));
    gui.add(absorptionFreq.setup("Absorption Freq", 7000, 50, 10000));
    gui.add(absorption.setup("Absorption", 0.15, 0.0, 1.0));
    gui.add(dryWet.setup("Dry/Wet", 0.5, 0.0, 1.0));
    
    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        grainStream->process();
        float currentSample = grainStream->getSample();
        
        reverb->setAbsorption(absorption);
        reverb->setCutOff(absorptionFreq);
        reverb->setDryWet(dryWet);
        reverb->setPreDelay(preDelay);
        
        reverb->process(currentSample);
        currentSample = reverb->getSample();
        //currentSample = ofRandom(-1.0, 1.0);
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
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
