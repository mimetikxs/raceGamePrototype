#include "runningState.h"
#include "standbyState.h"


runningState::runningState(App *a):BaseState(a){
    BaseState::initialize();
    
    app->race.setup();
    app->race.start();
};

runningState::~runningState(){};

void runningState::draw(){
    app->race.draw();
    app->race.drawInfo();
};

void runningState::update(){
    app->race.update();
};

void runningState::next(){
    app->setCurrentState(new standbyState(app));
    delete this;
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
            
            
        case 'w':
            bike2.bAccelerate = true;
            break;
        case 'a':
            bike2.bTurnLeft = true;
            break;
        case 'd':
            bike2.bTurnRight = true;
            break;
            
            
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
            
        case 'w':
            bike2.bAccelerate = false;
            break;
        case 'a':
            bike2.bTurnLeft = false;
            break;
        case 'd':
            bike2.bTurnRight = false;
            break;
            
        default:
            break;
    }
}