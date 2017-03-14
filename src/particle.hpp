#pragma once
#include "ofMain.h"
#include "ofxGui.h"

enum particleMode{
    PARTICLE_MODE_ATTRACT = 0,
    PARTICLE_MODE_REPEL,
    PARTICLE_MODE_NEAREST_POINTS,
    PARTICLE_MODE_NOISE
};

class demoParticle{
    
public:
    demoParticle();
    
    void setMode(particleMode newMode);
    void setAttractPoints( vector <ofPoint> * attract );
    void setVelFactor(float factor);
    void setFrcFactor(float factor);
    void setDragFactor(float factor);
    
    void reset();
    void update();
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    float velFactor = 1.0f;
    float dragFactor = 1.0f;
    float frcFactor = 4.0f;
    
    


    
    particleMode mode;
    
    vector <ofPoint> * attractPoints;
};
