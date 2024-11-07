#pragma once

#include "ofMain.h"

#include "ofxFft.h"
#include "ofxTskokmtMath.h"

class volumeUnit {

public:
    void setup();
    float get();
    void audioReceived(float* input, int bufferSize, int nChannels);
    
    float volumeTime;
        
private:
    ofxFft* fft;
    vector<float> buffers, bins;
    
    float volume;
    float previousVolume;
    
    
    
    float time;
    float previousTime;
    
    float trueVolume;
    float previousTrueVolume;
    
    ofxTskokmtMath math;
};
