//
//  PanelPower.h
//  racingGame
//
//  Created by Nestor Rubio Garcia on 05/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "Player.h"
#include "assets.h"


class PanelPower {
    
public:
    
    PanelPower();
    
    void setup(vector<Player*>* players);
    void update();
    void draw();
    
    vector<Player*> * players;
    
    ofVec2f position;
    
private:
    
    ofFbo fboBars;
    vector<ofVec2f> barPositions;
    ofMesh mask;
    float maskTopMin;
    float maskTopMax;
    float maskBottomMin;
    float maskBottomMax;
    
    void drawPowerBar(int index);
    
    Assets* assets;
    
    
    
//    void keyPressed(ofKeyEventArgs& eventArgs){
//        int key = eventArgs.key;
//        switch (key) {
//            case OF_KEY_UP:
//                p.y--;
//                break;
//            case OF_KEY_DOWN:
//                p.y++;
//                break;
//            case OF_KEY_LEFT:
//                p.x--;
//                break;
//            case OF_KEY_RIGHT:
//                p.x++;
//                break;
//            default:
//                break;
//        }
//        cout << p << endl;
//    }
};
