#ifndef __App__
#define __App__

#include "baseApp.h"
#include "Race.h"
//#include "CountDown.h"

class App: public BaseApp
{
public:
    
    Race race;
//    CountDown countDown;
    
    App();
    ~App(){};
};

#endif
