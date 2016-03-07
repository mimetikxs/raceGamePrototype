#include "assets.h"

void Assets::loadAssets(){
    loadImage(&collisionMap, "images/map.png");
    loadImage(&progressMap, "images/progess-map.png");
    loadImage(&backgroundImg, "images/background-track-only.png");
    
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
    
    loadImage(&panelPower0, "images/panel-power/panelPower0.png");
    loadImage(&panelPower1, "images/panel-power/panelPower1.png");
    loadImage(&powerBar, "images/panel-power/powerBar.png");
    
    loadImage(&panelRankingBack, "images/ranking/rankingBack.png");
    
    loadImage(&panelWinnersBack, "images/winners/winnersBack.png");
    loadImage(&panelWinnersFront, "images/winners/winnersFront.png");
    
    loadImage(&cupBack, "images/cup/cupBack.png");
    loadImage(&cupFront, "images/cup/cupFront.png");
    
    loadImage(&panelLapsBack, "images/laps/lapsBack.png");
    loadImage(&panelLapsFront, "images/laps/lapsFront.png");
    
    for(int i = 0; i < 4; i++){
        motorSound[i].load("motorcycle.wav");
        //motorSound[i].setMultiPlay(true);
        motorSound[i].setLoop(true);
        motorSound[i].setPosition(ofRandom(1));
        //motorSound[i].setVolume(0.8);
    }
    
    cheer.load("cheer_short.wav");
    cheer.setMultiPlay(true);
    
    presura25.load("GT-Pressura-Mono.otf", 25, true, true);
    
    countdown.load("countdown-no-alpha.mp4");
}


string Assets::getPlayerName(int i){
    return getData("player_" + ofToString(i))["name"].asString();
}

int Assets::getPlayerPosition(int i){
    return getData("player_" + ofToString(i))["position"].asInt();
}

string Assets::getPlayerAttributes(int i){
    return getData("player_" + ofToString(i))["color"].asString();
}

int Assets::getNumLaps(){
    return getData("num_laps").asInt();
}

bool Assets::useBikeCollisions(){
    return getData("collisions").asBool();
}

vector<ofImage*> Assets::getRandomPowerupImage(){
    int i = ofRandom(4);
    vector<ofImage*> img;
    switch (i) {
        case 0:
            img.push_back(&powerup1);
            img.push_back(&powerupGlow1);
            return img;
            break;
        case 1:
            img.push_back(&powerup2);
            img.push_back(&powerupGlow2);
            return img;
            break;
        case 2:
            img.push_back(&powerup3);
            img.push_back(&powerupGlow3);
            return img;
            break;
        case 3:
            img.push_back(&powerup4);
            img.push_back(&powerupGlow4);
            return img;
            break;
        default:
            img.push_back(&powerup1);
            img.push_back(&powerupGlow1);
            return img;
            break;
    }
}