//
//  Race.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 24/02/2016.
//
//

#include "Race.h"


Race::Race()
: player("player 1", bike) // init the players
{
    bPaused = false;
    bStarted = false;
}


void Race::setup(){
    collisionMap.load("map.png");
    progressMap.load("progess-map.png");
    
    // position bikes on the starting position
    bike.setPosition(ofGetWidth()/2, 660);
    bike.setRotation(90);
}


void Race::start() {
    bStarted = true;
    elapsedTime = 0;
    prevTime = ofGetElapsedTimeMillis();
}


void Race::update(){
    if(bStarted){
        bike.update();
        bike.checkColision(&collisionMap);
        
        updateRanking();
        
        // update timer
        elapsedTime += ofGetElapsedTimeMillis() - prevTime;
        prevTime = ofGetElapsedTimeMillis();
    }
}


void Race::draw() {
    collisionMap.draw(0,0);
    bike.drawDebug();
}


void Race::drawInfo(){
    ofDrawBitmapStringHighlight(getElapsedTimeString(), 20, 708);
    ofDrawBitmapStringHighlight("LAP: " + ofToString(player.completedLaps), 20, 728);
    ofDrawBitmapStringHighlight("COMPLETED: " + ofToString(player.lapPercent*100, 2) + "%", 20, 748);
}



void Race::updateRanking(){
    const ofVec2f p = player.bike.getPosition();
    ofColor color = progressMap.getPixels().getColor(p.x, p.y);
    float percent = color.r / 255.f;
    
    // check if line crossed
    if (player.lapPercent == 1.0 && percent == 0.0) {
        player.completedLaps += 1;
    }
    
    player.lapPercent = percent;	
}




string Race::getElapsedTimeString() {
    int millis = elapsedTime;
    int seconds = millis / 1000;
    int minutes = seconds / 60;
    int tens = (millis - seconds * 1000) / 10;
    string minutesTXT = ofToString(minutes, 2, '0');
    string secondsTXT = ofToString(seconds, 2, '0');
    string tensTXT = ofToString(tens, 2, '0');
    
    return minutesTXT + ":" + secondsTXT + ":" + tensTXT;
}