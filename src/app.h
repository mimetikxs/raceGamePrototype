#ifndef __App__
#define __App__

#include "baseApp.h"
#include "Race.h"
#include "CountDown.h"
#include "PanelPower.h"
#include "PanelRanking.h"
#include "TimesPanel.h"


class App: public BaseApp
{
public:
    
    Race race;    
    // panels
    CountDown countDown;
    PanelPower panelPower;
    PanelRanking panelRanking;
    TimesPanel panelTime;
    
    App();
    ~App(){};
};

#endif
