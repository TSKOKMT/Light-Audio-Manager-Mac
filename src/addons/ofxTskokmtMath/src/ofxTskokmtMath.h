#pragma once

#include "ofMain.h"

class ofxTskokmtMath {
    
public:
    static float mean(vector<float> values);
    
    float easeFilter(float value_, float amount_);
    float previousValue;
    bool bFistTime = true;
    
    float meanFilter(float value_,  int numOfSample_);
    vector<float> stackedValues;
    
private:
};
