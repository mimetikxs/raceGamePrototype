//
//  Bike.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 23/02/2016.
//
//

#include "Bike.h"

//#define TO_RADIANS 


Bike::Bike(ofVec2f _position, float _rotation){
    position.set(_position);
    rotation = _rotation;
    speed = 0;
    
    parameters.add( acceleration.set("acceleration", 0.4, 0.0, 2.0) );
    parameters.add( friction.set("friction", 0.85, 0.5, 0.999) );
    parameters.add( maxSpeed.set("max speed", 2.0, 1.0, 50.0) );
    parameters.add( rotationStep.set("rotation step", 0.17, 0.0001, 1.0) );
    parameters.add( scale.set("scale", 1.0, 0.1, 2.0) );
    scale.addListener(this, &Bike::onScaleChage);
    
    parametersCollision.add( frontFriction.set("front friction", 0.33, 0.99, 0.1) );
    parametersCollision.add( sidesFriction.set("sides friction", 0.85, 0.99, 0.1) );
    parametersCollision.add( sidesRotation.set("sides rotation", 0.01, 0.001, 0.05) );
    
    bAccelerate = false;
    bTurnLeft = false;
    bTurnRight = false;
    
    // define the bounding box in the bike's local coords
    // TODO: width and length are defined after loading the sprite
    length = 70 * scale;
    width = 30 * scale;
    float halfLength = length/2;
    float halfWidth = width/2;
    corners.push_back( ofVec2f(-halfWidth, -halfLength) );  // back right
    corners.push_back( ofVec2f(halfWidth, -halfLength) );   // back left
    corners.push_back( ofVec2f(halfWidth, halfLength) );    // front left
    corners.push_back( ofVec2f(-halfWidth, halfLength) );   // front right
    
    // collision points
    float offset = 20; // so the side points are not at the center
    collisionPoints.push_back( ofVec2f(0, -halfLength) );  // back
    collisionPoints.push_back( ofVec2f(halfWidth, offset*scale) );    // left
    collisionPoints.push_back( ofVec2f(0, halfLength) );   // front
    collisionPoints.push_back( ofVec2f(-halfWidth, offset*scale) );   // right
    
    collisionFlags.push_back(false);
    collisionFlags.push_back(false);
    collisionFlags.push_back(false);
    collisionFlags.push_back(false);
}


void Bike::setPosition(float x, float y){
    position.set(x, y);
}


void Bike::setRotation(float newRotation){
    float radians = newRotation * PI/180;
    updateRotation(radians);
}


void Bike::update(){
    if(bAccelerate){
        speed += (speed < maxSpeed) ? acceleration.get() : 0;
    }
    
    if(bTurnRight){
        float newRotation = rotation - (rotationStep * (speed / maxSpeed));
        updateRotation(newRotation);
    }
    
    if(bTurnLeft){
        float newRotation = rotation + (rotationStep * (speed / maxSpeed));
        updateRotation(newRotation);
    }
    
    speed *= (speed < 0.03f) ? 0.0f : friction.get();
    
    velocity.x = sin(rotation) * speed;
    velocity.y = cos(rotation) * speed;
    
    position += velocity;
}


void Bike::updateRotation(float newRotation){
    float prevRotation = rotation;
    
    rotation = newRotation;
    
    float diff = prevRotation - newRotation;
    
    for(auto & corner : corners){
        corner.rotateRad(diff);
    }
    
    for(auto & point : collisionPoints){
        point.rotateRad(diff);
    }
}


void Bike::checkColision(ofImage *map){
    for(int i=0; i<collisionPoints.size(); i++){
        const ofVec2f& p = position + collisionPoints[i];
        ofColor color = map->getPixels().getColor(p.x, p.y);
        collisionFlags[i] = (color.r == 0) ? true : false;
    }
    
    if(collisionFlags[0]){
        //cout << "back" << endl;
        speed *= frontFriction;
    }
    
    if(collisionFlags[1]){
        //cout << "left" << endl;
        updateRotation( rotation - sidesRotation );
        speed *= sidesFriction;
    }
    
    if(collisionFlags[2]){
        //cout << "front" << endl;
        speed *= frontFriction;
    }
    
    if(collisionFlags[3]){
        //cout << "right" << endl;
        updateRotation( rotation + sidesRotation );
        speed *= sidesFriction;
    }
}


void Bike::drawDebug(){
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(position);
    
    // box
    ofNoFill();
    ofSetColor(255);
    
    ofBeginShape();
    ofVertex(corners[0].x, corners[0].y);
    ofVertex(corners[1].x, corners[1].y);
    ofVertex(corners[2].x, corners[2].y);
    ofVertex(corners[3].x, corners[3].y);
    ofVertex(corners[0].x, corners[0].y);
    ofEndShape();
    
    ofFill();
    ofSetColor(255);
    
    // origin
    ofDrawCircle(0,0, 3);
    
    ofSetColor(255,0,0);
    
    // collision points
    for(int i = 0; i < collisionPoints.size(); i++){
        if(collisionFlags[i] == true){
            ofFill();
            ofDrawCircle(collisionPoints[i], 5);
        }else{
            ofNoFill();
            ofDrawCircle(collisionPoints[i], 3);
        }
    }
    
    ofFill();
    ofSetColor(0,255,255);
    
    // velocity vector
    ofDrawLine(0,0, velocity.x * 10,velocity.y * 10);
    
    ofPopStyle();
    ofPopMatrix();
}


void Bike::onScaleChage(float& value){
    length = 70 * value;
    width = 30 * value;
    float halfLength = length/2;
    float halfWidth = width/2;
    
    corners[0].set(-halfWidth, -halfLength);  // back right
    corners[1].set(halfWidth, -halfLength);   // back left
    corners[2].set(halfWidth, halfLength);    // front left
    corners[3].set(-halfWidth, halfLength);   // front right
    
    // collision points
    float offset = 20;
    collisionPoints[0].set(0, -halfLength);  // back
    collisionPoints[1].set(halfWidth, offset*value);    // left
    collisionPoints[2].set(0, halfLength);   // front
    collisionPoints[3].set(-halfWidth, offset*value);   // right
    
    
    for(auto & corner : corners){
        corner.rotateRad(-rotation);
    }
    for(auto & point : collisionPoints){
        point.rotateRad(-rotation);
    }
}