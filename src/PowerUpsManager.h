//
//  PowerUpsManager.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 04/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "PowerUp.h"
#include "assets.h"


#define POWER_SECONDS 5.f           // seconds that powerups add to the power bar
#define SHOW_INTERVAL 5.f           // interval to show a new power up
#define MAX_POWERUPS 5              // max number of powerups on screen
#define SAFE_DIST_SQUARED 170*170   // powerup won't show if it a bike is closer than this


class PowerUpsManager {

    
public:
    
    Assets* assets;
    
    ofParameterGroup parameters;
    ofParameter<float> powerSeconds;
    ofParameter<float> interval;
    ofParameter<float> maxNumPowerups;
    ofParameter<float> safeDist;
    
    
    PowerUpsManager(){
        powerups.push_back( new PowerUp(1260, 137, 20) );
        powerups.push_back( new PowerUp(1500, 217, 20) );
        powerups.push_back( new PowerUp(1658, 146, 20) );
        powerups.push_back( new PowerUp(1582, 398, 20) );
        powerups.push_back( new PowerUp(1403, 467, 20) );
        powerups.push_back( new PowerUp(1205, 461, 20) );
        powerups.push_back( new PowerUp(1107, 847, 20) );
        powerups.push_back( new PowerUp(887, 967, 20) );
        powerups.push_back( new PowerUp(634, 914, 20) );
        powerups.push_back( new PowerUp(338, 858, 20) );
        powerups.push_back( new PowerUp(252, 658, 20) );
        powerups.push_back( new PowerUp(97, 527, 20) );
        powerups.push_back( new PowerUp(161, 341, 20) );
        powerups.push_back( new PowerUp(525, 353, 20) );
        powerups.push_back( new PowerUp(765, 613, 20) );
        powerups.push_back( new PowerUp(725, 341, 20) );
        powerups.push_back( new PowerUp(937, 221, 20) );
        powerups.push_back( new PowerUp(1107, 641, 20) );
        
        parameters.setName("powerups manager");
        parameters.add( powerSeconds.set("added seconds", POWER_SECONDS, 1, 10));
        parameters.add( interval.set("show interval", SHOW_INTERVAL, 1, 15));
        parameters.add( maxNumPowerups.set("max powerups", MAX_POWERUPS, 1, 10));
        
        assets = Assets::getInstance();
        
        reset();
    }
    
    
    void reset(){
        for(auto powerup : powerups){
            powerup->active = false;
        }
        activeCount = 0;
        lasttime = ofGetElapsedTimef();
    }
    
    
    void update(vector<Bike*>& bikes){
        // check collisions with bikes
        for(auto powerUp : powerups){
            if(powerUp->active){
                for(auto bike : bikes){
                    if(powerUp->collides(bike)){
                        bike->powerbar.addTime(powerSeconds); // add 5 secods to power bar
                        powerUp->active = false;
                        activeCount--;
                    }
                }
            }
        }
        
        // activate new powerups
        float idleTime = ofGetElapsedTimef() - lasttime;
        if(idleTime > interval){
            if(activeCount < maxNumPowerups  &&  activeCount < powerups.size()){
                showNewPowerUp(bikes);
            }
            lasttime = ofGetElapsedTimef();
        }
    }
    
    
    void draw(){
        for(auto powerUp : powerups){
            if(powerUp->active){
                powerUp->draw();
            }
        }
    }
    
    
private:
    
    
    vector<PowerUp*> powerups;
    int activeCount;
    float lasttime;
    
    
    void showNewPowerUp(vector<Bike*>& bikes){
        PowerUp* powerup;
        
        // pick a random power up that is not active
        bool isValid = false;
        while(!isValid){
            int randomIndex = ofRandom(powerups.size());
            
            powerup = powerups[randomIndex];
            
            isValid = (powerup->active) ? false : true;
        }
        
        // check that the powerup is not too close to any of the bikes
        isValid = isValidDistance(powerup, bikes);
        
        // activate the powerup
        if(isValid){
//            cout << "new powerup" << endl;
            powerup->setImage(assets->getRandomPowerupImage());
            powerup->active = true;
            activeCount++;
        }else{
//            cout << "[add powerup aborted]: too close to bike" << endl;
            // NOTE:
            // At this point, we won't show a powerup on this call.
            // We need to wait 5s until showNewPowerUp() is called again...
            // ...or we could keep calling showNewPowerUp() until we get a valid powerup
            // but that would block the thread for too long.
        }
    }
    
    
    bool isValidDistance(PowerUp* power, vector<Bike*>& bikes){
        for(auto bike : bikes){        
            ofVec2f bikeDir( bike->getDirection() );
            ofVec2f bikePos( bike->getPosition() );
            ofVec2f powerPos( power->collisionPoint->position );
            ofVec2f bikeToPower( powerPos - bikePos );
            float distanceSq = bikeToPower.lengthSquared();
            float sphereRadiusSq = bike->getScale() * bike->getScale();
            
            bool insideBoundingSphere = distanceSq < sphereRadiusSq;
            if(insideBoundingSphere){
                return false;
            }
            
            bool isAhead = bikeDir.dot(bikeToPower) > 0;
            if(!isAhead){
                return true;
            }
            
            bool isTooClose = distanceSq < SAFE_DIST_SQUARED;
            if(isTooClose){
                return false;
            }
            
            return true;
        }
    }
};
