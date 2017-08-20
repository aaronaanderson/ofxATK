//
//  Spatialization.hpp
//  libraryBuilding
//
//  Created by Aaron Anderson on 8/4/17.
//
//

#ifndef Spatialization_hpp
#define Spatialization_hpp

#include <stdio.h>
#include "ofMain.h"

static const float sqrt2o2 = 0.707106781186548;

struct StFrame{
    float left;
    float right;
};

//mono to stereo
inline StFrame stPan(float input, float position){
    //expected range is -1 to 1. will not break if boundry exceeded
    StFrame temp;
    float theta = ofDegToRad(position*45); //-45 to 45, in radians
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    temp.left = (sqrt2o2 * (sinTheta - cosTheta)) * input;
    temp.right = (sqrt2o2 * (sinTheta + cosTheta))*input;
    return temp;
}

struct QuadFrame{
    float fL;
    float fR;
    float rR;
    float rL;
};

//mono to quad;
inline QuadFrame quadPan(float input, float position){
    //expected range is 0-4
    QuadFrame temp;
    float pos = fmod(position, 4.0);//make sure it gets wrapped
    float theta = (fmod(position, 1.0)*2.f)-1.f;
    StFrame stereo = stPan(input, theta);//
    int whichChannels = int(position);//truncate to determine which speakers
    switch(whichChannels){
        case 0://between 0 and 1
            temp.fL = stereo.left;
            temp.fR = stereo.right;
            temp.rR = 0.0;
            temp.rL = 0.0;
            break;
        case 1://between 1 and 2
            temp.fL = 0.0;
            temp.fR = stereo.left;
            temp.rR = stereo.right;
            temp.rL = 0.0;
            break;
        case 2://between 2 and 3
            temp.fL = 0.0;
            temp.fR = 0.0;
            temp.rR = stereo.left;
            temp.rL = stereo.right;
            break;
        case 3://between 3 and 0
            temp.fL = stereo.right;
            temp.fR = 0.0;
            temp.rR = 0.0;
            temp.rL = stereo.left;
            break;
        //default:
          //  cout << "somethingwrong with quad panner" << endl;
    }
    return temp;
}

struct Five1Frame{
    //ordered by convention
    float fL;
    float fR;
    float fC;
    float lfe;
    float rR;
    float rL;
};

//mono to 5.1
inline Five1Frame f1Pan(float input, float position, float lfeMix = 0.0){
    //this one is a bit trick. In a standard 5.1 setup, the speakers are not distributed
    //equally in polar space. teh distance between the rear speakers is larger than the distance
    //between the front speakers. However, I will choose to ignore this for convenience of
    //programming and user case. 0 will equal front left; distribute clockwise; 4 = rear left
    //the sub feed is an indepentantly controlled parameter "lfeMix"
    Five1Frame temp;
    // position should be between 0 and 5.0;
    float theta = (fmod(position, 1.0)*2.0)-1.0;
    StFrame stereo = stPan(input, theta);
    float pos = fmod(position, 5.0);//make sure it gets wrapped
    int whichChannels = int(pos);//truncate to determine which two speakers
    switch(whichChannels){
        case 0://between 0 and 1
            temp.fL = stereo.left;
            temp.fC = stereo.right;
            temp.fR = 0.0;
            temp.rL = 0.0;
            temp.rR = 0.0;
            temp.lfe = lfeMix * input;
            break;
        case 1://between 1 and 2
            temp.fL = 0.0;
            temp.fC = stereo.left;
            temp.fR = stereo.right;
            temp.rL = 0.0;
            temp.rR = 0.0;
            temp.lfe = lfeMix * input;
            break;
        case 2://between 2 and 3
            temp.fL = 0.0;
            temp.fC = 0.0;
            temp.fR = stereo.left;
            temp.rL = stereo.right;
            temp.rR = 0.0;
            temp.lfe = lfeMix * input;
            break;
        case 3://between 3 and 4
            temp.fL = 0.0;
            temp.fC = 0.0;
            temp.fR = 0.0;
            temp.rL = stereo.left;
            temp.rR = stereo.right;
            temp.lfe = lfeMix * input;
            break;
        case 4://between 4 and 0
            temp.fL = stereo.right;
            temp.fC = 0.0;
            temp.fR = 0.0;
            temp.rL = 0.0;
            temp.rR = stereo.left;
            temp.lfe = lfeMix * input;
            break;
        //default:
            
    }
    
    return temp;
}

struct OctFrame{
    //honestly at this point it makes mroe sense to do this with an array,
    //but I chose a struct here to be consistent
    float one;
    float two;
    float three;
    float four;
    float five;
    float six;
    float seven;
    float eight;
};

//mono to octaphonic
inline OctFrame octPan(float input, float position){
    OctFrame temp;
    //input should be from 0, to 8.0 (0 being front left, then clockwise distribution)
    float pos = fmod(position, 8.0);//make sure it gets wrapped
    int whichChannels = int(pos);//truncate to determine which two speakers
    float theta = (fmod(position, 1.0)*2.0)-1.0;
    StFrame stereo = stPan(input, theta);
    switch(whichChannels){
        case 0:
            temp.one = stereo.left;
            temp.two = stereo.right;
            temp.three=temp.four=temp.five=temp.six=temp.seven=temp.eight = 0.0;
            break;
        case 1:
            temp.two = stereo.left;
            temp.three = stereo.right;
            temp.four=temp.five=temp.six=temp.seven=temp.eight=temp.one= 0.0;
            break;
        case 2:
            temp.three = stereo.left;
            temp.four = stereo.right;
            temp.five=temp.six=temp.seven=temp.eight=temp.one=temp.two= 0.0;
            break;
        case 3:
            temp.four = stereo.left;
            temp.five = stereo.right;
            temp.six=temp.seven=temp.eight=temp.one=temp.two=temp.three= 0.0;
            break;
        case 4:
            temp.five = stereo.left;
            temp.six = stereo.right;
            temp.seven=temp.eight=temp.one=temp.two=temp.three=temp.four= 0.0;
            break;
        case 5:
            temp.six = stereo.left;
            temp.seven = stereo.right;
            temp.eight=temp.one=temp.two=temp.three=temp.four=temp.five= 0.0;
            break;
        case 6:
            temp.seven = stereo.left;
            temp.eight = stereo.right;
            temp.one=temp.two=temp.three=temp.four=temp.five=temp.six= 0.0;
            break;
        case 7:
            temp.eight = stereo.left;
            temp.one = stereo.right;
            temp.two=temp.three=temp.four=temp.five=temp.six=temp.seven= 0.0;
            break;
        
    }
    return temp;
}

#endif /* Spatialization_hpp */
