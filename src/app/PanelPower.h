//
//  PanelPower.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 05/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelPower {
    
public:
    
    PanelPower();
    
    void setup(vector<Player*>* players);
    void draw();
    
    vector<Player*> * players;
    
    ofVec2f position;
    
private:
    
    ofFbo fboBars;
    vector<ofVec2f> barPositions;
    ofMesh mask;
    float maskTopMin;
    float maskTopMax;
    float maskBottomMin;
    float maskBottomMax;
    
    void drawPowerBar(int index);
    
    Assets* assets;
};
