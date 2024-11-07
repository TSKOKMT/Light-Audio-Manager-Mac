#include "mode05.h"

//--------------------------------------------------------------
mode05::mode05() {
    
}

//--------------------------------------------------------------
vector<ofPtr<ofFloatColor>> mode05::get(float time_, int count_) {
    
    //SETUP
    
    vector<ofPtr<ofFloatColor>> colors;
    for (int i = 0; i < count_; i++) {
        ofPtr<ofFloatColor> colorPtr = ofPtr<ofFloatColor>(new ofFloatColor);
        colors.push_back(colorPtr);
    }
    
    //UPDATE
    
    int VMap[15] = {0, 1, 2, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5};
    
    int countH = 28;
    int countV = 15;
    for (int i = 0; i < colors.size(); i++) {
        int indexH = i % countH;
        int indexV = i / countH;
        
        indexV = VMap[indexV];
        
        float a = (float)indexH / countH * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)indexV / countV;
        
        float b = ofNoise(a / 4., h, time_ / 4.);
        b = ofNormalize(cos(b * PI), 1, -1);
        b = ofNormalize(cos(b * PI), 1, -1);
        
        //b *= .5;
        //b = b > .5 ? .5 : 0;
        
        ofFloatColor theColor = ofFloatColor(b, b, 0);
        
        colors[i]->set(theColor);
    }

    //DRAW
    
    //RETURN
    
    return colors;
}
