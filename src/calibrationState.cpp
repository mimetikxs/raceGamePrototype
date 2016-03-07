#include "calibrationState.h"
#include "startState.h"

calibrationState::calibrationState(App *a):BaseState(a){
    BaseState::initialize();
};

calibrationState::~calibrationState(){
};

void calibrationState::draw(){
    Assets::getInstance()->collisionMap.draw(0, 0);
};

void calibrationState::update(){};

void calibrationState::next(){
    app->setCurrentState(new startState(app));
    delete this;
};

void calibrationState::keypressed(int key){
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