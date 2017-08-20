#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    delayLine = new TapIn(4000);//setup with maximum delay time
    delayLineAccess = new TapOut(delayLine, 100);//(which delay line, inital delay time)

    
    grainStream = new SimpleGrainStream();
    gui.setup();
    gui.add(delayTime.setup("Delay Time (ms)", 100, 5, 4000));
    gui.add(feedBack.setup("Feedback", 0.4, 0.0, 1.0));
    gui.add(dryWet.setup("Dry/Wet", 0.4, 0.0, 1.0));
    
    delayTimeSV.currentValue = delayTimeSV.targetValue = delayTime;
    delayTimeSV.smoother = new ParameterSmoother(300);
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
    for(int i = 0; i < bufferSize; i ++){
        delayTimeSV.targetValue = delayTime;//set the slider output as the target value
        delayTimeSV.currentValue = delayTimeSV.smoother->process(delayTimeSV.targetValue);//smooth transition
        delayLineAccess->setTime(delayTimeSV.currentValue);
        grainStream->process();
        float currentSample = grainStream->getSample();
        float delay = delayLineAccess->getSample();
        delayLine->feed(currentSample + (delay * feedBack));
        
        currentSample = (currentSample * (1.0-dryWet)) + (delay*dryWet);
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
