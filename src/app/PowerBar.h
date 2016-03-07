//
//  PowerBar.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 01/03/2016.
//
//

#pragma once

#include "ofMain.h"

#define TOTAL_DURATION 5


class PowerBar {
    
public:
    
    float acceleration;
    float friction;
    float maxSpeed;
    float rotationStep;
    
    float totalDuration;
    
    
    PowerBar(){
        acceleration = 0.1;
        friction = 0.1;
        maxSpeed = 0.1;
        rotationStep = 0.1;
        
        reset();
    }
    
    
    void reset(){
        elapsedTime = 0;
        lastElapsedTime = 0;
        totalDuration = TOTAL_DURATION;
        percent = 1;
        
        bActive = false;
    }
    
    
    void update(){
        if(bActive){
            elapsedTime += ofGetElapsedTimef() - lastElapsedTime;
            lastElapsedTime = ofGetElapsedTimef();
            
            percent = 1 - (elapsedTime / totalDuration);
            
            if(percent <= 0){
                deactivate();
            }
        }
    }
    
    
    void activate(){
        if(percent > 0){
            bActive = true;
            lastElapsedTime = ofGetElapsedTimef();
        }
    }

    
    void deactivate(){
        bActive = false;
    }
    
    
    bool isActive(){ return bActive; }
    
    
    void addTime(float seconds){
        elapsedTime -= seconds;
        elapsedTime = elapsedTime < 0 ? 0 : elapsedTime;
        
        percent = 1 - (elapsedTime / totalDuration);
    }
    
    
    float getPercent(){
        return percent;
    }
    
    
private:
    
    bool bActive;
    
    float percent;
    
    float elapsedTime;
    float lastElapsedTime;
};
