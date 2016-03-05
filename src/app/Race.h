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
#include "PowerUpsManager.h"



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
    bool isFinised(){ return bFinished; }
    
    LineSegment finishingLine;
    
    vector<StartingMark> startingMarks;
    
    vector<Bike*> bikes;
    vector<Player*> players;
    
    PowerUpsManager powerupsManager;
    
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
    
    bool bStarted, bFinished;
    
    uint64_t prevTime;
    uint64_t elapsedTime;
    
    float rankLastTime;
    
    int numLaps;
    
    void updateBikes();
    void updatePlayers();
    void updateRanking();
    void updateTimer();
    void checkStuck();
    string getElapsedTimeString();
    
    
};
