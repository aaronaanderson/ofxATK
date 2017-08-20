//
//  SoundFile.cpp
//  libraryBuilding
//
//  Created by Institute of Digital Intermedia Arts on 7/15/17.
//
//

#include "SoundFile.hpp"

void SoundFile::resize(unsigned int sizeInSamps){
    buffer.resize(sizeInSamps);
}

//--------------------------------------------------------------
void SoundFile::clear(){
    for(int i = 0; i < realSize; i++){
        buffer[i] = 0.0f;//set all members to 0.0
    }
}
//--------------------------------------------------------------
void SoundFile::erase(){
    buffer.clear();//actually erase all members
}
//--------------------------------------------------------------
void SoundFile::draw(){
    ofDrawRectangle(x, y, width, height);
    //TODO
}
//--------------------------------------------------------------
void SoundFile::draw(int newX, int newY, int newWidth, int newHeight){
    setDrawPosition(x, y);
    setDrawSize(newWidth, newHeight);
    ofSetColor(0);
    ofDrawRectangle(x, y, width, height);
    ofSetColor(ofColor(15, 24, 130));
    ofDrawRectangle(x+1, y+1, width-2, height-2);

    
//    float skip = size/float(width);
//    for(int i = 0; i < width; i++){
//        ofDrawLine(i+x, (height*0.5)+y,i+x, ((height*0.5)+y) + (buffer[int(i*skip)]*(height*0.5)));
//    }
    
    ofPushStyle();
    float cellWidth = width*0.62/drawResolution;
    ofNoFill();//just empty rectangels
    ofSetColor(220);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetLineWidth(1.0);
    for(int i = 0; i < drawResolution; i++){
        float tempX = ofMap(i, 0, drawResolution-1, (cellWidth*0.5+1.0), width - (cellWidth*0.5+1.0));
        
        ofDrawRectangle(tempX + x, y+(height*0.5), cellWidth, cellSizes[i]*height);
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void SoundFile::load(){//load sound file with load dialog
    ofFileDialogResult loadFileResult = ofSystemLoadDialog();//open the load dialog
    string path = loadFileResult.getPath();//store the string
    const char *filePath = path.c_str();// convert from fancy string to C string
    
    ifd = psf_sndOpen(filePath, &soundFileProperties, 0);//open the sound file
    
    if (ifd < 0) {//this can happen if the file does not exist or the format is not supported
        ofSystemAlertDialog("Error loading file");
    }
    else {
        frame = (float*)malloc(soundFileProperties.chans * sizeof(float));//set the size of frame to be the nSamples per Frame
        framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//grab the first frame
        totalFramesRead = 0;
        buffer.clear();//clear the vector that the soundFile will be stored in
        buffer.push_back(0.0);//add a zero sample
        while (framesRead == 1) {//while there are still frames to be read
            totalFramesRead++;//keep track of number of frames;
            for (int i = 0; i < soundFileProperties.chans; i++) {//for every sample in the frame
                if(i == 0){
                   buffer.push_back(frame[i]);//add frame to the soundFile vector
                }
            }
            framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//returns 1 if there are still more frames
            //cout << framesRead << " " << endl;
        }
        //adjust for cubic interpolation, allowing to keep the check out of the process loop
        size = totalFramesRead;
        buffer[0] = buffer[size-1];//the first sample = the last sample
        buffer[size] = buffer[1];
        buffer[size+1] = buffer[2];
        realSize = size+3;
        soundFileSampleRate = soundFileProperties.srate;
    }
}
//--------------------------------------------------------------
void SoundFile::load(string dataPath){//load sound file from written path
    const char *filePath = dataPath.c_str();// convert from fancy string to C string
    ifd = psf_sndOpen(filePath, &soundFileProperties, 0);//open the sound file
    
    if (ifd < 0) {//this can happen if the file does not exist or the format is not supported
        ofSystemAlertDialog("Error loading file");
    }
    else {
        frame = (float*)malloc(soundFileProperties.chans * sizeof(float));//set the size of frame to be the nSamples per Frame
        framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//grab the first frame
        totalFramesRead = 0;
        buffer.clear();//clear the vector that the soundFile will be stored in
        buffer.push_back(0.0);//add a buffer
        while (framesRead == 1) {//while there are still frames to be read
            totalFramesRead++;//keep track of number of frames;
            for (int i = 0; i < soundFileProperties.chans; i++) {//for every sample in the frame
                if(i == 0){//just keep left channel for now TODO
                    buffer.push_back(frame[i]);//add frame to the soundFile vector
                }
            }
            framesRead = psf_sndReadFloatFrames(ifd, frame, 1);//returns 1 if there are still more frames
            //cout << framesRead << " " << endl;
        }
        size = totalFramesRead;
       
        buffer[0] = buffer[size-1];//the first sample = the last sample
        buffer.push_back(buffer[1]);//the second to last sample = first actual samp
        buffer.push_back(buffer[2]);//the last samp = the second actual sample
        realSize = size+3;
        soundFileSampleRate = soundFileProperties.srate;
        
        //store the data that is needed to draw
        int samplesPerCell = size/(float)drawResolution;
        cout << cellSizes.size() << endl;
        cout << drawResolution << endl;
        for(int i = 0; i < drawResolution; i++){//for every drawCell
            float average = 0;
            for(int j = 0; j < samplesPerCell; j++){//for every sample in cell
                average += fabs(buffer[(i*samplesPerCell)+j]);
            }
            average = average/float(samplesPerCell);
            cout << i << " " <<average << endl;
            cellSizes[i] = average;
        }
    }
}
//--------------------------------------------------------------
void SoundFile::normalize(){
    //first, bump any DC offset
    float average = 0;
    for(int i = 1; i < size+1; i++){//ignore padding
        average += buffer[i];
    }
    float offset = average/size;
    //now use that average to adjust every sample;
    for(int i = 0; i < realSize; i++){
        buffer[i] += offset;
    }
    //DC offset taken care of
    //find highest point, ignoring polarity
    float highestPoint = 0;
    for(int i = 1; i < size; i++){
        if(fabs(buffer[i]) > highestPoint){
            highestPoint = fabs(buffer[i]);
        }
    }
    float scalar = 1.0f/highestPoint;
    //now that we have the scalar, apply to whole buffer equally
    for(int i = 0; i < realSize; i++){
        buffer[i] *= scalar;
    }
}
//--------------------------------------------------------------
void SoundFile::normalize(float level){
    //first, bump any DC offset
    float average = 0;
    for(int i = 1; i < size+1; i++){//ignore padding
        average += buffer[i];
    }
    float offset = average/size;
    //now use that average to adjust every sample;
    for(int i = 0; i < realSize; i++){
        buffer[i] += offset;
    }
    //DC offset taken care of
    //find highest point, ignoring polarity
    float highestPoint = 0;
    for(int i = 1; i < size; i++){
        if(fabs(buffer[i]) > highestPoint){
            highestPoint = fabs(buffer[i]);
        }
    }
    float scalar = level/highestPoint;//this is the only difference
    //now that we have the scalar, apply to whole buffer equally
    for(int i = 0; i < realSize; i++){
        buffer[i] *= scalar;
    }
}
