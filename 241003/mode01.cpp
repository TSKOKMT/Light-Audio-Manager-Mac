#include "mode01.h"

//--------------------------------------------------------------
vector<ofPtr<ofFloatColor>> mode01::get(float time_, int count_) {
    
    //SETUP
    
    vector<ofPtr<ofFloatColor>> colors;
    for (int i = 0; i < count_; i++) {
        ofPtr<ofFloatColor> colorPtr = ofPtr<ofFloatColor>(new ofFloatColor);
        colorPtr->setHsb(0.0, 0.2, 1.0);
        colors.push_back(colorPtr);
    }
    
    
    //UPDATE
    
    float angle = ofGetMouseX() / (float)ofGetWidth() * TWO_PI * 2;
    float height = ofGetMouseY() / (float)ofGetHeight() * 2;
    
    float t = time_;
    float angleR = (ofNoise(t / 8.) + pow(ofNoise(t / 4., 10), 4) * ofNoise(t * 6, 20) / 24.);
    float heightR = (ofNoise(t / 6., 100) + pow(ofNoise(t / 4., 110), 4) * ofNoise(t * 6, 120) / 12.);
    angleR = ofNormalize(cos(angleR * PI), 1, -1);
    heightR = ofNormalize(cos(angleR * PI), 1, -1);
    angleR *= TWO_PI;
    
    t -= 100;
    float angleG = (ofNoise(t / 8.) + pow(ofNoise(t / 4., 10), 4) * ofNoise(t * 6, 20) / 24.);
    float heightG = (ofNoise(t / 6., 100) + pow(ofNoise(t / 4., 110), 4) * ofNoise(t * 6, 120) / 12.);
    angleG = ofNormalize(cos(angleG * PI), 1, -1);
    heightG = ofNormalize(cos(angleG * PI), 1, -1);
    angleG *= TWO_PI;
    
    t -= 100;
    float angleB = (ofNoise(t / 8.) + pow(ofNoise(t / 4., 10), 4) * ofNoise(t * 6, 20) / 24.);
    float heightB = (ofNoise(t / 6., 100) + pow(ofNoise(t / 4., 110), 4) * ofNoise(t * 6, 120) / 12.);
    angleB = ofNormalize(cos(angleB * PI), 1, -1);
    heightB = ofNormalize(cos(angleB * PI), 1, -1);
    angleB *= TWO_PI;
    
    float hour = 23;
    for (int i = 0; i < colors.size(); i++) {
        float a = ofWrap(i / hour, 0, 1) * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = i / (float)colors.size();
        
        float theMotion = pow(ofNormalize(sin(a + angle), -1, 1), 100);
        theMotion *= pow(ofNormalize(sin((h + height) * TWO_PI), -1, 1), 4);
        
        float r = pow(ofNormalize(sin(a + angleR), -1, 1), 100);
        r *= pow(ofNormalize(sin((h + heightR) * TWO_PI), -1, 1), 4);
        float g = pow(ofNormalize(sin(a + angleG), -1, 1), 100);
        g *= pow(ofNormalize(sin((h + heightG) * TWO_PI), -1, 1), 4);
        float b = pow(ofNormalize(sin(a + angleB), -1, 1), 100);
        b *= pow(ofNormalize(sin((h + heightB) * TWO_PI), -1, 1), 4);
        
        colors[i]->set(r, g, b);
    }
    
    //DRAW
    
    //ofDrawLine(angle / TWO_PI / 2. * ofGetWidth(), 0, angle / TWO_PI / 2. * ofGetWidth(), ofGetHeight());
    //ofDrawLine(0, height / 2. * ofGetHeight(), ofGetWidth(), height / 2. * ofGetHeight());
    
    ofSetColor(255, 0, 0);
    ofDrawLine(angleR / TWO_PI * ofGetWidth(), 0, angleR / TWO_PI * ofGetWidth(), ofGetHeight());
    ofDrawLine(0, heightR * ofGetHeight(), ofGetWidth(), heightR * ofGetHeight());
    
    ofSetColor(0, 255, 0);
    ofDrawLine(angleG / TWO_PI * ofGetWidth(), 0, angleG / TWO_PI * ofGetWidth(), ofGetHeight());
    ofDrawLine(0, heightG * ofGetHeight(), ofGetWidth(), heightG * ofGetHeight());
    
    ofSetColor(0, 0, 255);
    ofDrawLine(angleB / TWO_PI * ofGetWidth(), 0, angleB / TWO_PI * ofGetWidth(), ofGetHeight());
    ofDrawLine(0, heightB * ofGetHeight(), ofGetWidth(), heightB * ofGetHeight());

    //RETURN
    
    return colors;
}
