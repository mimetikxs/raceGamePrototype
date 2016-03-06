

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
    
    int getNumLaps();
    
    string getPlayerName(int i);
    ofColor getPlayerColor(int i);
    
    ofImage backgroundImg;
    ofImage collisionMap;
    ofImage progressMap;
    
    ofImage bike1;
    ofImage bike2;
    ofImage bike3;
    ofImage bike4;
    ofImage bikeGlow;
    
    ofImage helmet1;
    ofImage helmet2;
    ofImage helmet3;
    ofImage helmet4;
    ofImage& getHelmet(int i);
    
    ofImage powerup1;
    ofImage powerup2;
    ofImage powerup3;
    ofImage powerup4;
    ofImage powerupGlow1;
    ofImage powerupGlow2;
    ofImage powerupGlow3;
    ofImage powerupGlow4;
    vector<ofImage*> getRandomPowerupImage();
    
    ofImage panelPower0;
    ofImage panelPower1;
    ofImage powerBar;
    
    ofImage panelRanking;
    
    ofImage panelWinners;
    ofImage cup;
    
    ofImage panelLaps;
};

#endif
