//
//  Trail.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 07/03/2016.
//
//

#pragma once

#include "ofMain.h"


//class Node {
//public:
//    ofVec2f position;
//    Node(ofVec2f pos)
//    : position(pos)
//    {}
//};



class Trail {

public:
    
    Trail(){
        numNodes = 40;
    }
    
    void update(ofVec2f position){
        if(nodes.size() < numNodes){
            nodes.push_back(position);
        }else{
            // remove first
            nodes.erase(nodes.begin());
            nodes.push_back(position);
        }
    }
    
    void draw(){
        if(nodes.size() < 2) return;
        
        ofPushStyle();
        
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        for(int i = 0; i < nodes.size(); i++){
            float opacity = float(i)/float(numNodes);
        
            ofSetColor(color, opacity*opacity*opacity*190);
            
            ofDrawCircle(nodes[i], 10);
        }
        ofPopStyle();
    }
    
    
    int numNodes;
    vector<ofVec2f> nodes;
    ofColor color;
    
};