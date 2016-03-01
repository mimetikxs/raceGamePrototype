//
//  Bike.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 23/02/2016.
//
//

#pragma once

#include "ofMain.h"


class CollisionPoint {
public:
    bool isColliding;
    ofVec2f position;
    float radius;
    // TODO
    // string label = front, back, left, etc...
    CollisionPoint(float x=0, float y=0, float r=0){
        position.set(x, y);
        isColliding = false;
        radius = r;
    }
};


//class Checkpoint{
//public:
//    ofVec2f position;
//    float rotation;
//    Checkpoint(){
//        rotation = 0;
//    }
//};


class Bike {
    
public:
    
    Bike(ofImage* image);
    
    void setPosition(float x, float y);
    void setRotation(float radians);
    void setScale(float scale);
    
    float getSpeed() { return speed; }
    ofVec2f getPosition() { return position; }
    ofVec2f getFrontPos() { return collisionPoints[2].position + position; }
    ofVec2f getBackPos() { return collisionPoints[0].position + position; }
    ofVec2f getVelocity() { return velocity; }
    ofVec2f getDirection() { return direction; }
    vector<CollisionPoint> & getCollisionCircles() { return collisionCircles; }
    
    void doNAACollision(ofImage* map);
    void doBikeCollision(Bike* bike);
    void update();
    void draw(ofColor color = ofColor(255));
    void drawDebug(ofColor color = ofColor(255));
    
    ofVec2f localToGlobal(ofVec2f& localPoint);
    
    // controls
    bool bAccelerate, bTurnLeft, bTurnRight;
    
    // driving physics
    float acceleration;
    float friction;
    float maxSpeed;
    float rotationStep;
    
    // NAA collision response
    float frontFriction;
    float sidesFriction;
    float sidesRotation;
    
    // bike-bike collision response
    float bikeHitFriction;
    
    // testing //////////////////////////////
    
    // illegal actions
    float stuckTimer;
    float stuckPrevTimer;
    float getTimeStuck();
    
    //Checkpoint checkpoint;
    //float checkpointPrevTime;
    
    //bool isGoingBackwads;
    
    // end testing //////////////////////////
    
private:
    
    ofVec2f position; // origin
    float scale;
    float rotation;
    
    float speed;
    ofVec2f direction;
    ofVec2f velocity;
    
    float length, width;
    ofImage* image;
    
    // rect corners
    vector<ofVec2f> corners;
    // non accessible areas (NAA) collision
    vector<CollisionPoint> collisionPoints;
    // bike-bike collision
    vector<CollisionPoint> collisionCircles;
    
    ofVboMesh mesh;
};
