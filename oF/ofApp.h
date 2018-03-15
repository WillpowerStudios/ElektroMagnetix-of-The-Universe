// WILLPOWER STUDIOS / 2018 13 03
// http://willpowerstudios.com / https://www.instagram.com/willpowerstudios/
// Project inspired by Engineerish > https://youtu.be/tcMK2Unvxtc
// Being an openFrameworks user, I decided to recreate the hack using oF while playing with the visuals to do live projections with interactive LEDs mapping structures in physical spaces
// Big thank you to Engineerish ^_^
// Please share your updates if you've made cool changes ^_^
// The idea is to have a projection mapping + LEDs animating in a space
// If you know how to make this system wireless please share:
// - mic sensor + power for LEDs > All running from Arduino / ESP32 / Other

// Make sure you use the addon ofxSimpleSerial > https://github.com/LeoColomb/ofxSimpleSerial

#pragma once
#include "ofMain.h"

// SERIAL
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"
using namespace std;


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    // Audio In
    void audioIn( float * input, int bufferSize, int nChannels );

    vector <float> left;
    vector <float> right;
    
    int bufferSize = 1024;
    int bufferCounter;
    int drawCounter;
    
    float smoothedVol;
    float smoothedVolL;
    float smoothedVolR;
    float scaledVol;
    float scaledVolL;
    float scaledVolR;
    
    //int bufferSize = 512;
    ofSoundStream soundStream;
    
    
    // Serial
    void                onNewMessage(string & message);
    ofxSimpleSerial     serial;
    string              message;
    bool                remember;
    bool                requestRead;
    int                 serial01;
    
};



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

