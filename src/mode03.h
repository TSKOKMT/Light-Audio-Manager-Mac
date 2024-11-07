#pragma once

#include "ofMain.h"

#include "ofxFft.h"

class mode03 {

public:
    mode03();
    
    vector<ofPtr<ofFloatColor>> get(float time_, int count_, float volume_);
        
private:
    vector<ofFloatColor> palette;
};
