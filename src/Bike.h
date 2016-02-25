//
//  Bike.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 23/02/2016.
//
//

#pragma once

#include "ofMain.h"


class Bike {
    
public:
    
    Bike(ofVec2f position = ofVec2f(0,0), float rotation = 0.f);
    
    void setPosition(float x, float y);
    void setRotation(float degrees);
    float getSpeed() { return speed; }
    ofVec2f getPosition() { return position; }
    ofVec2f getFrontPos() { return collisionPoints[2] + position; }
    ofVec2f getBackPos() { return collisionPoints[0] + position; }
    
    void checkColision(ofImage* map);
    
    void update();
    void drawDebug();
    
    bool bAccelerate, bTurnLeft, bTurnRight;
    
    ofParameterGroup parameters;
    ofParameter<float> acceleration;
    ofParameter<float> friction;
    ofParameter<float> maxSpeed;
    ofParameter<float> rotationStep;
    ofParameter<float> scale;
    
    ofParameterGroup parametersCollision;
    ofParameter<float> frontFriction;
    ofParameter<float> sidesFriction;
    ofParameter<float> sidesRotation;
    
private:
    
    ofVec2f position;
    float speed;
    float rotation;
    ofVec2f velocity;
    
    float length, width;
    
    void updateRotation(float newRotation);
    
    vector<ofVec2f> corners;
    vector<ofVec2f> collisionPoints;
    ofMatrix4x4 rotationMat;
    
    
    // collision flags
    vector<bool> collisionFlags;
    
    // scaling
    void onScaleChage(float& value);
};
