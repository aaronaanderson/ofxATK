#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    soundFile = new SoundFile(ofToDataPath("almondBreak.wav"));
    player = new SoundPlayer(soundFile, 0, true);
    
    playbackSpeed = 1.0;
    player->setSpeed(playbackSpeed);
    
    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    soundFile->draw(20, 20, 400, 180);
    player->draw();//draw the currentPosition
    
    ofSetColor(0);
    string hud = "Press spacebar to start at the beginning \n";
    hud += "(up/down)current speed = " + ofToString(playbackSpeed) + "\n";
    
    if(player->getLoopEnabled()){
        hud += "(l)looping enabled  \n";
        hud += "(t) loop type: ";
        switch(player->getLoopMode()){
            case 0:
                hud += "standard";
                break;
            case 1:
                hud += "palindrome";
                break;
        }
    }else{
        hud += "(l)looping disabled\n";
    }
    
    
    
    ofDrawBitmapString(hud, 20, 200);
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        
        player->process();
        float currentSample = player->getSample();
        
        
        
        buffer[i*nChannels+0] = currentSample;
        buffer[i*nChannels+1] = currentSample;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case OF_KEY_DOWN:
            playbackSpeed -= 0.1;
            player->setSpeed(playbackSpeed);
            break;
        case OF_KEY_UP:
            playbackSpeed += 0.1;
            player->setSpeed(playbackSpeed);
            break;
        case ' ':
            player->setLocation(0);
            player->play();
            break;
        case 'l':
            player->loop(!player->getLoopEnabled());
            break;
        case 't':
            if(player->getLoopMode() == 0){
                player->setLoopMode(1);
            }else{
                player->setLoopMode(0);
            }
            
            break;
    }
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
void ofApp::exit(){
    ofSoundStreamClose();
}
