//
//  Race.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//

#pragma once

#include "ofMain.h"

#include "Player.h"
#include "Bike.h"

// this is the racing state of the game

class Race {
    
public:
    
    Race();
    
    void setup();
    void update();
    void draw();
    void drawInfo();
    
    void start();
    void togglePause();
    
    Bike bike;
    Player player;
    ofImage collisionMap;
    ofImage progressMap;
    
private:
    
    bool bPaused, bStarted;
    
    uint64_t prevTime;
    uint64_t elapsedTime;
    
    void updateRanking();
    string getElapsedTimeString(); // TODO: move to ultils
};
