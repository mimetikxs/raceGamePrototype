//
//  PowerUp.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 01/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Bike.h"
#include "assets.h"


class PowerUp {
    
public:
    
    vector<ofImage*> image;
    CollisionPoint* collisionPoint;
    bool active;
    
    
    PowerUp(float x, float y, float radius) {
        collisionPoint = new CollisionPoint(x, y, radius);
        active = false;
    }
    
    
    void setImage(vector<ofImage*> img){
        image = img;
    }
    
    
    void draw(){
        float halfW = image[0]->getWidth()/2;
        float halfH = image[0]->getHeight()/2;
        ofVec2f p = collisionPoint->position;
        
        ofPushStyle();
        ofSetColor(255, ofMap(sin(ofGetElapsedTimef()*6), -1, 1, 0, 255));
        image[1]->draw(p.x-halfW, p.y-halfH); //glow
        ofPopStyle();
        
        image[0]->draw(p.x-halfW, p.y-halfH);
    }
    
    
    void drawDebug(){
        ofPushStyle();
        if(collisionPoint->isColliding){
            ofNoFill();
            ofSetColor(ofColor::red);
        }else{
            ofSetColor(ofColor::red);
        }
        
        ofVec2f p = collisionPoint->position;
        float r = collisionPoint->radius;
        ofDrawCircle(p.x, p.y, r);
        ofPopStyle();
    }
    
    
    bool collides(Bike* bike){
        ofVec2f posA = collisionPoint->position;
        float radiusA = collisionPoint->radius;
        
        vector<CollisionPoint>& bikeCollisionPoints = bike->getCollisionCircles();
        for(int j = 0; j < bikeCollisionPoints.size(); j++){
            CollisionPoint& circleB = bikeCollisionPoints[j];
            ofVec2f posB = bike->localToGlobal(circleB.position);
            float radiusB = circleB.radius * bike->getScale();
            
            float collisionDistance = radiusA + radiusB;
            ofVec2f deltaBA(posA - posB);
            float distance = deltaBA.length();
            bool isColliding = distance < collisionDistance;
            
            isColliding = isColliding;
            
            if(isColliding){
                return true;
            }
        }
        return false;
    }
    
};
