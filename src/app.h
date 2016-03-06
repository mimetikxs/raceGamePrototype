#ifndef __App__
#define __App__

#include "baseApp.h"
#include "Race.h"
#include "CountDown.h"
#include "PanelPower.h"


class App: public BaseApp
{
public:
    
    Race race;    
    // panels
    CountDown countDown;
    PanelPower panelPower;
    
    App();
    ~App(){};
};

#endif
