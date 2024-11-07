#pragma once

#include "ofMain.h"

#include "mode01.h"
#include "mode02.h"
#include "mode03.h"
#include "mode04.h"
#include "mode05.h"

#include "volumeUnit.h"

class ofApp : public ofBaseApp{

public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    void audioReceived(float* input, int bufferSize, int nChannels);
		
private:
    vector<ofPtr<ofSerial>> serials;
    void send(vector<ofPtr<ofFloatColor>> &colors_);
    
    int count;
    
    int mode = 4;
    mode01 myMode01;
    mode02 myMode02;
    mode03 myMode03;
    mode04 myMode04;
    mode05 myMode05;
    int modeCount = 5;
    
    volumeUnit myVolumeUnit;
};