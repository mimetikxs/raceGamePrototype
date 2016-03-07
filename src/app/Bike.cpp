//
//  Bike.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 23/02/2016.
//
//

#include "Bike.h"

#define TO_RADIANS PI/180.f
#define TO_DEGREES 180.f/PI


Bike::~Bike(){
    motorSound->setPaused(true);
}


Bike::Bike(ofImage* img, ofImage* _glow, ofSoundPlayer* sound){
    image = img;
    glow = _glow;
    motorSound = sound;
    
    acceleration = 0.4;
    friction = 0.85;
    maxSpeed = 2.0;
    rotationStep = 0.17;
    
    frontFriction = 0.33;
    sidesFriction = 0.85;
    sidesRotation = 0.01;
    
    bikeHitFriction = 0.85;
    
    // init geometry (all coordinates are normalized [0..1]):
    scale = 1.0;
    length = 1.0f;
    width = image->getHeight() / image->getWidth(); //0.42f;
    
    float halfLength = length/2;
    float halfWidth = width/2;
    
    corners.push_back(ofVec2f(-halfWidth, -halfLength));  // back right
    corners.push_back(ofVec2f(halfWidth, -halfLength));   // back left
    corners.push_back(ofVec2f(halfWidth, halfLength));    // front left
    corners.push_back(ofVec2f(-halfWidth, halfLength));   // front right
    
    mesh.addVertex(ofVec3f(-halfWidth-0.05, -halfLength, 0));
    mesh.addVertex(ofVec3f(halfWidth+0.05, -halfLength, 0));
    mesh.addVertex(ofVec3f(halfWidth+0.05, halfLength+0.1, 0));
    mesh.addVertex(ofVec3f(-halfWidth-0.05, halfLength+0.1, 0));
    mesh.addTexCoord(ofVec2f(image->getWidth(),0));
    mesh.addTexCoord(ofVec2f(image->getWidth(),image->getHeight()));
    mesh.addTexCoord(ofVec2f(0,image->getHeight()));
    mesh.addTexCoord(ofVec2f(0,0));
    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(0, 2, 3);
    
    float offset = 0.2;
    collisionPoints.push_back(CollisionPoint(0, -halfLength));       // back
    collisionPoints.push_back(CollisionPoint(halfWidth, offset));    // left
    collisionPoints.push_back(CollisionPoint(0, halfLength));        // front
    collisionPoints.push_back(CollisionPoint(-halfWidth, offset));   // right
    
    collisionCircles.push_back(CollisionPoint(0, -halfLength + halfWidth, halfWidth)); // back
    collisionCircles.push_back(CollisionPoint(0, 0, halfWidth));                       // center
    collisionCircles.push_back(CollisionPoint(0, halfLength - halfWidth, halfWidth));  // front
}


void Bike::reset(ofVec2f pos, float rot){
    position = pos;
    rotation = rot;
    speed = 0;
    
    bAccelerate = false;
    bTurnLeft = false;
    bTurnRight = false;
    bPullover = false;
    
    stuckTimer = 0;
    stuckPrevTimer = 0;
    
    powerbar.reset();
    
    motorSound->setSpeed(0.5);
    motorSound->setVolume(0.2);
    motorSound->setPaused(false);
    if(!motorSound->isPlaying()) motorSound->play();
}


void Bike::update(){
    float _acceleration;
    float _maxSpeed;
    float _rotationStep;
    
    if(powerbar.isActive()){
        // power up values
        _acceleration = powerbar.acceleration;
        _maxSpeed = powerbar.maxSpeed;
        _rotationStep = powerbar.rotationStep;
    }else{
        // normal values
        _acceleration = acceleration;
        _maxSpeed = maxSpeed;
        _rotationStep = rotationStep;
    }
    
    
    
    if(bAccelerate || powerbar.isActive()){
        speed += (speed < _maxSpeed) ? _acceleration : 0;
    }
    
    if(bTurnRight){
        float newRotation = rotation - _rotationStep;
        setRotation(newRotation);
    }
    
    if(bTurnLeft){
        float newRotation = rotation + _rotationStep;
        setRotation(newRotation);
    }
    
    if(bPullover || speed > maxSpeed){
        speed *= (speed < 0.003f) ? 0.0f : friction;
    }
    
    motorSound->setSpeed(ofMap(speed/maxSpeed, 0, 1, 0.5, 1.0));
    motorSound->setVolume(ofMap(speed/maxSpeed, 0, 1, 0.2, 0.6));
    
    direction.x = sin(rotation);
    direction.y = cos(rotation);
    
    velocity.set(direction * speed);
    
    position += velocity;
    
    powerbar.update();
}


void Bike::doNAACollision(ofImage *map){
    for(int i=0; i<collisionPoints.size(); i++){
        //const ofVec2f& p = position + collisionPoints[i].position;
        const ofVec2f& p = localToGlobal( collisionPoints[i].position );
        ofColor color = map->getPixels().getColor(p.x, p.y);
        collisionPoints[i].isColliding = (color.r == 0) ? true : false;
    }
    
//    if(collisionPoints[0].isColliding){
//        //cout << "back" << endl;
//        speed *= frontFriction;
//    }
    
    if(collisionPoints[1].isColliding){
        //cout << "left" << endl;
        setRotation( rotation - sidesRotation );
        speed *= sidesFriction;
    }
    
    if(collisionPoints[2].isColliding){
        //cout << "front" << endl;
        speed *= frontFriction;
    }
    
    if(collisionPoints[3].isColliding){
        //cout << "right" << endl;
        setRotation( rotation + sidesRotation );
        speed *= sidesFriction;
    }
}


float Bike::getTimeStuck(){
    if(collisionPoints[1].isColliding
       && collisionPoints[2].isColliding
       && collisionPoints[3].isColliding)
    {
        stuckTimer += ofGetElapsedTimef() - stuckPrevTimer;
    }else{
        stuckTimer = 0;
    }
    
    stuckPrevTimer = ofGetElapsedTimef();
    
    return stuckTimer;
}


void Bike::doBikeCollision(Bike* other){
    
    for(int i = 0; i < collisionCircles.size(); i++){
        CollisionPoint& circleA = collisionCircles[i];
        ofVec2f posA = localToGlobal(circleA.position);
        float radiusA = circleA.radius * scale;
        
        for(int j = 0; j < other->collisionCircles.size(); j++){
            CollisionPoint& circleB = other->collisionCircles[j];
            ofVec2f posB = other->localToGlobal(circleB.position);
            float radiusB = circleB.radius * scale;
            
            float collisionDistance = radiusA + radiusB;
            ofVec2f deltaBA(posA - posB);
            float distance = deltaBA.length();
            bool isColliding = distance < collisionDistance;
            
            if (isColliding) {
                circleA.isColliding = true;
                circleB.isColliding = true;
                
                // collision response
                float overlap = collisionDistance - distance;
                ofVec2f correctedBA = deltaBA.scale(overlap/2);
                
                this->position += correctedBA;
                other->position -= correctedBA;
                
                // uncomment this to add a speed penalty
//                this->speed *= bikeHitFriction;
//                other->speed *= bikeHitFriction;
                
                //return;
            }
        }
    }
}


void Bike::setPosition(float x, float y){
    position.set(x, y);
}


void Bike::setRotation(float newRotation){
    rotation = newRotation;
}


void Bike::setScale(float value){
    scale = value;
}


ofVec2f Bike::localToGlobal(ofVec2f& localPoint){
    ofVec2f global(localPoint);
    global *= scale;
    global.rotateRad(-rotation);
    global += position;
    return global;
}


void Bike::draw(ofColor color){
    
    ofPushMatrix();
    ofTranslate(position);
    ofRotate(-rotation * TO_DEGREES);
    ofScale(scale, scale);
    
    if(powerbar.isActive()){
        glow->getTexture().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
        glow->bind();
        mesh.draw();
        glow->unbind();
    }
    
    image->getTexture().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
    image->bind();
    mesh.draw();
    image->unbind();
    
    ofPopMatrix();
    
}


void Bike::drawDebug(ofColor color){
    ofPushStyle();
    
    // box
    ofFill();
    ofSetColor(color, 160);
    ofEnableAlphaBlending();
    
    ofVec2f p1 = localToGlobal(corners[0]);
    ofVec2f p2 = localToGlobal(corners[1]);
    ofVec2f p3 = localToGlobal(corners[2]);
    ofVec2f p4 = localToGlobal(corners[3]);
    
    ofBeginShape();
    ofVertex(p1.x, p1.y);
    ofVertex(p2.x, p2.y);
    ofVertex(p3.x, p3.y);
    ofVertex(p4.x, p4.y);
    ofEndShape();
    
    ofDisableAlphaBlending();
    
    ofFill();
    ofSetColor(255);
    
    // origin
    ofDrawCircle(0,0, 2);
    
    ofNoFill();
    ofSetColor(0,255,0);
    
    // collision circles
    for(auto & c : collisionCircles){
        ofVec2f pos = localToGlobal(c.position);
        if(c.isColliding){
            ofFill();
        }else{
            ofNoFill();
        }
        ofDrawCircle(pos, c.radius*scale);
    }
    
    ofSetColor(255,0,0);
    
    // collision points
    for(auto & p : collisionPoints){
        ofVec2f pos = localToGlobal(p.position);
        if(p.isColliding){
            ofFill();
            ofDrawCircle(pos, 5);
        }else{
            ofNoFill();
            ofDrawCircle(pos, 3);
        }
    }
    
    ofNoFill();
    ofSetColor(0,255,255);
    
    // velocity vector
    ofDrawLine(position.x,position.y, position.x + velocity.x * scale * 0.3, position.y + velocity.y * scale * 0.3);
    
    ofPopStyle();
}