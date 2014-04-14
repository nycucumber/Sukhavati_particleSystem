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
    
    noise = false;
    //use 'n' to toggle
    
    TimeToDoLastRead = false;
    body2_set = false;
    p_returning = false;
    setVV = false;
    acceleration_set=false;
    
    releaseTime = 1;
    timer = 0;
    maxSpeed = 10;
    maxforce = 0.2;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    kinect.update();
    
    cout<<"TIMER: "<<timer<<endl;
    cout<< "p_returning: "<<p_returning<<endl;
    
    
    if (noise) { //only execute when particles got released
        
        tsB = ofGetElapsedTimef();
        timer = tsB - tsA;
        
    }
    
    
}

//-------------------------------------------------------------
void testApp::draw(){

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
    
    
    
    //get mesh data from kinect per frame---------------------
    if(!noise){
        for ( int y=0;y < h; y++){
            for(int x=0; x < w; x++){
               if(kinect.getDistanceAt(x, y)>0 && kinect.getDistanceAt(x, y)<1000){
                    body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                   if (setVV==false) {
                       velocity.push_back(ofVec3f(ofRandom(-0.1,0.1), ofRandom(-0.1,0.1),ofRandom(-0.1,0.1)));
                   }
                
                }
            }
        }
        if(velocity.size()!=0){
            setVV = true;
            cout<<"velocity is "<<velocity[0]<<endl;

        }
    }
    
    
    //if we pressed key, read data from kinect one more time then set TimeToDoLastRead to false---------------------
    
    if(noise && TimeToDoLastRead){
        body.clear();
        for ( int y=0;y < h; y++){
            for(int x=0; x < w; x++){
                if(kinect.getDistanceAt(x, y)>0 && kinect.getDistanceAt(x, y)<1000){
                    body.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                }
            }
        }
        TimeToDoLastRead = false;
        tsA = ofGetElapsedTimef();        //get the time when we TimeToDoLastRead everthing and kick off the animation

    }
    
    

    
    
    //if we pressed key, move every vertex in "body" ------------------------------------
    
    if(noise && TimeToDoLastRead == false){
        
        if(timer >= releaseTime && p_returning == false){
            //GET REAL-TIME KINECT IMAGE, GET DATA STORING INTO "BODY2"
            for ( int y=0;y < h; y++){
                for(int x=0; x < w; x++){
                    if(kinect.getDistanceAt(x, y)>0 && kinect.getDistanceAt(x, y)<1000){
                        body2.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                    }
                }
            }
            p_returning = true; //kick off our animation
            timer = 0;//reset timer
            tsA = ofGetElapsedTimef();//time stamp A
        }
        
        
        //if 'particle returning' is true, move towards our targets
        if (p_returning == true) {
            
            for(int i=0;i<body.size();i++){
                ofVec3f desired;
                ofVec3f steer;
                desired = body2[i]-body[i];
                desired.normalize();
                desired * maxSpeed;
                steer = desired-velocity[i];
                steer.limit(maxforce);
                acceleration.push_back(steer);
                velocity[i] = velocity[i]+acceleration[i];
                body[i]+=velocity[i];
            
            }
        }
        
        //RESET STATE ACCORDING BY TIMER>=3
        if(timer >= releaseTime && p_returning == true){
            velocity.clear();
            velocity.push_back(ofVec3f(ofRandom(-0.1,0.1), ofRandom(-0.1,0.1),ofRandom(-0.1,0.1)));

            p_returning = false;
            
            timer = 0;
            tsA = ofGetElapsedTimef();
        }
        
        
        
        //if 'particle returning' is false, move randomly
        if(p_returning == false){
            for(int i=0;i<body.size();i++) {
                body[i]=body[i]+velocity[i];
            }
        }
        
    }
    
    
    //apply all of the positions information into our mesh  ----------------------------
    for(int i=0;i<body.size();i++){
        kmesh.addVertex(body[i]);
    }
    
    kmesh.setMode(OF_PRIMITIVE_LINE_LOOP);
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
    
    acceleration.clear();
    body2.clear();
    cout<<"----------------------"<<endl;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='n'){
        noise = !noise;
        TimeToDoLastRead = true;
        timer = 0;

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
