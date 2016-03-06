//
//  PanelRanking.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#include "PanelRanking.h"


PanelRanking::PanelRanking(){
    assets = Assets::getInstance();
    
    // TODO: move to assets
    presura22.load("GT-Pressura-Mono.otf", 22, true, true);
    presura22.setLineHeight(18.0f);
    presura22.setLetterSpacing(1.037);
    presura31.load("GT-Pressura-Mono.otf", 31, true, true);
    presura31.setLineHeight(18.0f);
    presura31.setLetterSpacing(1.037);
    
    positions.push_back(ofVec2f(0,79));
    positions.push_back(ofVec2f(30,176));
    positions.push_back(ofVec2f(30,255));
    positions.push_back(ofVec2f(30,332));
}


void PanelRanking::setup(vector<Player *> * _players){
    players = _players;
    position.set(1622, 657);
}



void PanelRanking::draw(){
    // draw background
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    assets->panelRanking.draw(position);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // draw players
    ofPushMatrix();
        ofTranslate(position);
        for (int i = 0; i < players->size(); i++) {
            drawPlayer(i);
        }
        drawPlayer(0);
    ofPopMatrix();
    
    ofDisableBlendMode();
}


void PanelRanking::drawPlayer(int index){
    Player* player = players->at(index);
    string name = ofToUpper(player->name);
    ofImage* helmet = player->helmet;
    int ranking = player->rankPos;
    
    ofVec2f p = positions[ranking];
    float x = p.x;
    float y = p.y;
    
    if(ranking == 0){
        // hemlet
        float offY = helmet->getHeight()/1.3;
        helmet->draw(x+27, y-offY);
        // name
        presura31.drawString(name, x+72, y);
    }else{
        // rank pos
        presura22.drawString(ofToString(ranking+1), x, y);
        // hemlet
        float offY = helmet->getHeight()/1.5;
        helmet->draw(x+27, y-offY);
        // name
        presura22.drawString(name, x+72, y);
    }
}