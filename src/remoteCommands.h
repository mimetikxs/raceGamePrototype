//
//  Header.h
//  raceGamePrototype
//
//  Created by miguel on 03/03/16.
//
//

#ifndef raceGamePrototype_Header_h
#define raceGamePrototype_Header_h
class RemoteCommands
{
    
public:
    
    virtual void processRemoteCommand(int player, bool up, bool down,
                                      bool left, bool right, bool turbo){};
};

#endif
