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
}


void PanelRanking::setup(vector<Player *> * _players){
    players = _players;
    position.set(1622, 657);
}



void PanelRanking::draw(){
    // draw background
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    assets->panelRanking.draw(position);
    ofDisableBlendMode();
}