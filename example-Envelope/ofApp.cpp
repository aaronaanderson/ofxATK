#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    envelope = new CTEnvelope(300, 4000, 0.7, 1000);
    
    frequency.currentValue = frequency.targetValue = 100;
    frequency.smoother = new ParameterSmoother(40);
    squareWave = new WTSquare(frequency.currentValue);
    
    //----setup GUI
    gui.setup();
    gui.add(attackSlider.setup("Attack", 120, 20, 3000));
    gui.add(decaySlider.setup("Decay", 40, 15, 1500));
    gui.add(sustainSlider.setup("Sustain", 0.6, 0.0, 1.0));
    gui.add(releaseSlider.setup("Release", 300, 50, 5000));
    gui.add(portamento.setup("Portamento", 200, 10, 1000));
    
    ofSoundStreamSetup(2, 0, 48000, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    ofSetColor(0);
    string instructions = "Press keys 'a' horizontally through 'k' to play a C Major scale";
    ofDrawBitmapString(instructions, 220, 20);
    
    //simple visualization of envelope
    ofColor c;
    int state; string stateString;
    state = (envelope->getState());
    
    switch(state){
        case 0://off
            c.setHsb(10, 200, 200);
            stateString = "off";
            break;
        case 1://attack
            c.setHsb(50, 200, 200);
            stateString = "attack";
            break;
        case 2://decay
            c.setHsb(90, 200, 200);
            stateString = "decay";
            break;
        case 3://sustain
            c.setHsb(130, 200, 200);
            stateString = "sustain";
            break;
        case 4://release
            c.setHsb(170, 200, 200);
            stateString = "release";
            break;
    }
    ofVec2f location;
    location.x = 20;
    location.y = ofMap(envelope->getValue(), 0, 1, ofGetHeight()-20, 160);
    ofSetColor(0);
    ofDrawBitmapString(stateString, location.x+20, location.y);
    ofSetColor(c);
    ofDrawCircle( location.x, location.y, 20);
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        envelope->setAttack(attackSlider);
        envelope->setDecay(decaySlider);
        envelope->setSustain(sustainSlider);
        envelope->setRelease(releaseSlider);
        envelope->process();
        
        squareWave->process();
        frequency.smoother->setTime(portamento);
        frequency.currentValue = frequency.smoother->process(frequency.targetValue);
        squareWave->setFreq(frequency.currentValue);
        float currentSample = squareWave->getSample() * envelope->getValue();

        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        envelope->setGate(1);
    }
    
    switch(key){
        case 'a':
            envelope->setGate(1);
            frequency.targetValue = mtof(36);
            currentNote = 'a';
            break;
        case 's':
            envelope->setGate(1);
            frequency.targetValue = mtof(38);
            currentNote = 's';
            break;
        case 'd':
            envelope->setGate(1);
            frequency.targetValue = mtof(40);
            currentNote = 'd';
            break;
        case 'f':
            envelope->setGate(1);
            frequency.targetValue = mtof(41);
            currentNote = 'f';
            break;
        case 'g':
            envelope->setGate(1);
            frequency.targetValue = mtof(43);
            currentNote = 'g';
            break;
        case 'h':
            envelope->setGate(1);
            frequency.targetValue = mtof(45);
            currentNote = 'h';
            break;
        case 'j':
            envelope->setGate(1);
            frequency.targetValue = mtof(47);
            currentNote = 'j';
            break;
        case 'k':
            envelope->setGate(1);
            frequency.targetValue = mtof(48);
            currentNote = 'k';
            break;
        default:
            cout << "key not set" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
        envelope->setGate(0);
    }
    
    switch(key){
        case 'a':
            if(currentNote == 'a')//avoid canceling note if key up was from previous note
                envelope->setGate(0);
            break;
        case 's':
            if(currentNote == 's')
                envelope->setGate(0);
            break;
        case 'd':
            if(currentNote == 'd')
                envelope->setGate(0);
            break;
        case 'f':
            if(currentNote == 'f')
                envelope->setGate(0);
            break;
        case 'g':
            if(currentNote == 'g')
                envelope->setGate(0);
            break;
        case 'h':
            if(currentNote == 'h')
                envelope->setGate(0);
            break;
        case 'j':
            if(currentNote == 'j')
                envelope->setGate(0);
            break;
        case 'k':
            if(currentNote == 'k')
                envelope->setGate(0);
            break;
        default:
            cout << "key not set" << endl;
    }
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
