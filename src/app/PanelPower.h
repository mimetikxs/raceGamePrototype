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


class PanelPower {
    
public:
    
    PanelPower(vector<Player*>& players);
    
    // reference to players
    vector<Player*>& players;
};
