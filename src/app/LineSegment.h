//
//  LineSegment.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 26/02/2016.
//
//
#pragma once

#include "ofMain.h"

// line segment from point a to point b

class LineSegment{
    
public:
    
    LineSegment(float ax, float ay, float bx, float by);
    
    ofVec2f a; // start point
    ofVec2f b; // end point
    
    ofVec2f delta; // b - a
    
//    ofVec2f ln; // left normal
//    ofVec2f rn; // right normal
    
    void draw();
    
    bool intersects(ofVec2f position, ofVec2f velocity);
    ofVec2f getIntersection(ofVec2f position, ofVec2f velocity);
    float getDistance(ofVec2f point);
};
