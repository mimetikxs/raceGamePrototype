#include "assets.h"

void Assets::loadAssets(){
    loadImage("map.png");
    loadImage("progess-map.png");
    loadImage("bike1.png");
    backgroundImg.load("background.png");
}


ofImage Assets::getMap(){
    return images["map.png"];
}

ofImage Assets::getCollisionMap(){
    return images["progess-map.png"];
}


ofImage Assets::getBikeImage(int i){
    return images["bike1.png"];
}

string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i)).asString();
}