//
//  startState.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#include "startState.h"
#include "runningState.h"
#include "standbyState.h"


startState::~startState(){};


startState::startState(App *a):BaseState(a){
    BaseState::initialize();
    
    app->race.setup();
};


void startState::update(){
    app->countDown.update();
    if (app->countDown.isFinished()) {
        next();
    }
};


void startState::next(){
    app->setCurrentState(new runningState(app));
    delete this;
};


void startState::draw(){
    app->race.draw();
    
    // TODO: show count down video
    ofDrawBitmapStringHighlight("3, 2, 1... GO!", ofGetWidth()/2, ofGetHeight()/2);
};


void startState::keypressed(int key){
    switch (key) {
        case OF_KEY_RETURN:
            next(); // debug only
            break;
        default:
            break;
    }
}


void startState::keyReleased(int key){
    switch (key) {
        default:
            break;
    }
}