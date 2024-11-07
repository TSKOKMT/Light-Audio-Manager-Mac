#pragma once

#include "ofMain.h"

class mode02 {

public:
    mode02();
    
    vector<ofPtr<ofFloatColor>> get(float time_, int count_, float volume_);
        
private:
    float timeR;
    float previousTimeR;
    
    float newTime;
    
    vector<ofFloatColor> palette;
};
