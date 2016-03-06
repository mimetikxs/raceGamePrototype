//
//  TimesPanel.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#include "TimesPanel.h"


// sorting function
bool sortByRankPos(Player* a , Player* b){
    float completedA = a->completedLaps + a->lapPercent;
    float completedB = b->completedLaps + b->lapPercent;
    if (completedA > completedB){
        return true;
    } else {
        return false;
    }
}



TimesPanel::TimesPanel(){
    assets = Assets::getInstance();
    
    // TODO: move to assets
    presura20.load("GT-Pressura-Mono.otf", 22, true, true);
    presura20.setLineHeight(18.0f);
    presura20.setLetterSpacing(1.037);
}


void TimesPanel::setup(vector<Player *> * _players){
    players = _players;
}


void TimesPanel::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofPushStyle();
    
    ofSetColor(0, 200);
    ofDrawRectangle(0,0, 1920, 42);
    
    ofDisableBlendMode();
    
    vector<Player*> sorted(*players);
    ofSort(sorted, sortByRankPos);
    
    ofVec2f pos(45,27);
    for(auto player : sorted){
        // draw rank and name in color
        ofSetColor(player->color);
        
        string rankPos = ofToString(player->rankPos + 1);
        string name = ofToUpper(player->name);
        string string1 = rankPos + ". " + name;
        
        presura20.drawString(string1, pos.x, pos.y);
        
        pos.x += presura20.stringWidth(string1) + 15;
        
        // draw player info in white
        ofSetColor(255);
        
        string lastLapTime = player->lastLapTimeString;
        string completedLaps = "(" + ofToString(player->completedLaps) + "/" + ofToString(assets->getNumLaps()) + ")";
        string string2 = completedLaps + " _ " + lastLapTime ;
        
        presura20.drawString(string2, pos.x, pos.y);
        
        pos.x += presura20.stringWidth(string2) + 35;
    }
    
    ofPopStyle();
}