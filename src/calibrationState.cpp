#include "calibrationState.h"
#include "startState.h"

calibrationState::calibrationState(App *a):BaseState(a){
    BaseState::initialize();
    x = -22;
    y = 33;
    sx = 1.009;
    sy = 1.004;
    px = -21;
    py = 32;
};

calibrationState::~calibrationState(){
};

void calibrationState::draw(){
    Assets::getInstance()->collisionMap.draw(x, y, 1920 * sx, 1080 * sy);
    
    
    app->panelCup.drawDebug();
    
    app->panelRanking.drawDebug();
    app->panelTime.drawDebug();
};

void calibrationState::update(){};

void calibrationState::next(){
    app->setCurrentState(new startState(app));
    delete this;
};

void calibrationState::keypressed(int key){
    switch (key) {
        case OF_KEY_UP:
            app->panelRanking.position.y -= 1;
            break;
        case OF_KEY_DOWN:
             app->panelRanking.position.y += 1;
            break;
        case OF_KEY_LEFT:
             app->panelRanking.position.x -= 1;
            break;
        case OF_KEY_RIGHT:
             app->panelRanking.position.x += 1;
            break;
        case '+':
            sx += 0.001;
            break;
        case '-':
            sx -= 0.001;
            break;
        case ' ':
            next();
            break;
        case 13:
            next();
            break;
        default:
            break;
    }
    cout <<  app->panelRanking.position.x << " " <<  app->panelRanking.position.y << " " << sx << " " << sy << endl;
}