//
//  PanelWinners.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#include "PanelWinners.h"


PanelWinners::PanelWinners(){
    assets = Assets::getInstance();
    
    // TODO: move to assets
    presura52.load("GT-Pressura-Mono.otf", 52, true, true);
    presura52.setLineHeight(18.0f);
    presura52.setLetterSpacing(1.037);
    presura25.load("GT-Pressura-Mono.otf", 25, true, true);
    presura25.setLineHeight(18.0f);
    presura25.setLetterSpacing(1.037);
    
    numberPositions.push_back(ofVec2f(41,127));
    numberPositions.push_back(ofVec2f(41,254));
    numberPositions.push_back(ofVec2f(41,372));
}


void PanelWinners::setup(vector<Player *> * _players){
    players = _players;
    position.set(1622, 615);
}



void PanelWinners::draw(){
    // draw background
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    assets->panelWinnersBack.draw(position);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    assets->panelWinnersFront.draw(position.x+2, position.y-19);
    
    // draw players
    ofPushMatrix();
    ofTranslate(position);
    
    ofPushStyle();
    for (int i = 0; i < players->size(); i++) {
        drawPlayer(i);
    }
    ofPopStyle();
    
    ofPopMatrix();
    
    ofDisableBlendMode();
}


void PanelWinners::drawPlayer(int index){
    Player* player = players->at(index);
    string name = ofToUpper(player->name);
    ofImage* helmet = player->helmet;
    int ranking = player->rankPos;
    
    if(ranking == 3)
        return;
    
    ofColor color = player->textColor;
    
    ofVec2f p = numberPositions[ranking];
    float x = p.x;
    float y = p.y;
    
    ofSetColor(color);
    presura52.drawString(ofToString(ranking+1), x, y);
    
    ofSetColor(255);
    
    x += 128;
    y += 6;
    presura25.drawString(name, x-presura25.stringWidth(name)/2, y);
    
    x -= 22;
    y -= 62;
    helmet->draw(x, y);
    
}