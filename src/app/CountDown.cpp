//
//  CountDown.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#include "CountDown.h"


CountDown::CountDown(){
    assets = Assets::getInstance();
    assets->countdown.setLoopState(OF_LOOP_NONE);
}

void CountDown::start(){
    assets->countdown.play();
}


bool CountDown::isFinished(){
   return assets->countdown.getIsMovieDone();
}


void CountDown::update(){
    assets->countdown.update();
}


void CountDown::draw(){
    assets->countdown.draw(1334,754, 253,273);
}