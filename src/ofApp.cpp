#include "ofApp.h"
#include "runningState.h"



void ofApp::setup(){
    
    app = new App();
    app->setCurrentState(new runningState(app));
    osc = new OscAdapter(app);
    gui = new Gui(app);
}


void ofApp::draw(){

    ofClear(90);
    app->draw();
    gui->draw();
}
