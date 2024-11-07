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
    
    int countH = 28;
    int countV = 15;
    int VMap[15] = {0, 1, 2, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5};
    for (int i = 0; i < colors.size(); i++) {
        int indexH = i % countH;
        int indexV = i / countH;
        indexV = VMap[indexV];
        
        float a = (float)indexH / countH * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)indexV / countV;
        
        ofFloatColor theColor = ofFloatColor(volume_);
        
        colors[i]->set(theColor);
    }
    
    //DRAW
    
    //RETURN
    
    return colors;
}
