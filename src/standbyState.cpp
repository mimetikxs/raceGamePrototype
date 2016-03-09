#include "standbyState.h"
#include "startState.h"

standbyState::standbyState(App *a):BaseState(a){
    BaseState::initialize();
    Assets::getInstance()->standby.play();
    Assets::getInstance()->standby.setLoopState(OF_LOOP_NORMAL);
    
    for(int i = 0; i < 4; i++){
        Assets::getInstance()->motorSound[i].setVolume(0);
    }
};

standbyState::~standbyState(){
};

void standbyState::draw(){
    Assets::getInstance()->standby.draw(0, 0);
};

void standbyState::update(){
    
    Assets::getInstance()->standby.update();
};

void standbyState::next(){
    Assets::getInstance()->stopVideos();
    app->setCurrentState(new startState(app));
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