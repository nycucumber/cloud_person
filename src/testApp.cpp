#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255,255, 255);
    cam.enableMouseInput();
    cam.enableMouseMiddleButton();
    
    kinect.setRegistration();
    kinect.init();
    kinect.open();
    
    
    for(int i=0;i< 4000 ;i++){
        ps.push_back(ofVec3f(ofRandom(-300,300), ofRandom(-300,300),ofRandom(-300,300)));
    }
    

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
    mesh.setMode(OF_PRIMITIVE_POINTS);
    cam.begin();
    
    
  //  ofSetPlaneResolution(5, 5);
  //  ofDrawPlane(0, 0, 800, ofGetWidth(), ofGetHeight());
    
//    vector<ofVec3f> newPostions;
//    //looop through particles push back all positions
//    
//    //then loop through newPositions and change the vetex position
//    
//    ofVec3f& pos = mesh.getVertices()[0];
//    pos.x = newPostions[0].x;
//    pos.y = newPostions[0].y;
//    pos.z = newPostions[0].z;

    
    int w = 640;
    int h = 480;
    int step = 20;
    
    vector<target> targets;
    
    for(int y=0;y<h;y+=step){
        for(int x=0;x<w;x+=step){
            if(kinect.getDistanceAt(x, y)>0&&kinect.getDistanceAt(x, y)<1000){
                targets.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
            }
        }
    }
    
    
    //compare the amount between our Particle Vector and all kinect particles
//    while(targets.size() > ps.size()){
//        ps.push_back(ofVec3f(ofRandom(-300,300), ofRandom(-300,300),800));
//    }
//    
//    if(targets.size() < ps.size()){
//        int dvalue = ps.size() - targets.size();
//        ps.erase(ps.begin(),ps.begin()+dvalue);
//    }

        
    for(int i=0;i<ps.size();i++){
        float minDistance = 100000;
        float index = 0;
        
        for(int b=0;b<targets.size();b++){
            float distance;
            distance = ps[i].location.distance(targets[b].location);
        //    cout<<distance<<endl;
            if(distance < minDistance){
                minDistance = distance;
                index = b;
            }
        }
       // cout<<"the "<<i<<"'th particle's"<<" minimum distance is "<<minDistance<<" .......his index in [targets] is: "<<index<<endl;
        ps[i].seek(targets[index].location);
        ps[i].update();
        mesh.addVertex(ps[i].getPosition());
    }
        
    ofSetColor(0, 0, 0);
    mesh.draw();
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
