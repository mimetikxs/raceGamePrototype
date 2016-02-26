

#ifndef __raceGamePrototype__gui__
#define __raceGamePrototype__gui__

#include "ofxGui.h"
#include "app.h"

class Gui
{
    ofxPanel gui;
    App *app;
    bool bVisible;
    
public:
    
    Gui(App *a);

    
    void draw();

    void load();

    void save();

    void toggleVisibility();
    void keyPressed(ofKeyEventArgs& eventArgs);
    void init();

};

#endif /* defined(__raceGamePrototype__gui__) */
