
#ifndef __baseAssets__
#define __baseAssets__

#include "ofMain.h"
#include "ofxJSON.h"

#define MAX_FONT 128

class BaseAssets{
public:
    BaseAssets();
    map<string, ofImage> images;
    
    void loadImage(string filename);
    void getImage(string filename);
    void loadVideo(ofVideoPlayer *video, string filename);
    void stopVideos();
    
    int getLocalPort();
    int getWidth();
    int getHeight();
    float getScale();
    string getRemoteDataAddress();
    
    string getRemoteIp();
    int getRemotePort();
    
    virtual void loadAssets()=0;
    
    ofTrueTypeFont *getFont(int size);
    void loadFont(int size);

    string default_font;
    Json::Value getData(string key);
    
private:
    vector<ofVideoPlayer*> videos;
    
    ofxJSONElement settings;
    
    void clearFonts();
    ofTrueTypeFont		*fonts[MAX_FONT];
    
};


#endif