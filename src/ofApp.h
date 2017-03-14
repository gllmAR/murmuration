#pragma once

#include "ofMain.h"
#include "particle.hpp"
#include "ofxOsc.h"
#include "ofxGui.h"

#define HOST "localhost"
#define PORT 12345


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void resetParticles();
        void setParticules();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void loadSoundFromFolder();
    
    
		
    particleMode currentMode;
    string currentModeStr;
    
    vector <demoParticle> p;
    vector <ofSoundPlayer> soundP;
    
    vector <ofPoint> attractPoints;
    vector <ofPoint> attractPointsWithMovement;
    
    ofxOscSender sender;
    
    ofxPanel gui;
    
    
    ofParameter<float> drag;
    ofParameter<float> friction;
    ofParameter<int> particuleNombre = 32;
    
     ofParameter<float> playbackSpeedMin;
    ofParameter<float> playbackSpeedRange;
    ofParameter<float> volume;
    ofxButton loadSoundFromFolderButton;
 
    ofParameter<string> loadedSoundPath;
    
    ofVec2f windowSize;
    
    int oldParticuleNombre;
    
    
    
    
};
