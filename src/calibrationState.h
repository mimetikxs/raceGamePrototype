
#ifndef __calibration__state__
#define __calibration__state__

#include "baseState.h"
#include "app.h"

class calibrationState: public BaseState
{
public:
    calibrationState(App *a);
    ~calibrationState();
    string toString() { return "calibration"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
};

#endif