//
//  PowerUp.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 01/03/2016.
//
//

#pragma once

#include "ofMain.h"

class PowerUp {
    
public:
    
    ofImage* image;
    CollisionPoint* collisionPoint;
    
    bool active;
    
//    PowerUp(float x, float y, ofImage* img) {
//        float radius = img->getWidth();
//        collisionPoint = new CollisionPoint(x, y, )
//    }
    PowerUp(float x, float y, float radius) {
        collisionPoint = new CollisionPoint(x, y, radius);
        active = false;
    }
    
    void drawDebug() {
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
