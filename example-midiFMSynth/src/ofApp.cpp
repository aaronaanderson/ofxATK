
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    // print input ports to console
    midiIn.listPorts(); // via instance
    
    // open port by number (you may need to change this)
    midiIn.openPort(2);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    
    frequency.currentValue = frequency.targetValue = 440;
    frequency.smoother = new ParameterSmoother(250);
    carrier = new WTSine(frequency.currentValue);
    amplitude.currentValue = amplitude.targetValue = 1.0;
    amplitude.smoother = new ParameterSmoother(20);
    
    modulator = new WTSine(200);
    
    ampEnv = new CTEnvelope(100, 90, 0.5, 400);
    indexEnv = new CTEnvelope(100, 300, 0.5, 500);
    
    //gui
    gui.setup();
    gui.setPosition(20, 250);
    gui.add(indexMax.setup("index max", 4.0, 0.0, 7.0));
    gui.add(ratio.setup("harmonic ratio", 2.0, 0.0, 5.0));
    
    
    //need to smooth values coming from MIDI or GUI.
    indexSmooth.currentValue = indexSmooth.targetValue = 0;
    indexSmooth.smoother = new ParameterSmoother(50);
    ratioSmooth.currentValue = ratioSmooth.targetValue = 1;
    ratioSmooth.smoother = new ParameterSmoother(50);
    
    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);
    
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(0);
    
    // draw the last recieved message contents to the screen
    text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
    ofDrawBitmapString(text.str(), 20, 20);
    text.str(""); // clear
    
    text << "channel: " << midiMessage.channel;
    ofDrawBitmapString(text.str(), 20, 34);
    text.str(""); // clear
    
    text << "pitch: " << midiMessage.pitch;
    ofDrawBitmapString(text.str(), 20, 48);
    text.str(""); // clear
    ofDrawRectangle(20, 58, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "velocity: " << midiMessage.velocity;
    ofDrawBitmapString(text.str(), 20, 96);
    text.str(""); // clear
    ofDrawRectangle(20, 105, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "control: " << midiMessage.control;
    ofDrawBitmapString(text.str(), 20, 144);
    text.str(""); // clear
    ofDrawRectangle(20, 154, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "value: " << midiMessage.value;
    ofDrawBitmapString(text.str(), 20, 192);
    text.str(""); // clear
    if(midiMessage.status == MIDI_PITCH_BEND) {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
    }
    else {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
    }
    gui.draw();
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){

        ampEnv->process();
        indexEnv->process();
        amplitude.currentValue = amplitude.smoother->process(amplitude.targetValue);
        indexSmooth.targetValue = indexMax;//target value is slider or MIDI input
        indexSmooth.currentValue = indexSmooth.smoother->process(indexSmooth.targetValue);
        ratioSmooth.targetValue = ratio;//target value is slider or MIDI input
        ratioSmooth.currentValue = ratioSmooth.smoother->process(ratioSmooth.targetValue);
        
        //set from MIDI note on
        frequency.currentValue = frequency.smoother->process(frequency.targetValue);
        
        modulator->setFreq(frequency.currentValue * ratioSmooth.currentValue);
        //the harder a note is pressed, the higher the index will rise
        float currentIndex = indexEnv->getValue() * indexSmooth.currentValue * amplitude.currentValue;
        modulator->process();
        float depth = currentIndex * frequency.currentValue * ratioSmooth.currentValue;
        float sweep = depth * modulator->getSample();
        carrier->setFreq(frequency.currentValue + sweep);
        carrier->process();
        
        float currentSample = carrier->getSample();
        
        currentSample *= ampEnv->getValue() * amplitude.currentValue * 0.1;
        
        
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
}
//--------------------------------------------------------------
void ofApp::exit() {
    
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
    midiMessage = msg;
    if(msg.velocity>0){
        frequency.targetValue = mtof(msg.pitch);
        amplitude.targetValue = (msg.velocity/127.f);
        ampEnv->setGate(1);
        indexEnv->setGate(1);
        mostRecentNote = msg.pitch;
    }else{
        if(msg.pitch == mostRecentNote){
             ampEnv->setGate(0);
            indexEnv->setGate(0);
        }
    }
    
    if(msg.control == 74){
        indexMax = msg.value*7/127.f;
    }
    if(msg.control == 71){
        ratio = msg.value*5/127.f;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    switch(key) {
        case 'l':
            midiIn.listPorts();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
