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
        receiver->getNextMessage(&m);
        processOscMessage(m);
    }
}


void OscAdapter::processOscMessage(ofxOscMessage msg){
    
    
}
