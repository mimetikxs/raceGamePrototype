

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
    bool useBikeCollisions();
    
    string getPlayerName(int i);
    int getPlayerPosition(int i);
    string getPlayerAttributes(int i);
    
    ofImage backgroundImg;
    ofImage collisionMap;
    ofImage progressMap;
    ofImage mask;
    
    ofImage bike1;
    ofImage bike2;
    ofImage bike3;
    ofImage bike4;
    ofImage bikeGlow;
    
    ofImage helmet1;
    ofImage helmet2;
    ofImage helmet3;
    ofImage helmet4;
    
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
    
    ofImage panelRankingBack;
    ofImage panelRankingFront;
    
    ofImage panelWinnersBack;
    ofImage panelWinnersFront;
    
    ofImage cupBack;
    ofImage cupFront;
    
    ofImage panelLapsBack;
    ofImage panelLapsFront;
    
    ofSoundPlayer motorSound[4];
    ofSoundPlayer cheer;
    ofSoundPlayer countdownSound;
    
    ofTrueTypeFont presura25;
    
    ofVideoPlayer countdown;
    
    ofVideoPlayer standby;
};

#endif
