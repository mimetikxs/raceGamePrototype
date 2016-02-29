#pragma once

#include "ofMain.h"
#include "app.h"
#include "gui.h"
#include "OscAdapter.h"
#include "ofxSyphon.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void draw();
    
    
    App *app;
    OscAdapter *osc;
    Gui *gui;
    
    // syphon
    ofFbo outputFbo;
    ofxSyphonServer syphon;
};
