#include "ofApp.h"


void ofApp::setup(){
    ofBackground(90);
    
    race.setup();
    
    race.start();
    
    gui.setup();
    gui.add(race.bike.parameters);
    gui.add(race.bike.parametersCollision);
    
    gui.loadFromFile("settings.xml");
}


void ofApp::update(){
    race.update();
}


void ofApp::draw(){
    race.draw();
    gui.draw();
    
    race.drawInfo();
}


void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            race.bike.bAccelerate = true;
            break;
        case OF_KEY_LEFT:
            race.bike.bTurnLeft = true;
            break;
        case OF_KEY_RIGHT:
            race.bike.bTurnRight = true;
            break;
        default:
            break;
    }
}


void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
            race.bike.bAccelerate = false;
            break;
        case OF_KEY_LEFT:
            race.bike.bTurnLeft = false;
            break;
        case OF_KEY_RIGHT:
            race.bike.bTurnRight = false;
            break;
        default:
            break;
    }
}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}
