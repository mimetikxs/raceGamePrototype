//
//  finishState.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#include "finishState.h"
#include "startState.h"
#include "runningState.h"
#include "standbyState.h"


finishState::~finishState(){};


finishState::finishState(App *a):BaseState(a){
    BaseState::initialize();
    
    // disable bike controls
    for(auto bike : app->race.bikes){
        bike->bAccelerate = false;
        bike->bTurnLeft = false;
        bike->bTurnRight = false;
        bike->bUsingPowerUp = false;
    }
};


void finishState::update(){
    app->race.update();
    app->countDown.update();
    if (app->countDown.isFinished()) {
        next();
    }
};


void finishState::next(){
    app->setCurrentState(new startState(app));
    delete this;
};


void finishState::draw(){
    app->race.draw();
    //app->race.drawInfo();
    
    // TODO:
    ofDrawBitmapStringHighlight("FINISHED!", ofGetWidth()/2, ofGetHeight()/2);
};


void finishState::keypressed(int key){
    switch (key) {
        case OF_KEY_RETURN:
            next(); // debug only
            break;
        default:
            break;
    }
}


void finishState::keyReleased(int key){
    switch (key) {
        default:
            break;
    }
}