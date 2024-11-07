#include "mode03.h"

//--------------------------------------------------------------
mode03::mode03() {
    
}

//--------------------------------------------------------------
vector<ofPtr<ofFloatColor>> mode03::get(float time_, int count_, float volume_) {
    
    //SETUP
    
    vector<ofPtr<ofFloatColor>> colors;
    for (int i = 0; i < count_; i++) {
        ofPtr<ofFloatColor> colorPtr = ofPtr<ofFloatColor>(new ofFloatColor);
        colors.push_back(colorPtr);
    }
    
    //UPDATE
    
    int lineCount = count_ / 10;
    for (int i = 0; i < colors.size(); i++) {
        int angleIdx = i / lineCount;
        int heightIdx = i % lineCount;
        if (angleIdx % 2) heightIdx = lineCount - heightIdx - 1;
        
        float a = (float)angleIdx / 10 * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)heightIdx / lineCount;
        
        ofFloatColor theColor = ofColor::black;
        
        //theColor.setHsb(ofNoise(time_), ofNoise(time_, 10), volume_);
        theColor.setHsb(0, 0, volume_);
        
        colors[i]->set(theColor);
    }
    
    //DRAW
    
    ofSetColor(volume_ * 255);
    ofDrawRectangle(ofGetWindowRect());
    
    //RETURN
    
    return colors;
}
