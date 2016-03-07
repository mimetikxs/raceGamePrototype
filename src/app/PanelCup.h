//
//  PanelCup.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 07/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelCup {
    
public:
    
    PanelCup();
    
    void setup();
    void draw();
    void drawDebug();
    
    ofVec2f position;
    
private:
    
    Assets* assets;    
};


