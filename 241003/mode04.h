#pragma once

#include "ofMain.h"

#include "ofxFft.h"

class mode04 {

public:
    mode04();
    
    vector<ofPtr<ofFloatColor>> get(float time_, int count_, float volume_);
    
    void load(string path_);
        
private:
    vector<ofFloatColor> palette;
    
    ofVideoPlayer video;
};
