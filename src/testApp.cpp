#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255,255, 255);
    cam.enableMouseInput();
    cam.enableMouseMiddleButton();
    
    kinect.setRegistration();
    kinect.init();
    kinect.open();
    
    
    for(int i=0;i<5000;i++){
        ps.push_back(ofVec3f(ofRandom(-300,300), ofRandom(-300,300),ofRandom(-300,300)));
    }
    

}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}
//--------------------------------------------------------------
void testApp::draw(){
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
    int step = 3;
    
    vector<ofVec3f> particles;
    
    for(int y=0;y<h;y+=step){
        for(int x=0;x<w;x+=step){
            if(kinect.getDistanceAt(x, y)>0&&kinect.getDistanceAt(x, y)<1000){
                particles.push_back(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
            }
        }
    }
    
    //compare the amount between our Particle Vector and all kinect particles
    while(particles.size() > ps.size()){
        ps.push_back(ofVec3f(ofRandom(-300,300), ofRandom(-300,300),800));
    }
    
    if(particles.size() < ps.size()){
        int dvalue = ps.size() - particles.size();
        ps.erase(ps.begin(),ps.begin()+dvalue);
    }
    
//    
//    //re-assign target
//    for(int a=0; a<particles.size(); a++){
//        for(int b=0; b<ps.size(); b++){
//            
//        }
//    }
//    
    //seek target
    for(int i=0;i<ps.size();i++){
    }
    
    for(int i=0;i<ps.size();i++){
//        float minDistance;
//        for(int b=0;b<particles.size();b++){
        
//            vector<float> distances;
//            distances.push_back(ps[i].location.distance(particles[b]));
//            

            
            ps[i].seek(particles[i]);
            ps[i].update();
            
            mesh.addVertex(ps[i].getPosition());
            
//        }
    }
    
    ofSetColor(0, 0, 0);
    mesh.draw();
    cam.end();
    
    
    cout<<particles.size()<<endl;  //particles amount
    particles.clear();

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
