//
//  PanelPower.cpp
//  racingGame
//
//  Created by Nestor Rubio Garcia on 05/03/2016.
//
//

#include "PanelPower.h"

PanelPower::PanelPower(vector<Player*>& _players)
: players(_players)
{
    cout << players.size() << endl;
}