

#ifndef __assets__
#define __assets__

#include "baseAssets.h"


class Assets: public BaseAssets
{
    static Assets* instance;
    Assets();

public:
    static Assets* getInstance();
    void loadAssets();
};

#endif
