//
//  Race.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//

#include "Race.h"

#define MAX_NUM_LAPS 5


Race::Race()
: finishingLine(1333, 79, 1333, 286)
{
    // init parameters
    parametersDriving.add( acceleration.set("acceleration", 0.4, 0.0, 2.0) );
    parametersDriving.add( friction.set("friction", 0.85, 0.5, 0.999) );
    parametersDriving.add( maxSpeed.set("max speed", 2.0, 1.0, 50.0) );
    parametersDriving.add( rotationStep.set("rotation step", 0.17, 0.0001, 1.0) );
    parametersDriving.add( scale.set("scale", 40, 1, 100) );
    parametersCollision.add( frontFriction.set("front friction", 0.33, 0.99, 0.1) );
    parametersCollision.add( sidesFriction.set("sides friction", 0.85, 0.99, 0.1) );
    parametersCollision.add( sidesRotation.set("sides rotation", 0.01, 0.001, 0.05) );
    parametersCollision.add( bikeHitFriction.set("bike hit friction", 0.85, 0.5, 0.999) );
    parametersMisc.add( maxStuckTime.set("max stuck time", 3, 0, 5) );
    parametersMisc.add( bDrawDebug.set("debug mode", true) );
    parametersPowerups.add( pu_acceleration.set("pu acceleration", 0.4, 0.0, 2.0) );
    parametersPowerups.add( pu_friction.set("pu friction", 0.85, 0.5, 0.999) );
    parametersPowerups.add( pu_maxSpeed.set("pu max speed", 2.0, 1.0, 50.0) );
    parametersPowerups.add( pu_rotationStep.set("pu rotation step", 0.17, 0.0001, 1.0) );
    
    ofAddListener(parametersDriving.parameterChangedE(), this, &Race::onParameterChange);
    ofAddListener(parametersCollision.parameterChangedE(), this, &Race::onParameterChange);
    ofAddListener(parametersPowerups.parameterChangedE(), this, &Race::onParameterChange);

    bPaused = false;
    bStarted = false;
    assets = Assets::getInstance();
    
    collisionMap = assets->getMap();
    progressMap = assets->getCollisionMap();
    bikeImage = assets->getBikeImage(0);
    backgroundImg = assets->getBackground();
    
    // testing power ups
    powerups.push_back( new PowerUp(527, 913, 20) );
    powerups[0]->active = true;
    
    numLaps = 0;
}


void Race::setup(){
    
    // init starting marks
    // TODO: load from json
    startingMarks.push_back(StartingMark(1248, 148, PI/2));
    startingMarks.push_back(StartingMark(1202, 211, PI/2));
    startingMarks.push_back(StartingMark(1105, 148, PI/2));
    startingMarks.push_back(StartingMark(1054, 211, PI/2));
    
    // init bikes
    // TODO: load bike sprites from json
    bikes.push_back(new Bike(&bikeImage));
    bikes.push_back(new Bike(&bikeImage));
    bikes.push_back(new Bike(&bikeImage));
    bikes.push_back(new Bike(&bikeImage));
    
    // init players
    // TODO: get constructor values from json
    players.push_back(new Player(assets->getPlayerName(0), bikes[0], ofColor::mediumOrchid, 0));
    players.push_back(new Player(assets->getPlayerName(1), bikes[1], ofColor::mediumSeaGreen, 1));
    players.push_back(new Player(assets->getPlayerName(2), bikes[2], ofColor::mediumTurquoise, 2));
    players.push_back(new Player(assets->getPlayerName(3), bikes[3], ofColor::sandyBrown, 3));
    
    // position bikes on the starting position
    for(auto player : players){
        ofVec2f pos = startingMarks[player->rankPos].position;
        float rot = startingMarks[player->rankPos].rotation;
        player->bike->setPosition(pos.x, pos.y);
        player->bike->setRotation(rot);
    }
}


void Race::start() {
    bStarted = true;
    elapsedTime = 0;
    numLaps = 0;
    prevTime = ofGetElapsedTimeMillis();
}


void Race::update(){
    if(bStarted){
        updateBikes();
        
        updatePowerUps();
        
        checkStuck();
        
        updateTimer();
        
        // this can be updated at a diferent rate
        updateRanking();
    }
}


void Race::draw() {
    //collisionMap.draw(0,0);
    backgroundImg.draw(0,0);
    
    //finishingLine.draw();
    
    if(bDrawDebug){
        for(auto powerUp : powerups){
            if(powerUp->active)
                powerUp->drawDebug();
        }
        for(auto & player : players){
            player->bike->drawDebug(player->color);
        }
    }else{
        for(auto powerUp : powerups){
            if(powerUp->active)
                powerUp->drawDebug();
        }
        for(auto & player : players){
            player->bike->draw(player->color);
        }
    }
}


void Race::drawInfo(){
    // timer
    ofDrawBitmapStringHighlight(getElapsedTimeString(), 1244, 868);
    
    // players info
    for(auto player : players){
        string name = player->name;
        string completedLaps = "LAP: " + ofToString(player->completedLaps);
        string completedPct  = ofToString(player->lapPercent*100, 2) + "%";
        float x = 1244 + 120 * player->rankPos;
        ofDrawBitmapStringHighlight(name, x, 918, player->color);
        ofDrawBitmapStringHighlight(completedLaps, x, 938, player->color);
        ofDrawBitmapStringHighlight(completedPct, x, 958, player->color);
        
        // power bar
        float powerPct  = player->bike->powerbar.getPercent();
        ofPushStyle();
        ofSetColor(player->color);
        ofNoFill();
        ofDrawRectangle(x-4, 968, 100, 15);
        ofFill();
        ofDrawRectangle(x-4, 968, 100*powerPct, 15);
        ofPopStyle();
    }
    
    ofDrawBitmapStringHighlight("LAP: " + ofToString(numLaps) + "/" + ofToString(MAX_NUM_LAPS), 1244, 888);
}


void Race::updateBikes(){
    //bikes[0]->bAccelerate = true; // debugging
    
    for(auto bike : bikes){
        bike->update();
        bike->doNAACollision(&collisionMap);
    }
    
    // bike-bike collision:
    
    // reset collision flags
    for(auto bike : bikes){
        for(auto & circle : bike->getCollisionCircles()){
            circle.isColliding = false;
        }
    }
    
    // check collisions
    for(int i = 0; i < bikes.size(); i++){
        Bike* bike1 = bikes[i];
        for(int j = i + 1; j < bikes.size(); j++){
            Bike* bike2 = bikes[j];
            
            bike1->doBikeCollision(bike2);
        }
    }
}


void Race::checkStuck(){
    for(auto player : players){
        Bike* bike = player->bike;
        if(bike->getTimeStuck() > maxStuckTime){
            ofVec2f pos = startingMarks[player->rankPos].position;
            float rot = startingMarks[player->rankPos].rotation;
            bike->setPosition(pos.x, pos.y);
            bike->setRotation(rot);
        }
    }
}


void Race::updateRanking(){
    for(auto player : players){
        Bike * bike = player->bike;
        
        // check if line crossed
        ofVec2f prevPos = bike->getFrontPos() - bike->getVelocity();
        float prevDistance = finishingLine.getDistance(prevPos);
        float currentDistance = finishingLine.getDistance(bike->getFrontPos());
        if(prevDistance < 0  && currentDistance >= 0){
            
            // update completed laps
            player->completedLaps += 1;
        }
        
        const ofVec2f p = bike->getPosition();
        bool isInsideTrack = (collisionMap.getPixels().getColor(p.x, p.y).r != 0);
        if (isInsideTrack){
            ofColor color = progressMap.getPixels().getColor(p.x, p.y);
            float percent = color.r / 255.f;
            
            // update completed percentage of current lap
            player->lapPercent = percent;
        }
    }
    
    // sort player ranking
    for(int i = 0; i < players.size(); i++){
        Player* playerA = players[i];
        int rankA = playerA->rankPos;
        float completedA = playerA->completedLaps + playerA->lapPercent;
        
        for(int j = i+1; j < players.size(); j++){
            Player* playerB = players[j];
            int rankB = playerB->rankPos;
            float completedB = playerB->completedLaps + playerB->lapPercent;
            
            if((completedA > completedB  &&  rankA > rankB)
               || (completedA < completedB  &&  rankA < rankB)){
                playerA->rankPos = rankB;
                playerB->rankPos = rankA;
            }
        }
    }
    
    // update race's completed laps
    int highestLap = 0;
    for(auto player : players){
        int playerLap = player->completedLaps;
        if(playerLap > highestLap){
            highestLap = playerLap;
        }
    }
    
    numLaps = highestLap;
}



void Race::updatePowerUps(){
    // check collisions with bikes
    for(auto powerUp : powerups){
        if(powerUp->active){
            for(auto bike : bikes){
                if(powerUp->collides(bike)){
                    bike->powerbar.addTime(5); // add 5 secods to power bar
                    powerUp->active = false;
                    
                    lasttime = ofGetElapsedTimef();
                }
            }
        }
    }
    
    // TODO: proper logic to activate/deactivate powerups
    float idleTime = ofGetElapsedTimef() - lasttime;
    if(idleTime > 10){
        powerups[0]->active = true;
    }
}


void Race::updateTimer(){
    elapsedTime += ofGetElapsedTimeMillis() - prevTime;
    prevTime = ofGetElapsedTimeMillis();
}


string Race::getElapsedTimeString(){
    int millis = elapsedTime;
    int seconds = millis / 1000;
    int minutes = seconds / 60;
    int tens = (millis - seconds * 1000) / 10;
    string minutesTXT = ofToString(minutes, 2, '0');
    string secondsTXT = ofToString(seconds - minutes*60, 2, '0');
    string tensTXT = ofToString(tens, 2, '0');
    return minutesTXT + ":" + secondsTXT + ":" + tensTXT;
}


void Race::onParameterChange(ofAbstractParameter& param){
    string paramName = param.getName();
    float value = param.cast<float>().get();
    
    if(paramName == "acceleration"){
        for(auto bike : bikes){
            bike->acceleration = value;
        }
    }
    else if(paramName == "friction"){
        for(auto bike : bikes){
            bike->friction = value;
        }
    }
    else if(paramName == "max speed"){
        for(auto bike : bikes){
            bike->maxSpeed = value;
        }
    }
    else if(paramName == "rotation step"){
        for(auto bike : bikes){
            bike->rotationStep = value;
        }
    }
    else if(paramName == "scale"){
        for(auto bike : bikes){
            bike->setScale(value);
        }
    }
    // collisions
    else if(paramName == "front friction"){
        for(auto bike : bikes){
            bike->frontFriction = value;
        }
    }
    else if(paramName == "sides friction"){
        for(auto bike : bikes){
            bike->sidesFriction = value;
        }
    }
    else if(paramName == "sides rotation"){
        for(auto bike : bikes){
            bike->sidesRotation = value;
        }
    }
    else if(paramName == "bike hit friction"){
        for(auto bike : bikes){
            bike->bikeHitFriction = value;
        }
    }
    // power ups
    else if(paramName == "pu acceleration"){
        for(auto bike : bikes){
            bike->powerbar.acceleration = value;
        }
    }
    else if(paramName == "pu friction"){
        for(auto bike : bikes){
            bike->powerbar.friction = value;
        }
    }
    else if(paramName == "pu max speed"){
        for(auto bike : bikes){
            bike->powerbar.maxSpeed = value;
        }
    }
    else if(paramName == "pu rotation step"){
        for(auto bike : bikes){
            bike->powerbar.rotationStep = value;
        }
    }
}