#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sine = new TSine(1);
    saw = new TSawtooth(1);
    square = new TSquare(1);
    tri = new TTriangle(1);
    
    carrier = new WTTriangle(480);
    modulator = new WTSine(70);
    
    whichLFO = SINE;//start with the sine as the LFO controller
    
    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    string instructions = "Simple Ring modulator";
    instructions += "\n press 1 for sine";
    instructions += "\n press 2 for sawtooth";
    instructions += "\n press 3 for triangle";
    instructions += "\n press 4 for square";
    instructions += "\n LFO frequency: " + ofToString(sine->getFreq());
    instructions += "\n LFO amplitude: " + ofToString(sine->getAmp());
    
    ofDrawBitmapString(instructions, 20, 20);

}
//--------------------------------------------------------------

void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        switch(whichLFO){
            case SINE:
                sine->process();
                modulator->setFreq(sine->getSample()*40 + 200);
                break;
            case SAW:
                saw->process();
                modulator->setFreq(saw->getSample()*40 + 200);
                break;
            case TRI:
                tri->process();
                modulator->setFreq(tri->getSample()*40 + 200);
                break;
            case SQUARE:
                square->process();
                modulator->setFreq(square->getSample()*40 + 200);
                break;
            default://should never happen, just error checking
                cout << "invalid LFO type" << endl;
        }
        
        carrier->process();//calculate the next sample for carrier
        modulator->process();//calculate the next sample for modulator
        
        //simple ring modulation; carrier signal * modulator signal
        float currentSample = carrier->getSample()*modulator->getSample();
        
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
            case '1':
            whichLFO = SINE;
            break;
            case '2':
            whichLFO = SAW;
            break;
            case '3':
            whichLFO = TRI;
            break;
            case '4':
            whichLFO = SQUARE;
            break;
            
        default:
            cout << "no command set for that key input" << endl;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    float freq = ofMap(x, 0, ofGetWidth(), 0, 20);
    sine->setFreq(freq);
    saw->setFreq(freq);
    tri->setFreq(freq);
    square->setFreq(freq);
    
    float amp = ofMap(y, ofGetHeight(), 0, 0, 1.0);
    sine->setAmp(amp);
    saw->setAmp(amp);
    tri->setAmp(amp);
    square->setAmp(amp);
    
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

void ofApp::exit(){
    ofSoundStreamClose();
}
