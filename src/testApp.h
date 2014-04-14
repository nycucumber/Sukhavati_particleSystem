//
// Sukhavati
// Created By Yang Wang @ 2014 - New York
// This is a Thesis Project
// 



#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    bool noise;
    bool TimeToDoLastRead;
    bool body2_set;
    bool acceleration_set;
    bool p_returning;
    bool setVV;
    ofMesh mesh;
    ofEasyCam cam;
    ofxKinect kinect;
    
    vector<ofVec3f> body;
    vector<ofVec3f> body2;
    vector<ofVec3f> velocity;
    vector<ofVec3f> desired;
    vector<ofVec3f> steer;
    vector<ofVec3f> acceleration;
  
    float timer;
    float tsA;
    float tsB;
    float maxSpeed;
    float maxforce;
    float releaseTime;
};
