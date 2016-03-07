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
  
    Player(string _name, Bike* _bike, ofImage* _helmet, ofColor _textColor, ofColor _trailColor, int _rankPos)
    :name(_name)
    ,bike(_bike)
    ,helmet(_helmet)
    ,textColor(_textColor)
    ,trailColor(_trailColor)
    ,rankPos(_rankPos)
    ,completedLaps(0)
    ,lapPercent(0.0)
    ,lastLapTimeString("00:00:00")
    {}
    
    // attributes
    string name;
    ofColor textColor;
    ofColor trailColor;
    
    // race data
    int startingIndex;     // player will start the race in this postion
    int rankPos;           // ranking of this player in the race (0 based)
    int completedLaps;     // number of completed laps
    float lapPercent;
    
    string lastLapTimeString;
    
    Bike* bike;
    
    ofImage* helmet;
};
