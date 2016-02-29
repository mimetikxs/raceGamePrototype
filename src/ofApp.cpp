#include "ofApp.h"
#include "runningState.h"



void ofApp::setup(){
    
    app = new App();
    app->setCurrentState(new runningState(app));
    osc = new OscAdapter(app);
    gui = new Gui(app);
    
    // syphon
    syphon.setName("Racing game");
    outputFbo.allocate(1024, 768);
}


void ofApp::draw(){
    
    outputFbo.begin();
    ofClear(0);
    app->draw();
    outputFbo.end();
    
    outputFbo.getTexture().draw(0,0);
    
    syphon.publishTexture(&outputFbo.getTexture());
    
    gui->draw();
}
