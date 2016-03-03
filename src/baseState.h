#ifndef __State__
#define __State__

#include "ofMain.h"
#include "remoteCommands.h"

class App;

class BaseState : public RemoteCommands
{
    
protected:
    App *app;
    float timer;
    
public:
    BaseState(App *a);
    ~BaseState();
    
    bool isDone(int duration);
    void initialize();
    
    virtual void next()=0;
    virtual string toString()=0;
    virtual void draw()=0;
    virtual void update()=0;
    virtual void keypressed(int key){};
    virtual void keyReleased(int key){};
    
    virtual void click(int x, int y){};
    

};


#endif