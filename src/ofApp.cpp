#include "ofApp.h"
#include "runningState.h"
//#include "startState.h"


void ofApp::setup(){
    
    app = new App();
    app->setCurrentState(new runningState(app));
    osc = new OscAdapter(app);
    gui = new Gui(app);
    
    // syphon
    syphon.setName("Racing game");
    outputFbo.allocate(1920, 1080);
}


void ofApp::draw(){
    
    outputFbo.begin();
    ofClear(0);
    app->draw();
    outputFbo.end();
    
    syphon.publishTexture(&outputFbo.getTexture());
    
    outputFbo.getTexture().draw(0,0);
    gui->draw();
}
