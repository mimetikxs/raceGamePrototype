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
    Assets::getInstance()->loadSettings();
    
    app->race.setup();
    app->countDown.start();
    
    Assets::getInstance()->countdownSound.play();
    
};


void startState::update(){
    app->countDown.update();
    if (app->countDown.isFinished()) {
        next();
    }
};


void startState::next(){
    app->countDown.stop();
    app->setCurrentState(new runningState(app));
    Assets::getInstance()->countdownSound.stop();
    
    delete this;
};


void startState::draw(){
    app->race.draw();
    app->panelTime.draw();
    app->countDown.draw();
    app->panelRanking.draw();
};

void startState::cancel(){
    app->countDown.stop();
    app->setCurrentState(new standbyState(app));
    delete this;
};

void startState::keypressed(int key){
    switch (key) {
        case OF_KEY_RETURN:
            next(); // debug only
            break;
        case 'q':
            cancel();
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