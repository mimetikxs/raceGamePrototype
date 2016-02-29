//
//  Race.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//

#include "assets.h"
#include "Race.h"


Race::Race()
: finishingLine(398, 707, 398, 583)
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
    
    ofAddListener(parametersDriving.parameterChangedE(), this, &Race::onParameterChange);
    ofAddListener(parametersCollision.parameterChangedE(), this, &Race::onParameterChange);

    bPaused = false;
    bStarted = false;

    collisionMap = Assets::getInstance()->getMap();
    progressMap = Assets::getInstance()->getCollisionMap();
    bikeImage = Assets::getInstance()->getBikeImage(0);
}


void Race::setup(){
    
    // init starting marks
    // TODO: load from json
    startingMarks.push_back(StartingMark(ofGetWidth()/2 + 20, 620, PI/2));
    startingMarks.push_back(StartingMark(ofGetWidth()/2, 665, PI/2));
//    startingMarks.push_back(StartingMark(ofGetWidth()/2, 660, PI/2));
//    startingMarks.push_back(StartingMark(ofGetWidth()/2, 660, PI/2));
    
    // init bikes
    // TODO: load bike sprites from json
    bikes.push_back(new Bike(&bikeImage));
    bikes.push_back(new Bike(&bikeImage));
//    bikes.push_back(new Bike());
//    bikes.push_back(new Bike());
    
    // init players
    // TODO: get constructor values from json
    players.push_back(new Player(Assets::getInstance()->getPlayerName(0), bikes[0], ofColor::mediumOrchid, 0));
    players.push_back(new Player(Assets::getInstance()->getPlayerName(1), bikes[1], ofColor::mediumSeaGreen, 1));
//    players.push_back(new Player("player 3", bikes[2], ofColor::mediumTurquoise, 2));
//    players.push_back(Player("player 4", bikes[3], ofColor::sandyBrown, 3));
    
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
    prevTime = ofGetElapsedTimeMillis();
}


void Race::update(){
    if(bStarted){
        updateBikes();
        
        checkStuck();
        
        updateTimer();
        
        // this can be updated at a diferent rate
        updateRanking();
    }
}


void Race::draw() {
    collisionMap.draw(0,0);
    
    finishingLine.draw();
    
    if(bDrawDebug){
        for(auto & player : players){
            player->bike->drawDebug(player->color);
        }
    }else{
        for(auto & player : players){
            player->bike->draw(player->color);
        }
    }
}


void Race::drawInfo(){
    // timer
    ofDrawBitmapStringHighlight(getElapsedTimeString(), 20, 678);
    
    // players info
    for(auto player : players){
        string name = player->name;
        string completedLaps = "LAP: " + ofToString(player->completedLaps);
        string completedPct  = ofToString(player->lapPercent*100, 2) + "%";
        float x = 20 + 120 * player->rankPos;
        ofDrawBitmapStringHighlight(name, x, 708, player->color);
        ofDrawBitmapStringHighlight(completedLaps, x, 728, player->color);
        ofDrawBitmapStringHighlight(completedPct, x, 748, player->color);
    }
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
}