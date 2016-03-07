//
//  PanelRanking.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelRanking {
    
public:
    
    PanelRanking();
    
    void setup(vector<Player*>* players);
    void draw();
    void drawDebug();
    
    vector<Player*> * players;
    
    ofVec2f position;
    
private:
    
    Assets* assets;
    
    ofTrueTypeFont presura22;
    ofTrueTypeFont presura31;
    
    ofVec2f p;
    vector<ofVec2f> positions;
    
    void drawPlayer(int i);
    
};
