//
//  Race.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//  this is the racing state of the game
//
//

#pragma once

#include "ofMain.h"

#include "Player.h"
#include "Bike.h"
#include "LineSegment.h"
#include "assets.h"
#include "PowerUp.h"

#define MAX_NUM_LAPS 5


class StartingMark{
public:
    ofVec2f position;
    float rotation;
    StartingMark(float x, float y, float _rotation){
        position.set(x, y);
        rotation = _rotation;
    }
    
    void draw();
};



class Race {
    
public:
    
    Race();
    
    void setup();
    void update();
    void draw();
    void drawInfo();
    
    void start();
    void togglePause();
    
    LineSegment finishingLine;
    
    vector<StartingMark> startingMarks;
    
    vector<Bike*> bikes;
    vector<Player*> players;
    
    ofParameterGroup parametersDriving;
    ofParameter<float> acceleration;
    ofParameter<float> friction;
    ofParameter<float> maxSpeed;
    ofParameter<float> rotationStep;
    ofParameter<float> scale;
    
    ofParameterGroup parametersCollision;
    ofParameter<float> frontFriction;
    ofParameter<float> sidesFriction;
    ofParameter<float> sidesRotation;
    ofParameter<float> bikeHitFriction;
    
    ofParameterGroup parametersMisc;
    ofParameter<float> maxStuckTime;
    ofParameter<bool> bDrawDebug;
    
    ofParameterGroup parametersPowerups;
    ofParameter<float> pu_acceleration;
    ofParameter<float> pu_friction;
    ofParameter<float> pu_maxSpeed;
    ofParameter<float> pu_rotationStep;
    
    void onParameterChange(ofAbstractParameter& param);
    
    
private:
    Assets *assets;
    
    bool bPaused, bStarted;
    
    uint64_t prevTime;
    uint64_t elapsedTime;
    
    int numLaps;
    
    void updateBikes();
    void updateRanking();
    void updateTimer();
    void checkStuck();
    string getElapsedTimeString();
    
    // power ups
    vector<PowerUp*> powerups;
    void updatePowerUps();
    float lasttime; // debug: elapsed when powerup was deactivated
};
