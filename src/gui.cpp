#include "gui.h"


Gui::Gui(App *a){
    app = a;
    gui.setup();
    init();
    
    bVisible = true;
    load();
    ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
}

void Gui::draw(){
    if(bVisible)
        gui.draw();
}

void Gui::load(){
    string path = ofToDataPath("settings.xml");
    ofLogNotice() << "Loading gui from: " << path;
    gui.loadFromFile(path);
}

void Gui::save(){
    string path = ofToDataPath("settings.xml");
    ofLogNotice() << "Saving gui to: " << path;
    gui.saveToFile(path);
}

void Gui::toggleVisibility(){
    bVisible = !bVisible;
}

void Gui::keyPressed (ofKeyEventArgs& eventArgs){
    switch (eventArgs.key) {
        case 'i':
            toggleVisibility();
            break;
        case 's':
            save();
            break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void Gui::init(){
    gui.add(app->race.parametersDriving);
    gui.add(app->race.parametersCollision);
    gui.add(app->race.parametersMisc);
}

