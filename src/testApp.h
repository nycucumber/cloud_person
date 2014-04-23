//
//  particle.h
//  PARTICLE_SYSTEM_TEST
//
//  Created by Yang Wang on 4/15/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "particle.h"
#include "target.h"
#include "ofxUI.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 4444
#define NUM_MSG_STRINGS 20

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
    
   // ofMesh mesh;
    ofEasyCam cam;
    ofxKinect kinect;
   // ofVboMesh mesh;
    vector<particle> ps;
    bool firstRun;
    float meditationLevel;
    //UI
    ofxUICanvas * gui;
    void exitUI();
    void guiEvent(ofxUIEventArgs &e);
    
    //osc
    ofxOscReceiver receiver;
    
    
};
