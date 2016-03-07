//
//  PanelWinners.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelWinners {
    
public:
    
    PanelWinners();
    
    void setup(vector<Player*>* players);
    void draw();
    
    vector<Player*> * players;
    
    ofVec2f position;
    
private:
    
    Assets* assets;
    
    ofTrueTypeFont presura52;
    ofTrueTypeFont presura25;
    
    
    vector<ofVec2f> numberPositions;
    
    void drawPlayer(int i);
    

    
};
