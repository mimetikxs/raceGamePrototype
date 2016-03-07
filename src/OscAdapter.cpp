#include "OscAdapter.h"

OscAdapter::OscAdapter(App *a){
    app = a;
    int localPort = a->getAssets()->getLocalPort();
    
    receiver = new ofxOscReceiver;
    
    receiver->setup(localPort);
    
    ofLogNotice() << "listening for osc messages on port " << localPort;
    bOnline = false;
  
    
    ofAddListener(ofEvents().update, this, &OscAdapter::update);
}

OscAdapter::~OscAdapter(){
    delete receiver;
}

void OscAdapter::update(ofEventArgs &args){
    while(receiver->hasWaitingMessages()){
        bOnline = true;
        ofxOscMessage m;
        receiver->getNextMessage(m);
        processOscMessage(m);
    }
    
    for(int i = 0; i < 4; i ++)
        active[i] = false;
}


void OscAdapter::processOscMessage(ofxOscMessage msg){
    
    
    if(msg.getAddress() == "/player"){
        
        int player = ofToInt(msg.getArgAsString(0))  - 1;
        bool up = !msg.getArgAsBool(1);
        bool down = !msg.getArgAsBool(2);
        bool left = !msg.getArgAsBool(3);
        bool right = !msg.getArgAsBool(4);
        bool turbo = !msg.getArgAsBool(5);
        
        app->current_state->processRemoteCommand(player, up, down, left, right, turbo);
    
        cout << player << up << down << left << right << turbo << endl;
        
        active[player] = true;
        
    }
    
}
