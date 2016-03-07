//
//  PanelCup.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 07/03/2016.
//
//

#include "PanelCup.h"


PanelCup::PanelCup(){
    assets = Assets::getInstance();
}


void PanelCup::setup(){
    position.set(1334, 744);
}


void PanelCup::draw(){
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    assets->cupBack.draw(position);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    assets->cupFront.draw(position);
    
    ofDisableBlendMode();
}

void PanelCup::drawDebug(){
    
    ofSetColor(255);
    ofDrawRectangle(position.x, position.y,  assets->cupBack.getWidth(),  assets->cupBack.getHeight());
}