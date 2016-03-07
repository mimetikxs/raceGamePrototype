#include "calibrationState.h"
#include "startState.h"

calibrationState::calibrationState(App *a):BaseState(a){
    BaseState::initialize();
    x = -21;
    y = 39;
    sx = 1.01;
    sy = 1.011;
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
            y -= 1;
            break;
        case OF_KEY_DOWN:
            y += 1;
            break;
        case OF_KEY_LEFT:
            x -= 1;
            break;
        case OF_KEY_RIGHT:
            x += 1;
            break;
        case '+':
            sy += 0.001;
            break;
        case '-':
            sy -= 0.001;
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
    cout << x << " " << y << " " << sx << " " << sy << endl;
}