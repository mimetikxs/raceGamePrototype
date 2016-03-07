#include "ofApp.h"
#include "runningState.h"
#include "startState.h"
#include "calibrationState.h"
#include "standbyState.h"


void ofApp::setup(){
    
    app = new App();
    app->setCurrentState(new standbyState(app));
    osc = new OscAdapter(app);
    gui = new Gui(app);
    
    // syphon
    syphon.setName("Racing game");
    outputFbo.allocate(1920, 1080);
}


void ofApp::draw(){
    
    outputFbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofClear(0);
    app->draw();
    ofDisableBlendMode();
    outputFbo.end();
    
    
    syphon.publishTexture(&outputFbo.getTexture());
    ofSetWindowShape(1920 / 2,  1080 / 2);
   
    outputFbo.getTexture().draw(0,0, 1920/2, 1080/2);
    gui->draw();
}
