

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
    
    string getPlayerName(int i);
    
    ofImage getCollisionMap();
    ofImage getMap();
    ofImage getBackground();
    ofImage getBikeImage(int i);
};

#endif
