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


Bike::Bike(ofImage* img){
    image = img;
    
    position.set(0,0);
    rotation = 0;
    speed = 0;
    
    acceleration = 0.4;
    friction = 0.85;
    maxSpeed = 2.0;
    rotationStep = 0.17;
    
    frontFriction = 0.33;
    sidesFriction = 0.85;
    sidesRotation = 0.01;
    
    bikeHitFriction = 0.85;
    
    bAccelerate = false;
    bTurnLeft = false;
    bTurnRight = false;
    
    // testing
    stuckTimer = 0;
    stuckPrevTimer = 0;
    //checkpointPrevTime = 0;
    
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


void Bike::update(){
    if(bAccelerate){
        speed += (speed < maxSpeed) ? acceleration : 0;
    }
    
    if(bTurnRight){
        float newRotation = rotation - (rotationStep * (speed / maxSpeed));
        setRotation(newRotation);
    }
    
    if(bTurnLeft){
        float newRotation = rotation + (rotationStep * (speed / maxSpeed));
        setRotation(newRotation);
    }
    
    speed *= (speed < 0.003f) ? 0.0f : friction;
    
    direction.x = sin(rotation);
    direction.y = cos(rotation);
    
    velocity.set(direction * speed);
    
    position += velocity;
    
    // record position and rotation
//    if(!isStuck){
//        if(ofGetElapsedTimef() - checkpointPrevTime > 3){
//            checkpoint.rotation = rotation;
//            checkpoint.position = position;
//            
//            checkpointPrevTime = ofGetElapsedTimef();
//        }
//    }else{
//        checkpointPrevTime = ofGetElapsedTimef();
//    }
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
    
    //isStuck = stuckTimer > maxStuckTime;
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
                
                //
                //float pct = 1 - ABS(this->direction.dot(other->direction));
                //this->speed -= (bikeHitFriction * pct);
                //other->speed -= (bikeHitFriction * pct);
                
                this->speed *= bikeHitFriction;
                other->speed *= bikeHitFriction;
                
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
    
    ofSetColor(color);
    
    image->getTexture().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
    image->bind();
    mesh.draw();
    image->unbind();
    
    ofPopMatrix();
    
    
    
//    image->bind();
//    
//    ofVec2f p1 = localToGlobal(corners[0]);
//    ofVec2f p2 = localToGlobal(corners[1]);
//    ofVec2f p3 = localToGlobal(corners[2]);
//    ofVec2f p4 = localToGlobal(corners[3]);
//    
//    ofBeginShape();
//    ofVertex(p1.x, p1.y);
//    ofVertex(p2.x, p2.y);
//    ofVertex(p3.x, p3.y);
//    ofVertex(p4.x, p4.y);
//    ofEndShape();
//    
//    image->unbind();
    
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