//
//  LineSegment.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 26/02/2016.
//
//

#include "LineSegment.h"

// aux functions:

ofVec2f getRightNormal(ofVec2f v) {
    ofVec2f leftNormal;
    leftNormal.x = -v.y;
    leftNormal.y = v.x;
    return leftNormal;
}


ofVec2f getLeftNormal(ofVec2f v) {
    ofVec2f leftNormal;
    leftNormal.x = v.y;
    leftNormal.y = -v.x;
    return leftNormal;
}


// -----


LineSegment::LineSegment(float ax, float ay, float bx, float by){
    a.set(ax, ay);
    b.set(bx, by);
    delta.set(b - a);
}


void LineSegment::draw() {
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofSetLineWidth(2);
    ofDrawLine(a.x, a.y, b.x, b.y);
    ofPopStyle();
}


bool LineSegment::intersects(ofVec2f position, ofVec2f velocity){
    ofVec2f point( getIntersection(position, velocity) );
    ofVec2f v1( point - a );
    ofVec2f v2( point - b );
    float segmentLength = delta.length();
    float v1Length = v1.length();
    float v2Length = v2.length();
    return !(v1Length > segmentLength || v2Length > segmentLength);
}


ofVec2f LineSegment::getIntersection(ofVec2f position, ofVec2f velocity) {
    ofVec2f v1( velocity );     // motion vector
    ofVec2f v2( delta );        // colision line
    ofVec2f v3( a - position ); // aux vector
    
    ofVec2f v1_ln = getLeftNormal(v1);
    ofVec2f v3_ln = getLeftNormal(v3);
    
    float perpProduct1 = v1_ln.dot( v2.getNormalized() );
    float perpProduct2 = v3_ln.dot( v2.getNormalized() );
    float t = perpProduct2 / perpProduct1;
    
    ofVec2f intersection( position + velocity * t );
    
    cout << intersection << endl;
    
    return intersection;
}


float LineSegment::getDistance(ofVec2f point){
    ofVec2f v2( delta );        // colision line
    ofVec2f v3( a - point );    // aux vector
    
    ofVec2f v2_ln = getRightNormal(v2);
    
    float distance = v3.dot(v2_ln.normalize()); // projection of v3 into v2_ln
    
    return distance;
}
