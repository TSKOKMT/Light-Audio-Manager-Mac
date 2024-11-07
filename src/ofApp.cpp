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
    /*auto ports = config["serialPorts"];
    int baud = config["serialBaudRate"];
    for (string port : ports) {
        ofPtr<ofSerial> s = ofPtr<ofSerial>(new ofSerial);
        s->setup(port, baud);
        serials.push_back(s);
    }*/
    
    //Setup led
    count = 420;
    
    //Setup volumeUnit
    myVolumeUnit.setup();
    
    //setup gui
    gui.setup();
    gui.add(unitID.set("Unit ID", 0, 0, 50));
    gui.add(receiverPort.set("Receiver Port", "10000"));
    gui.add(senderHost.set("Sender Host", "192.168.12.138"));
    gui.add(senderPort.set("Sender Port", "10000"));
    
    //Setup osc
    receiver.setup(1000);
    sender.setup("192.168.12.138", 10000);
    
    cout << "Sender Host " << sender.getHost() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle("Light Dance | FPS " + ofToString(round(ofGetFrameRate())) + " | Status " + statusNames[status] + " | LightingMode " + ofToString(lightingMode) + " | RelationNum " + ofToString(relationNum));
    
    //Update osc
    if (receiver.getPort() != ofToInt(receiverPort)) receiver.setup(ofToInt(receiverPort));
    if (sender.getHost() != (string)senderHost || sender.getPort() != ofToInt(senderPort)) sender.setup((string)senderHost, ofToInt(senderPort));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //UPDATE
    
    auto frame = ofGetWindowRect();
    
    float unit = sqrt(frame.width * frame.height) / 120.;
    
    float time = ofGetElapsedTimef();
    
    float volume = myVolumeUnit.get();
    
    float amp = 8;
    
    //Receive from UnitManager
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        cout << "Received | Adress " << m.getAddress() << endl;
        if (m.getAddress() == "/zone2/unit_setup") {
            string sceneStatus = m.getArgAsString(0);
            int lightingMode_ = m.getArgAsInt(1);
            
            if (sceneStatus == "SETUP") {
                lightingMode = lightingMode_;
            }
            
            cout << "/zone2/unit_setup | " << "sceneStatus " << sceneStatus << " | lightingMode " << lightingMode << endl;
            
            responseToZone2Manager();
        }
        if (m.getAddress() == "/zone2/unit_touch") {
            string sceneStatus = m.getArgAsString(0);
            float relationNum_ = m.getArgAsInt(1);
            
            if (sceneStatus == "SLEEP") status = 0;
            if (sceneStatus == "READY") status = 1;
            if (sceneStatus == "AWAKE") status = 2;
            if (sceneStatus == "FINAL") status = 3;
            
            relationNum = relationNum_;
            
            cout << "/zone2/unit_touch | " << "sceneStatus " << sceneStatus << " | relationNum " << relationNum << endl;
            
            responseToZone2Manager();
        }
        if (m.getAddress() == "/zone2/unit_realtion") {
            string sceneStatus = m.getArgAsString(0);
            float relationNum_ = m.getArgAsInt(1);
            
            if (sceneStatus == "SLEEP") status = 0;
            if (sceneStatus == "READY") status = 1;
            if (sceneStatus == "AWAKE") status = 2;
            if (sceneStatus == "FINAL") status = 3;
            
            relationNum = relationNum_;
            
            cout << "/zone2/unit_realtion | " << "sceneStatus " << sceneStatus << " | relationNum " << relationNum << endl;
            
            responseToZone2Manager();
        }
    }
    
    //Get & send colors
    vector<ofPtr<ofFloatColor>> colors;
    
    if (status == 0) colors = myMode01.get(time, count);
    if (status == 1) colors = myMode02.get(myVolumeUnit.volumeTime, count, volume * amp);
    //if (status == 2) colors = myMode03.get(time, count, volume * amp);
    if (status == 3) colors = myMode04.get(time, count, volume * amp);
    if (status == 2) colors = myMode05.get(time, count);
    send(colors);
    
    ofSetColor(0);
    ofDrawRectangle(frame);
    
    //Draw volume
    ofSetColor(255);
    //ofDrawCircle(ofGetWindowRect().getCenter(), volume * ofGetHeight());
    
    //Draw colors
    ofPushStyle();
    
    //Draw
    int countH = 28;
    int countV = 15;
    int VMap[15] = {0, 1, 2, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5};
    for (int i = 0; i < colors.size(); i++) {
        float indexH = i % countH;
        float indexV = i / countH;
        indexV = VMap[(int)indexV];
        indexH += .5;
        indexV += .5;
        
        float a = (float)indexH / countH * TWO_PI;
        float x = sin(a);
        float y = cos(a);
        float h = (float)indexV / countV;
        
        ofPoint position;
        position.x = ofMap(a, 0, TWO_PI, 0, ofGetWidth());
        position.y = ofMap(h, 0, 1, ofGetHeight(), 0);
        
        ofSetColor(colors[i]->r * 255, colors[i]->g * 255, colors[i]->b * 255);
        ofDrawCircle(position, unit);
    }
    
    ofPopStyle();
    
    //Draw gui
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT) status = ofWrap(status + 1, 0, statusCount);
    if (key == OF_KEY_LEFT) status = ofWrap(status - 1, 0, statusCount);
    
    if (key == ' ') responseToZone2Manager();
}

//--------------------------------------------------------------
void ofApp::responseToZone2Manager() {
    
    int unitStatusCode = 100;
    
    ofxOscMessage m;
    m.setAddress("/light_audio/unit_status");
    m.addIntArg(unitID);
    m.addIntArg(unitStatusCode);
    sender.sendMessage(m);
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
void ofApp::send(vector<ofPtr<ofFloatColor>> colors_) {
    
    //Copy colors
    vector<ofPtr<ofFloatColor>> colors;
    for (const auto& color : colors_) {
        ofPtr<ofFloatColor> newColor = ofPtr<ofFloatColor>(new ofFloatColor(*color));
        colors.push_back(newColor);
    }
    
    //Process colors
    float amp = .5;
    for (int i = 0; i < colors.size(); i++) {
        colors[i]->r = colors[i]->r * amp;
        colors[i]->g = colors[i]->g * amp;
        colors[i]->b = colors[i]->b * amp;
    }
    float power = 2;
    for (int i = 0; i < colors.size(); i++) {
        colors[i]->r = pow(colors[i]->r, power);
        colors[i]->g = pow(colors[i]->g, power);
        colors[i]->b = pow(colors[i]->b, power);
    }

    vector<unsigned char> buffer;
    
    int num = count / 5;

    //Prepare buffer
    for (int i = 0; i < colors.size(); i++) {
        if((i % num) == 0) buffer.push_back(255);
        auto c = colors[i];
        unsigned char r = c->r * 254;
        unsigned char g = c->g * 254;
        unsigned char b = c->b * 254;
        buffer.push_back(r);
        buffer.push_back(g);
        buffer.push_back(b);
    }
    
    //Send colors
    /*int i = 0;
    for (auto s : serials) {
        int startIdx = (num * 3 + 1) * i;
        int bufSize = num * 3 + 1;
        s->writeBytes(&buffer[startIdx], bufSize);
        i++;
    }*/
}
