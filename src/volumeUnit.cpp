#include "volumeUnit.h"

//--------------------------------------------------------------
void volumeUnit::setup() {
    
    fft = ofxFft::create(2048);
    ofSoundStreamSetup(0, 1, 48000, 128, 4);
}

//--------------------------------------------------------------
float volumeUnit::get() {
    
    previousTime = time;
    time = ofGetElapsedTimef();
    
    float exponent = 1.5;
    
    volume = pow(volume, exponent);
    
    float bottom = .05;
    float top = 1;
    float f = 3;
    
    float ease = ofClamp((volume - previousVolume) * f, bottom, top);
    
    //update trueVolume
    previousTrueVolume = trueVolume;
    trueVolume = previousTrueVolume + (volume - previousTrueVolume) * ease;
    trueVolume = math.meanFilter(trueVolume, 2);
    
    //Update volumeTime
    volumeTime += (time - previousTime) * pow(ofClamp(ofMap(trueVolume, 0, 1, 1, 0), 0, 1), .1);
    
    previousVolume = volume;
    
    return trueVolume;
}

//--------------------------------------------------------------
void volumeUnit::audioReceived(float *input, int bufferSize, int nChannels) {
    
    if (buffers.size() != bufferSize) buffers.resize(bufferSize);
    for (int i = 0; i < bufferSize; i++) {
        buffers[i] = abs(input[i]);
    }
    
    if (bins.size() != fft->getBinSize()) {
        bins.resize(fft->getBinSize());
    }
    fft->setSignal(input);
    memcpy(&bins[0], fft->getAmplitude(), sizeof(float) * fft->getBinSize());
    bins.resize(bins.size() / 2.);
    
    volume = ofxTskokmtMath::mean(buffers);
}
