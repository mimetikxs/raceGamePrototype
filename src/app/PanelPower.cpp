//
//  PanelPower.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 05/03/2016.
//
//

#include "PanelPower.h"

PanelPower::PanelPower(){
    assets = Assets::getInstance();
    
    fboBars.allocate(assets->panelPower0.getWidth(), assets->panelPower0.getHeight());
    
    barPositions.push_back(ofVec2f(94,33));
    barPositions.push_back(ofVec2f(94,101));
    barPositions.push_back(ofVec2f(94,165));
    barPositions.push_back(ofVec2f(94,232));
    
    maskTopMin = 9;
    maskTopMax = 144;
    maskBottomMin = -3;
    maskBottomMax = 132;
    
    mask.addVertex(ofVec3f(164, 0, 0));
    mask.addVertex(ofVec3f(maskTopMin, 0, 0));
    mask.addVertex(ofVec3f(maskBottomMin, 22, 0));
    mask.addVertex(ofVec3f(164, 22, 0));
    mask.addTriangle(0, 1, 2);
    mask.addTriangle(0, 2, 3);
    
    //ofAddListener(ofEvents().keyPressed, this, &PanelPower::keyPressed);
}


void PanelPower::setup(vector<Player*>* _players){
    players = _players;
    position.set(1334, 774);
}


void PanelPower::update(){
    
}


void PanelPower::draw(){
    // draw background
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    assets->panelPower0.draw(position);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    assets->panelPower1.draw(position);
    
    // draw power bars
    fboBars.begin();
    ofClear(0);
    for (int i = 0; i < players->size(); i++) {
        drawPowerBar(i);
    }
    fboBars.end();
    
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    fboBars.draw(position);
    ofDisableBlendMode();
}


void PanelPower::drawPowerBar(int index){
    Player* player = players->at(index);
    ofVec2f& pos = barPositions[index];
    float pct = player->bike->powerbar.getPercent();
    
    float top = ofMap(pct, 0, 1, maskTopMin, maskTopMax);
    float bottom = ofMap(pct, 0, 1, maskBottomMin, maskBottomMax);
    mask.setVertex(1, ofVec3f(top, 0, 0));
    mask.setVertex(1, ofVec3f(top, 0, 0));
    mask.setVertex(2, ofVec3f(bottom, 22, 0));
    
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
    assets->powerBar.draw(0,0);

    ofPushStyle();
    ofSetColor(0);
        mask.draw();
    ofPopStyle();
    
    ofPopMatrix();
    
}

