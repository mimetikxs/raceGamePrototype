#include "assets.h"

void Assets::loadAssets(){
    loadImage(&map, "map.png");
    loadImage(&collisionMap, "progess-map.png");
    loadImage(&bikeImg, "bike1.png");
    loadImage(&backgroundImg, "background.png");
}


string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i)).asString();
}