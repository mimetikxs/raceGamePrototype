#include "assets.h"

void Assets::loadAssets(){
    collisionMap.load("map.png");
    progressMap.load("progess-map.png");
    backgroundImg.load("background.png");
    bike1.load("bike1.png");
}

string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i)).asString();
}