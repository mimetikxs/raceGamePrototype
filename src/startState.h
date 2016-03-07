//
//  startState.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#pragma once

#include "baseState.h"
#include "app.h"

class startState: public BaseState
{
public:
    startState(App *a);
    ~startState();
    string toString() { return "starting"; }
    void update();
    void draw();
    void next();
    void cancel();
    void keypressed(int key);
    void keyReleased(int key);
};
