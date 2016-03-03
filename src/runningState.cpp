#include "runningState.h"
#include "standbyState.h"
#include "finishState.h"


runningState::~runningState(){};


runningState::runningState(App *a):BaseState(a){
    BaseState::initialize();
    
    app->race.start();
};


void runningState::update(){
    app->race.update();
    if(app->race.isFinised()){
        next();
    }
};


void runningState::next(){
    app->setCurrentState(new finishState(app));
    delete this;
};


void runningState::draw(){
    app->race.draw();
    app->race.drawInfo();
};


void runningState::keypressed(int key){
    Bike& bike1 = *app->race.bikes[0];
    Bike& bike2 = *app->race.bikes[1];
    
    switch (key) {
        case OF_KEY_UP:
            bike1.bAccelerate = true;
            break;
        case OF_KEY_LEFT:
            bike1.bTurnLeft = true;
            break;
        case OF_KEY_RIGHT:
            bike1.bTurnRight = true;
            break;
        case '0':
            bike1.activatePower();
            break;
            
        case 'w':
            bike2.bAccelerate = true;
            break;
        case 'a':
            bike2.bTurnLeft = true;
            break;
        case 'd':
            bike2.bTurnRight = true;
            break;
        case '1':
            bike2.activatePower();
            break;
        
        // debug only, state changes when race is finished
        case ' ':
            next();
            break;
        case 13:
            next();
            break;
        default:
            break;
    }
}


void runningState::keyReleased(int key){
    Bike& bike1 = *app->race.bikes[0];
    Bike& bike2 = *app->race.bikes[1];
    
    switch (key) {
        case OF_KEY_UP:
            bike1.bAccelerate = false;
            break;
        case OF_KEY_LEFT:
            bike1.bTurnLeft = false;
            break;
        case OF_KEY_RIGHT:
            bike1.bTurnRight = false;
            break;
        case '0':
            bike1.deactivatePower();
            break;
            
        case 'w':
            bike2.bAccelerate = false;
            break;
        case 'a':
            bike2.bTurnLeft = false;
            break;
        case 'd':
            bike2.bTurnRight = false;
            break;
        case '1':
            bike2.deactivatePower();
            break;
            
        default:
            break;
    }
}