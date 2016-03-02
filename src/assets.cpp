#include "assets.h"

void Assets::loadAssets(){
    loadImage("map.png");
    loadImage("progess-map.png");
    loadImage("bike1.png");
    loadImage("background.png");
}


ofImage Assets::getMap(){
    return images["map.png"];
}

ofImage Assets::getCollisionMap(){
    return images["progess-map.png"];
}

ofImage Assets::getBackground(){
    return images["background.png"];
}

ofImage Assets::getBikeImage(int i){
    return images["bike1.png"];
}

string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i)).asString();
}