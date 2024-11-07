#include "mode04.h"

//--------------------------------------------------------------
mode04::mode04() {
    
    load("/Users/tskokmt/PROJECT/Royal Blue/PRESENTATION/02 feel.mp4");
    
    video.setVolume(0);
}

//--------------------------------------------------------------
vector<ofPtr<ofFloatColor>> mode04::get(float time_, int count_, float volume_) {
    
    //SETUP
    
    vector<ofPtr<ofFloatColor>> colors;
    for (int i = 0; i < count_; i++) {
        ofPtr<ofFloatColor> colorPtr = ofPtr<ofFloatColor>(new ofFloatColor);
        colors.push_back(colorPtr);
    }
    
    //UPDATE
    
    video.update();
    
    ofPixels pixels;
    video.getTexture().readToPixels(pixels);
    
    int lineCount = count_ / 10;
    for (int i = 0; i < colors.size(); i++) {
        int angleIdx = i / lineCount;
        int heightIdx = i % lineCount;
        if (angleIdx % 2) heightIdx = lineCount - heightIdx - 1;
        
        float a = (float)angleIdx / 10 * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)heightIdx / lineCount;
        
        ofFloatColor theColor = pixels.getColor(a / TWO_PI * pixels.getWidth(), (1 - h) * pixels.getHeight());
        theColor *= volume_;
        
        colors[i]->set(theColor);
    }
    
    //DRAW
    
    ofSetColor(volume_ * 255);
    ofDrawRectangle(ofGetWindowRect());
    
    //RETURN
    
    return colors;
}

//--------------------------------------------------------------
void mode04::load(string path_) {
    
    video.load(path_);
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
}
