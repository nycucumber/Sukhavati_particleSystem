#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    cam.enableMouseInput();
    cam.enableMouseMiddleButton();
    //kinect
    kinect.setRegistration();
    kinect.init();
    kinect.open();
    noise = false; //use 'n' to toggle
    freeze = false;
    
}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}

//-------------------------------------------------------------
void testApp::draw(){
    
  
    
    ofVec3f velocity;
    velocity.set(ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1)));
    
    
    ofMesh kmesh;
    cam.begin();
    
    
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofPoint(ofVec3f(0,0,0));
    
    ofPopStyle();
    
    kmesh.setMode(OF_PRIMITIVE_POINTS);
  
    
    
    int w = 640;
    int h = 480;
    int step = 10;
    
   
    
    
    if(!noise){
        for ( int y=0;y < h; y++){
            for(int x=0; x < w; x++){
                if(kinect.getDistanceAt(x, y)>0 && kinect.getDistanceAt(x, y)<1000){
                    body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                   
                    //kmesh.addVertex(kinect.getWorldCoordinateAt(x, y));
                    //body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                }
            }
        }
    }else if(freeze){
        body.clear();
        for ( int y=0;y < h; y++){
            for(int x=0; x < w; x++){
                if(kinect.getDistanceAt(x, y)>0 && kinect.getDistanceAt(x, y)<1000){
                    body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                    
                    //kmesh.addVertex(kinect.getWorldCoordinateAt(x, y));
                    //body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                }
            }
        }
        freeze = false;
        
    }
    
    
    
    
    cout<<body.size()<<endl;
    
    
    if(noise){
        for(int i=0;i<body.size();i++) {
            ofVec3f _velocity;
            _velocity.set(ofRandom(-1,1), ofRandom(-1,1),ofRandom(-1,1));
            body[i]=body[i]+_velocity;
        }
    }
    
    
    
    //apply all of the positions information into our mesh
    for(int i=0;i<body.size();i++){
        kmesh.addVertex(body[i]);
    }
    
    ofPushMatrix();
    ofPushStyle();
    ofEnableDepthTest();
    ofScale(-0.5,-0.5,0.5);
    ofSetColor(255, 255, 255);
    kmesh.draw();
    ofDisableDepthTest();
    ofPopStyle();
    ofPopMatrix();
    cam.end();
  
    
    if(!noise){
        
        body.clear();
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='n'){
        noise = !noise;
        freeze = true;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
