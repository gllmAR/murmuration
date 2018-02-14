#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    
    sender.setup(HOST, PORT);
    windowResized(ofGetWindowWidth(), ofGetWindowHeight());
    
    gui.setup("");
    gui.setName("murmuration");
    gui.add(particuleNombre.set("particule",32,1,100));
    gui.add(friction.set("friction",1, 0, 10));
    gui.add(drag.set("drag",1, 0, 10));
    gui.add(playbackSpeedMin.set("playbackSpeedMin",0, -1,1));
    gui.add(playbackSpeedRange.set("playbackSpeedRange", 1, 0, 5));
    gui.add(volume.set("volume", 0.2, 0, 1));
    gui.add(loadSoundFromFolderButton.setup("loadSound"));
    gui.add(loadSoundsFromFolderButton.setup("loadSounds"));
    gui.add(loadedSoundPath.set(""));

    loadSoundFromFolderButton.addListener(this, &ofApp::loadSoundFromFolder);
    loadSoundsFromFolderButton.addListener(this, &ofApp::loadSoundsFromFolder);
    
    setParticules();
    
    ofSetFrameRate(60);
    gui.setPosition(ofGetWindowWidth()-200, 0);
}

void ofApp::setParticules(){
    
    p.assign(particuleNombre, demoParticle());
    soundP.resize(particuleNombre);
    for (int i=0;i<particuleNombre;i++){
        soundP[i].load("sample.mp3");
        soundP[i].setVolume(volume);
        soundP[i].play();
        soundP[i].setLoop(1);
    }
    currentMode = PARTICLE_MODE_ATTRACT;
    
    currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    
    resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){
    
    //these are the attraction points used in the forth demo
    attractPoints.clear();
    for(int i = 0; i < 4; i++){
        attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
    }
    
    attractPointsWithMovement = attractPoints;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].setAttractPoints(&attractPointsWithMovement);;
        p[i].reset();
    }
    
    oldParticuleNombre= particuleNombre;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (particuleNombre!=oldParticuleNombre){
        setParticules();
    }
    ofxOscMessage m;
    m.setAddress("/x/y");
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].update();
        p[i].setFrcFactor(friction);
        p[i].setDragFactor(drag);
        
        float particulePlaybackSpeed = playbackSpeedMin + (p[i].pos.y/windowSize.y)*playbackSpeedRange;
        soundP[i].setPan(p[i].pos.x/windowSize.x);
        soundP[i].setSpeed(particulePlaybackSpeed);
        soundP[i].setVolume(volume);

        m.addFloatArg(p[i].pos.x/windowSize.x);
        m.addFloatArg(p[i].pos.y/windowSize.y);
    
    }
    
    sender.sendMessage(m, false);
    ofSoundUpdate();

    
    //lets add a bit of movement to the attract points
    for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
        attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].draw();
    }
    
    ofSetColor(190);
    if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
        for(unsigned int i = 0; i < attractPoints.size(); i++){
            ofNoFill();
            ofDrawCircle(attractPointsWithMovement[i], 10);
            ofFill();
            ofDrawCircle(attractPointsWithMovement[i], 4);
        }
    }
    
    ofSetColor(230);
    ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == '1'){
        currentMode = PARTICLE_MODE_ATTRACT;
        currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    }
    if( key == '2'){
        currentMode = PARTICLE_MODE_REPEL;
        currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
    }
    if( key == '3'){
        currentMode = PARTICLE_MODE_NEAREST_POINTS;
        currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
    }
    if( key == '4'){
        currentMode = PARTICLE_MODE_NOISE;
        currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
        resetParticles();
    }
    
    if( key == ' ' ){
        resetParticles();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    windowSize.x=w;
    windowSize.y=h;
     gui.setPosition(w-200, 0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------

void ofApp::loadSoundFromFolder(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
        string path = result.getPath();
        loadedSoundPath = path;
        
        for (int i=0;i<particuleNombre;i++){
            soundP[i].load(path);
            soundP[i].setVolume(volume);
            soundP[i].play();
            soundP[i].setLoop(1);
        }
        // load your file at `path`
    }

}

void ofApp::loadSoundsFromFolder(){
     ofFileDialogResult result = ofSystemLoadDialog("Load file",true);
    
    if(result.bSuccess) {
        string path = result.getPath();
        loadSoundsDir(path);
        }
        // load your file at `path`
    }

//--------------------------------------------------------------

void ofApp::loadSoundsDir(string folder){
    
    soundsPath.clear();
    string path = folder;
    ofDirectory dir(path);

    dir.allowExt("wav");
    dir.listDir();
    dir.allowExt("mp3");
    dir.listDir();
    dir.allowExt("aiff");
    dir.listDir();
    dir.allowExt("mp4");
    dir.listDir();
    dir.sort();
    dir.listDir();
    soundsTotal = dir.size();
    
    // erreur a catcher s'il n y a pas de folder.
    
    // storer les path des images dans un vector de string
    for (int i = 0; i < dir.size(); i++){
        soundsPath.push_back (dir.getPath(i));
        
    }
    
    for (int i=0;i<particuleNombre;i++){
        soundP[i].load(soundsPath[i%soundsPath.size()]);
        soundP[i].setVolume(volume);
        soundP[i].play();
        soundP[i].setLoop(1);
        cout<<soundsPath[i%soundsPath.size()]<<endl;
    }
      
}

