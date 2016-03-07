//
//  Bike.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 23/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "PowerBar.h"
#include "Trail.h"


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


class Bike {
    
public:
    
    ~Bike();
    Bike(ofImage* image, ofImage* glow, ofSoundPlayer* sound, ofColor trailColor);
    
    void reset(ofVec2f pos, float rot);
    
    void setPosition(float x, float y);
    void setRotation(float radians);
    void setScale(float scale);
    
    float getSpeed() { return speed; }
    ofVec2f getPosition() { return position; }
    ofVec2f getFrontPos() { return collisionPoints[2].position + position; }
    ofVec2f getBackPos() { return collisionPoints[0].position + position; }
    ofVec2f getVelocity() { return velocity; }
    ofVec2f getDirection() { return direction; }
    float getScale() { return scale; }
    vector<CollisionPoint> & getCollisionCircles() { return collisionCircles; }
    
    void doNAACollision(ofImage* map);
    void doBikeCollision(Bike* bike);
    void update();
    void draw(ofColor color = ofColor(255));
    void drawDebug(ofColor color = ofColor(255));
    
    ofVec2f localToGlobal(ofVec2f& localPoint);
    
    // controls
    bool bAccelerate, bTurnLeft, bTurnRight, bPullover;
    
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
    
    // power ups
    bool bUsingPowerUp;
    
    // illegal actions
    float stuckTimer;
    float stuckPrevTimer;
    float getTimeStuck();
    
    // power ups
    PowerBar powerbar;
    void activatePower(){ powerbar.activate(); }
    void deactivatePower(){ powerbar.deactivate(); }
    
    ofSoundPlayer* motorSound;
    
private:
    
    ofVec2f position; // origin
    float scale;
    float rotation;
    
    float speed;
    ofVec2f direction;
    ofVec2f velocity;
    
    float length, width;
    ofImage* image;
    ofImage* glow;
    ofVboMesh mesh;
    
    // rect corners
    vector<ofVec2f> corners;
    // non accessible areas (NAA) collision
    vector<CollisionPoint> collisionPoints;
    // bike-bike collision
    vector<CollisionPoint> collisionCircles;
    
    Trail trail;
    ofColor trailColor;
};
