#pragma once

#include "ofMain.h"

#include "ofxFft.h"

class mode05 {

public:
    mode05();
    
    vector<ofPtr<ofFloatColor>> get(float time_, int count_);
        
private:
    vector<ofFloatColor> palette;
};
