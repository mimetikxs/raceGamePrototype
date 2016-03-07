//
//  PanelCup.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 07/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelCup {
    
public:
    
    PanelCup();
    
    void setup();
    void draw();
    
    ofVec2f position;
    
private:
    
    Assets* assets;    
    
    ofVec2f p;
    void keyPressed(ofKeyEventArgs& eventArgs){
        int key = eventArgs.key;
        switch (key) {
            case OF_KEY_UP:
                p.y--;
                break;
            case OF_KEY_DOWN:
                p.y++;
                break;
            case OF_KEY_LEFT:
                p.x--;
                break;
            case OF_KEY_RIGHT:
                p.x++;
                break;
            default:
                break;
        }
        cout << p << endl;
    }
};


