#ifndef __App__
#define __App__

#include "baseApp.h"
#include "Race.h"

class App: public BaseApp
{
public:
    
    Race race;
    
    App();
    ~App(){};
    
};

#endif
