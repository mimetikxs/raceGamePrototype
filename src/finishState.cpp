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
        bike->bPullover = true;
    }
};


void finishState::update(){
    //fadeout sound
    for(auto bike : app->race.bikes){
        float currentVol = bike->motorSound->getVolume();
        float newVol = currentVol - 0.005;
        
        if(newVol > 0){
            bike->motorSound->setVolume(newVol);
        }else{
            bike->motorSound->setVolume(0);
            bike->motorSound->setPaused(true);
        }
    }
};


void finishState::next(){
    app->setCurrentState(new startState(app));
    delete this;
};


void finishState::draw(){
    app->race.draw();
    app->panelTime.draw();
    app->panelWinners.draw();
    app->panelCup.draw();
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
