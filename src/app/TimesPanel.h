//
//  TimesPanel.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#pragma once


#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class TimesPanel {
    
public:
    
    TimesPanel();
    
    void setup(vector<Player*>* players);
    void draw();
    
    vector<Player*> * players;
    
private:
    
    Assets* assets;
    
    ofTrueTypeFont presura20;
    
    void drawPlayer(int i);
};
