#include "standbyState.h"
#include "runningState.h"

standbyState::standbyState(App *a):BaseState(a){
    BaseState::initialize();
};

standbyState::~standbyState(){
};

void standbyState::draw(){
};

void standbyState::update(){};

void standbyState::next(){
    app->setCurrentState(new runningState(app));
    delete this;
};

void standbyState::keypressed(int key){
    switch (key) {
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