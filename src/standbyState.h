
#ifndef __standby__state__
#define __standby__state__

#include "baseState.h"
#include "app.h"

class standbyState: public BaseState
{
public:
    standbyState(App *a);
    ~standbyState();
    string toString() { return "standby"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
};

#endif