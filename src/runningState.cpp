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
    switch (key) {
        case OF_KEY_UP:
            app->race.bike.bAccelerate = true;
            break;
        case OF_KEY_LEFT:
            app->race.bike.bTurnLeft = true;
            break;
        case OF_KEY_RIGHT:
            app->race.bike.bTurnRight = true;
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
    switch (key) {
        case OF_KEY_UP:
            app->race.bike.bAccelerate = false;
            break;
        case OF_KEY_LEFT:
            app->race.bike.bTurnLeft = false;
            break;
        case OF_KEY_RIGHT:
            app->race.bike.bTurnRight = false;
            break;
            
        default:
            break;
    }
}