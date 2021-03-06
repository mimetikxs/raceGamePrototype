
#ifndef __calibration__state__
#define __calibration__state__

#include "baseState.h"
#include "app.h"

class calibrationState: public BaseState
{
public:
    int x, y;
    int px, py;
    float sx, sy;
    calibrationState(App *a);
    ~calibrationState();
    string toString() { return "calibration"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
};

#endif