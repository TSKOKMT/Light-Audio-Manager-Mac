#include "ofxTskokmtMath.h"

//--------------------------------------------------------------
float ofxTskokmtMath::mean(vector<float> values) {
    
    float sum = 0.;
    for (int i = 0; i < values.size(); i++) sum += values[i];
    return sum / (float)values.size();
}

//--------------------------------------------------------------
float ofxTskokmtMath::easeFilter(float value_, float amount_) {
    
    if (bFistTime) {
        previousValue = value_;
        bFistTime = false;
    }
    value_ = previousValue + (value_ - previousValue) * amount_;
    previousValue = value_;
    
    return value_;
}

//--------------------------------------------------------------
float ofxTskokmtMath::meanFilter(float value_, int numOfSample_) {
 
    if (stackedValues.size() != numOfSample_) stackedValues = vector<float>(numOfSample_, value_);
    
    float mean = 0;
    for (int i = 0; i < numOfSample_; i++) {
        mean += stackedValues[i];
    }
    mean += value_;
    mean /= float(numOfSample_ + 1);
    
    for (int i = numOfSample_ - 1; i >= 1; i--) {
        stackedValues[i] = stackedValues[i - 1];
    }
    stackedValues[0] = value_;
    
    return mean;
}
