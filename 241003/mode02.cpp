#include "mode02.h"

//--------------------------------------------------------------
mode02::mode02() {
    
    //Setup palette
    
    /*ofImage image;
    image.load("palette.png");
    palette.resize(image.getWidth());
    for (int i = 0; i < palette.size(); i++) {
        palette[i] = image.getColor(i, 0);
    }*/
    
    /*palette.push_back(ofColor::seaGreen);
    palette.push_back(ofColor::yellow);
    palette.push_back(ofColor::seaGreen);
    palette.push_back(ofColor::yellowGreen);
    palette.push_back(ofColor::green);
    palette.push_back(ofColor::forestGreen);*/
    
    /*palette.push_back(ofColor::hotPink);
    palette.push_back(ofColor::orangeRed);
    palette.push_back(ofColor::blueViolet);
    palette.push_back(ofColor::deepPink);
    palette.push_back(ofColor::royalBlue);
    palette.push_back(ofColor::blue);*/
    
    /*palette.push_back(ofColor::red);
    palette.push_back(ofColor::yellow);
    palette.push_back(ofColor::green);
    palette.push_back(ofColor::orange);
    palette.push_back(ofColor::orangeRed);
    palette.push_back(ofColor::greenYellow);*/
    
    /*palette.push_back(ofColor::skyBlue);
    palette.push_back(ofColor::blue);
    palette.push_back(ofColor::green);
    palette.push_back(ofColor::lightCyan);
    palette.push_back(ofColor::cyan);
    palette.push_back(ofColor::seaGreen);*/
    
    palette.push_back(ofColor::white);
    palette.push_back(ofColor::white);
    palette.push_back(ofColor::white);
    palette.push_back(ofColor::white);
    palette.push_back(ofColor::white);
    palette.push_back(ofColor::white);
}

//--------------------------------------------------------------
vector<ofPtr<ofFloatColor>> mode02::get(float time_, int count_, float volume_) {
    
    //SETUP
    
    vector<ofPtr<ofFloatColor>> colors;
    for (int i = 0; i < count_; i++) {
        ofPtr<ofFloatColor> colorPtr = ofPtr<ofFloatColor>(new ofFloatColor);
        colors.push_back(colorPtr);
    }
    
    
    //UPDATE
    
    //time_ *= 3;
    
    previousTimeR = timeR;
    timeR = time_;
    
    newTime += (timeR - previousTimeR) * volume_ * 7.5;
    time_ = newTime;
    
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
        
        for (int i = 0; i < palette.size(); i++) {
            int seed = i * 100 * PI;
            
            float angle = ofNoise(time_ / 60., seed) * 6. * TWO_PI;
            angle = ofWrap(angle, a - PI, a + PI);
            
            float height = ofNoise(time_ / 5., seed);
            height = ofNormalize(cos(height * PI), 1, -1);
            
            float strength = ofNormalize(abs(angle - a), HALF_PI, 0);
            strength *= ofNormalize(abs(height - h), .75, 0);
            strength = pow(strength, 1);
            
            theColor += palette[i] * strength;
            
            theColor *= volume_;
        }
        
        theColor.setHsb(ofNoise(i / 100., time_) / 5. + .6, 1 - pow(theColor.getBrightness(), .5), theColor.getBrightness());
        
        colors[i]->set(theColor);
    }
    
    //DRAW
    
    ofPushStyle();
    for (int i = 0; i < palette.size(); i++) {
        ofSetColor(palette[i]);
        ofDrawRectangle(i * 100, ofGetHeight() - 100, 100, 100);
    }
    ofPopStyle();

    //RETURN
    
    return colors;
}
