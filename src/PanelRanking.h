//
//  PanelRanking.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 06/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelRanking {
    
public:
    
    PanelRanking();
    
    void setup(vector<Player*>* players);
    void draw();
    
    vector<Player*> * players;
    
    ofVec2f position;
    
private:
    
    Assets* assets;
    
    ofTrueTypeFont presura22;
    ofTrueTypeFont presura31;
    
    ofVec2f p;
    vector<ofVec2f> positions;
    
    void drawPlayer(int i);
    
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
