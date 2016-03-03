//
//  finishState.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 03/03/2016.
//
//

#pragma once

#include "baseState.h"
#include "app.h"

class finishState: public BaseState
{
public:
    finishState(App *a);
    ~finishState();
    string toString() { return "finished"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
    void keyReleased(int key);
};
