//
//  CountDown.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#pragma once
#include "ofMain.h"
#include "assets.h"

class CountDown {

public:
    CountDown();
    
    void start();
    bool isFinished();
    
    void update();
    void draw();
    void stop();
    
    Assets* assets;
};
