#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(false);
    ofSetWindowShape(ofGetScreenWidth() * (16 / 18.), ofGetScreenWidth() / 2.);
    ofSetWindowPosition((ofGetScreenWidth() - ofGetWidth()) / 2., (ofGetScreenHeight() - ofGetHeight()) / 2.);
    ofBackground(0);
    ofSetCircleResolution(60);
    ofSetLineWidth(10);
    ofSetFrameRate(200);
    
    ofJson config = ofLoadJson("config.json");
    
    //Setup serial
    auto ports = config["serialPorts"];
    int baud = config["serialBaudRate"];
    for (string port : ports) {
        ofPtr<ofSerial> s = ofPtr<ofSerial>(new ofSerial);
        s->setup(port, baud);
        serials.push_back(s);
    }
    
    //Setup led
    count = 420;
    cout << "Count : " << count << endl;
    
    //Setup volumeUnit
    myVolumeUnit.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle("Light Dance | FPS " + ofToString(round(ofGetFrameRate())) + " | Mode " + ofToString(mode));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    auto frame = ofGetWindowRect();
    
    float unit = sqrt(frame.width * frame.height) / 120.;
    
    float time = ofGetElapsedTimef();
    
    float volume = myVolumeUnit.get();
    
    float amp = 8;
    
    //Get & send colors
    vector<ofPtr<ofFloatColor>> colors;
    if (mode == 0) colors = myMode01.get(time, count);
    if (mode == 1) colors = myMode02.get(myVolumeUnit.volumeTime, count, volume * amp);
    if (mode == 2) colors = myMode03.get(time, count, volume * amp);
    if (mode == 3) colors = myMode04.get(time, count, volume * amp);
    if (mode == 4) colors = myMode05.get(time, count);
    send(colors);
    
    ofSetColor(0);
    ofDrawRectangle(frame);
    
    //Draw volume
    ofSetColor(255);
    ofDrawCircle(ofGetWindowRect().getCenter(), volume * ofGetHeight());
    
    //Draw colors
    ofPushStyle();
    
    //Draw
    int lineCount = count / 10;
    for (int i = 0; i < colors.size(); i++) {
        int angleIdx = i / lineCount;
        int heightIdx = i % lineCount;
        if (angleIdx % 2) {
            heightIdx = lineCount - heightIdx - 1;
        }
        
        float a = (float)angleIdx / 10 * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)heightIdx / lineCount;
        
        ofPoint position = ofPoint(ofMap(a, 0, TWO_PI, 0, ofGetWidth()), ofMap(h, 1, 0, 0, ofGetHeight()));
        
        ofSetColor(colors[i]->r * 255, colors[i]->g * 255, colors[i]->b * 255);
        ofDrawCircle(position, unit);
    }
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT) mode = ofWrap(mode + 1, 0, modeCount);
    if (key == OF_KEY_LEFT) mode = ofWrap(mode - 1, 0, modeCount);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

    myMode04.load(dragInfo.files.front());
}

//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    
    myVolumeUnit.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::send(vector<ofPtr<ofFloatColor>> &colors_) {
    
    vector<unsigned char> buffer;
    
    int num = count / 5;
    
    //Process
    float power = 2;
    for (int i = 0; i < colors_.size(); i++) {
        colors_[i]->r = pow(colors_[i]->r, power);
        colors_[i]->g = pow(colors_[i]->g, power);
        colors_[i]->b = pow(colors_[i]->b, power);
    }

    for (int i = 0; i < colors_.size(); i++) {
        if((i % num) == 0) buffer.push_back(255);
        auto c = colors_[i];
        unsigned char r = c->r * 254;
        unsigned char g = c->g * 254;
        unsigned char b = c->b * 254;
        buffer.push_back(r);
        buffer.push_back(g);
        buffer.push_back(b);
    }
    
    int i = 0;
    for (auto s : serials) {
        int startIdx = (num * 3 + 1) * i;
        int bufSize = num * 3 + 1;
        s->writeBytes(&buffer[startIdx], bufSize);
        i++;
    }
}
