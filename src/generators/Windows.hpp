//
//  Windows.hpp
//
//  Created by Aaron Anderson on 7/17/17.
//
// math functions from ofxMaximilian

#ifndef Windows_hpp
#define Windows_hpp

#include <stdio.h>
#include "ofMain.h"


inline double hannWindow(double phase){//0-1
    return 0.5*(1.0-cos((2.0f * PI * phase)/1.0f));
}

//no hamming, because who uses hamming?
//email me if I"m crazy

inline float cosWindow(double phase){
    return sin((PI * phase)/1.0f);
}

inline float rectWindow(double phase){
    return 1;
}

inline float triWindow(double phase){
    return 2.0f * (0.5 - fabs(phase - 0.5));
}

//non-zero endpoints, why use?
inline float blackmanHarrisWin(double phase){
    return 0.35875 -
    (0.48829 * cos((2 * PI * phase) / 1.0f)) +
    (0.14128 * cos((4 * PI * phase) / 1.0f)) +
    (0.01168 * cos((6 * PI * phase) / 1.0f));
}

//again, non-zero. why?
inline float blackmanNutallWin(double phase){
    return 0.3635819 -
    (0.4891775 * cos((2 * PI * phase) / 1.0f)) +
    (0.1365995 * cos((4 * PI * phase) / 1.0f)) +
    (0.0106411 * cos((6 * PI * phase) / 1.0f));
}

inline float gaussWin(double phase){
    double p = 1.0/(2.0*0.02);
    double k = phase - (0.5);
    return exp(-k*k*p);
}
#endif /* Windows_hpp */
