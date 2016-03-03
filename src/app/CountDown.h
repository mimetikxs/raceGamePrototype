//
//  CountDown.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#pragma once

class CountDown {

public:
    CountDown();
    
    void start();
    bool isFinished();
    
    void update();
    void draw();
};
