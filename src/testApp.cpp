#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    ofBackground(255,255, 255);
    cam.enableMouseInput();
    cam.enableMouseMiddleButton();
    
    kinect.setRegistration();
    kinect.init();
    kinect.open();
    firstRun = false;
}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}
//--------------------------------------------------------------
void testApp::draw(){
    if(kinect.isFrameNew()){
        ofMesh mesh;
        ofMesh kinectData;
        kinectData.setMode(OF_PRIMITIVE_POINTS);
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        cam.begin();
 
        int w = 640;
        int h = 480;
        int step = 10;
        
        vector<target> targets;
        
        for(int y=0;y<h;y+=step){
            for(int x=0;x<w;x+=step){
                if(kinect.getDistanceAt(x, y)>0&&kinect.getDistanceAt(x, y)<1000){
                    targets.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                    if(firstRun == false){
                        ps.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                    }
                    
                }
            }
        }
        firstRun = true;
        
        
        //compare the amount between our Particle Vector and all kinect particles
        while(targets.size() > ps.size()){
            ps.push_back(ofVec3f(ofRandom(-300,300), ofRandom(-300,300),800));
        }
 
        
        for(int i=0;i<ps.size();i++){
            float minDistance = 100000;
            float index = 0;
            
            for(int b=0;b<targets.size();b++){
                if(targets[b].choosen==false){
                //  kinectData.addVertex(targets[b].location);
                float distance;
                distance = ps[i].location.distance(targets[b].location);
                //    cout<<distance<<endl;
                if(distance < minDistance){
                    minDistance = distance;
                    index = b;
                }
                }
            }
            // cout<<"the "<<i<<"'th particle's"<<" minimum distance is "<<minDistance<<" .......his index in [targets] is: "<<index<<endl;
            ps[i].seek(targets[index].location);
            targets[index].choosen = true;
            ps[i].update();
            mesh.addVertex(ps[i].getPosition());
        }
        
        ofSetColor(0, 0, 0);
        mesh.draw();
        //  ofSetColor(220);
        //  kinectData.draw();
        cam.end();
        
        cout<<targets.size()<<endl;  //particles amount
        targets.clear();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
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
