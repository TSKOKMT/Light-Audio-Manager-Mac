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
    
    int countH = 28;
    int countV = 15;
    
    ofFbo fbo;
    fbo.allocate(countH, countV, GL_RGB, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(0, countV);
    ofScale(1, -1);
    video.draw(0, 0, fbo.getWidth(), fbo.getHeight());
    ofPopMatrix();
    fbo.end();
    
    ofPixels pixels;
    fbo.getTexture().readToPixels(pixels);
    
    int VMap[15] = {0, 1, 2, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5};
    for (int i = 0; i < colors.size(); i++) {
        int indexH = i % countH;
        int indexV = i / countH;
        indexV = VMap[indexV];
        
        float a = (float)indexH / countH * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)indexV / countV;
        
        ofFloatColor theColor = pixels.getColor(indexH, indexV);
        //theColor *= volume_;
        
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
