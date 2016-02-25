//
//  Player.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//

#pragma once

#include "ofMain.h"

#include "Bike.h"


class Player {
    
public:
  
    Player(string _name, Bike& _bike)
    :name(_name)
    ,bike(_bike)
    ,rank(0)
    ,completedLaps(0)
    ,lapPercent(0.0)
    {}
    
    string name;
    
    int rank;              // ranking of this player in the race
    int completedLaps;     // number of completed laps
    float lapPercent;
    
    Bike& bike;
    
//    float getCurrentLapPercent(){
//        int numLaps = completedLaps; // get rid of decimals
//        return completedLaps - numLaps;
//    }
};
