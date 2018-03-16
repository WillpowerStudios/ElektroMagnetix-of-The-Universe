#include "ofApp.h"

// Please share your updates if you've made cool changes ^_^

//--------------------------------------------------------------
void ofApp::setup(){
    // Scene
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    ofEnableAlphaBlending();
    ofSetVerticalSync( true );
    ofSetWindowTitle("AudioReactive LED Strip");
    ofEnableSmoothing();
    
    // Audio In
    // output channels,
    // 2 input channels,
    // 44100 samples per sec
    // 900 samples per buffer
    // 4 num buggers (latency)
    
    soundStream.printDeviceList();
    
    // if you want to set a different device id
    // soundStream.setDeviceID(0);
    // the device id corresponds to all audio devices, including input-only and output-only.
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    bufferCounter   = 0;
    drawCounter     = 0;
    smoothedVol     = 0.0;
    scaledVol       = 0.0;
    smoothedVolL     = 0.0;
    scaledVolL       = 0.0;
    smoothedVolR     = 0.0;
    scaledVolR       = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    // Visual
    ofSetCircleResolution(80);
    
    // Serial > Send
    serial.setup("/dev/cu.usbmodem1411", 9600);
    //serial.setup("/dev/cu.usbmodem1421", 9600);
    serial.startContinuousRead(false);
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
    
    message = "a";
    remember = false;
}

void ofApp::onNewMessage(string & message){
    cout << "onNewMessage, message: " << message << "\n";
}


//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Background
    ofSetColor(0,0,0,11);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    // Sound Reactivity
    float p = 0;
    float high = 0;
    
    //ofSetColor(255);
    ofSetLineWidth(2.0f);
    
    for(int i = 0; i < bufferSize - 1; i+=1) {
        
        // p is incrementing left channel input based on bufferSize
        p += left[i/2];
        if (left[i/2] > high) {
            high = left[i/2];
        }
        
        // color
        ofSetColor(255 + i, 50 + i / 3, 255 + i / 4);
        
        
        // Vertical Sound Visualization > Adaptive Screen Size
        ofDrawLine((ofGetWidth()/2-10) - (300*(p/2)), i, (ofGetWidth()/2-10) - (300*(p/2)), i+1 );
        ofDrawLine((ofGetWidth()/2+10) + (300*(p/2)),i, (ofGetWidth()/2+10) + (300*(p/2)), i+1 );
        
        // Vertical Sound Visualization
//        ofDrawLine(710 - (400*p), i, 710 - (400*p), i+1 );
//        ofDrawLine(730 + (400*p),i, 730 + (400*p), i+1 );
        
        // Vertical Sound Visualization 02
        //ofDrawLine(710 - (400*left[i]), i, 710 - (400*left[i+1]), i+1 );
        //ofDrawLine(730 + (400*right[i]),i, 730 + (400*right[i+1]), i+1 );
        
        //Horizontal Sound Visualization
        //ofDrawLine(i, 390 - (400*left[i]), i+1, 390 - (400*left[i+1]));
        //ofDrawLine(i, 410 + (400*right[i]), i+1, 410 + (400*right[i+1]));
    }
    
    // Turn on LEDs to sound input
    if (p > .5/* || high > 9*/) {
        float mapped = ofMap(p, 0, 30, 0, 1);
        ofSetColor(255 * mapped, 255 * mapped, 255 * mapped);
        // The circle drawn is a representation of the LEDs picking up Sound
        ofDrawCircle(ofGetWidth()/4,ofGetHeight() /2,200);
        ofDrawCircle(ofGetWidth()/1.35,ofGetHeight() /2,200);
        int a = round(mapped * 1400);
        
        // If Audio is detected, send message to Arduino ('a') > LED's Light up
        cout << "sending message: " << message << "\n";
                serial.writeString(message);
                message = "a";
    }
    
}

//--------------------------------------------------------------
void ofApp::audioIn( float * input, int bufferSize, int nChannels ){
    
    //float curVol = 0.0;
    float curVolL = 0.0;
    float curVolR = 0.0;
    
    // samples are interleaved
    int numCounted = 0;
    
    // lets go through each sample and calculate the root mean square which is a rough way to calculate vol
    for ( int i = 0; i < bufferSize; i++ ) {
        left[i]     = input[i*2]*.5;
        right[i]    = input[i*2+1]*.5;
        
        //        curVol += left[i] * left[i];
        //        curVol += right[i] * right[i];
        
        curVolL += left[i] * left[i];
        curVolR += right[i] * right[i];
        
        
        numCounted += 2;
    }
    
    // this is how we get the mean of rms ;)
    //curVol /= (float)numCounted;
    curVolL /= (float)numCounted;
    curVolR /= (float)numCounted;
    
    // this is how we get the root of rms :)
    //curVol = sqrt( curVol );
    curVolL = sqrt( curVolL );
    curVolR = sqrt( curVolR );
    
    
    //smoothedVol *= .83;
    smoothedVolL *= .83;
    smoothedVolR *= .83;
    smoothedVolL += .07 * curVolL;
    smoothedVolR += .07 * curVolR;
    
    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Audio In
    if( key == 's' ) {
        soundStream.start();
    }
    
    if ( key == 'e' ) {
        soundStream.stop();
    }
    
    //
    
    // Serial > send
    switch (key) {
        case 32: //space
            remember = true;
            break;
    }
}



// WILLPOWER STUDIOS
// The Creation of Worlds

// Site: http://WillpowerStudios.com
// Patreon: https://www.patreon.com/WillpowerStudios
// YouTube: https://www.youtube.com/willpowerstudios
// Instagram: https://www.instagram.com/willpowerstudios/
// Facebook: https://www.facebook.com/WillpowerStudios
// Twitter: https://twitter.com/willpowerstudio
// Medium: https://medium.com/@WillpowerStudios
// Meetup: https://www.meetup.com/CreativeCodingLA/
// Pinterest: https://www.pinterest.com/WillpowerStudio/
// Tumblr: http://willpowerlifeforce.com/
// Newsletter: http://willpowerstudios.us2.list-manage1.com/subscribe?u=a938b14fc35411d305eebfc9f&id=51b5411ac6
// vimeo: https://vimeo.com/willpowerstudios
// Github: https://github.com/WillpowerStudios
