#include "baseState.h"

BaseState::BaseState(App *a){
    timer = ofGetElapsedTimef();
    app = a;
}

void BaseState::initialize(){
    ofLogNotice() << "State: " << toString();
}

BaseState::~BaseState(){
    
}

bool BaseState::isDone(int duration){
    return (ofGetElapsedTimef() - timer) >= duration;
}
