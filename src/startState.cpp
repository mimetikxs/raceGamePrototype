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
    Assets::getInstance()->cheer.play();
    Assets::getInstance()->countdownSound.play();
    Assets::getInstance()->countdownSound.setMultiPlay(true);
    
};


void startState::update(){
    app->countDown.update();
    Assets::getInstance()->go.play();
    
    if (app->countDown.isFinished()) {
        Assets::getInstance()->cheer.play();
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
    Assets::getInstance()->countdownSound.stop();
    Assets::getInstance()->go.stop();
    Assets::getInstance()->cheer.stop();
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