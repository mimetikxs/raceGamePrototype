#include "assets.h"

void Assets::loadAssets(){
    loadImage(&collisionMap, "images/map.png");
    loadImage(&progressMap, "images/progess-map.png");
    loadImage(&backgroundImg, "images/background.png");
    
    loadImage(&bike1, "images/bikes/bike1.png");
    loadImage(&bike2, "images/bikes/bike2.png");
    loadImage(&bike3, "images/bikes/bike3.png");
    loadImage(&bike4, "images/bikes/bike4.png");
    loadImage(&bikeGlow, "images/bikes/bikeGlow.png");
    
    loadImage(&helmet1, "images/helmets/helmet1.png");
    loadImage(&helmet2, "images/helmets/helmet2.png");
    loadImage(&helmet3, "images/helmets/helmet3.png");
    loadImage(&helmet4, "images/helmets/helmet4.png");
    
    loadImage(&powerup1, "images/powerups/powerup1.png");
    loadImage(&powerup2, "images/powerups/powerup2.png");
    loadImage(&powerup3, "images/powerups/powerup3.png");
    loadImage(&powerup4, "images/powerups/powerup4.png");
    loadImage(&powerupGlow1, "images/powerups/powerup1-glow.png");
    loadImage(&powerupGlow2, "images/powerups/powerup2-glow.png");
    loadImage(&powerupGlow3, "images/powerups/powerup3-glow.png");
    loadImage(&powerupGlow4, "images/powerups/powerup4-glow.png");
    
    loadImage(&panelPower, "images/panel-power/panelPower.png");
    loadImage(&panelPower, "images/panel-power/powerBar.png");
    
    loadImage(&panelRanking, "images/panel-ranking.png");
    
    loadImage(&panelWinners, "images/panel-winners.png");
    loadImage(&cup, "images/cup.png");
    
    loadImage(&panelLaps, "images/laps.png");
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

ofImage& Assets::getHelmet(int i){
    switch (i) {
        case 0:
            return helmet1;
            break;
        case 1:
            return helmet2;
            break;
        case 2:
            return helmet3;
            break;
        case 3:
            return helmet4;
            break;
        default:
            return helmet1;
            break;
    }
}

int Assets::getNumLaps(){
    return getData("num_laps").asInt();
}