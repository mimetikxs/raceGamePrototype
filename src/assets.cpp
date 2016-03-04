#include "assets.h"

void Assets::loadAssets(){
    loadImage(&collisionMap, "map.png");
    loadImage(&progressMap, "progess-map.png");
    loadImage(&bike1, "bike1.png");
    loadImage(&backgroundImg, "background.png");
}


string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i)).asString();
}


ofColor Assets::getPlayerColor(int i){
    switch (i) {
        case 0:
            return ofColor::mediumOrchid;
            break;
        case 1:
            return ofColor::mediumSeaGreen;
            break;
        case 2:
            return ofColor::mediumTurquoise;
            break;
        case 3:
            return ofColor::sandyBrown;
            break;
        default:
            return ofColor();
            break;
    }
}