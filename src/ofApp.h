#pragma once

#include "ofMain.h"
#include "app.h"
#include "gui.h"
#include "OscAdapter.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void draw();
    
    
    App *app;
    OscAdapter *osc;
    Gui *gui;
    
};
