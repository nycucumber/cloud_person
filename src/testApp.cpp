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
    meditationLevel = 100;
    //GUI
    gui = new ofxUICanvas();
    gui->addSlider("Meditation_Level",0.0,100.0,100.0);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
//    ofToggleFullscreen();
    
    
    //osc:::::
    receiver.setup(PORT);
    
    // load the bilboard shader
	// this is used to change the
	// size of the particle
	if(ofGetGLProgrammableRenderer()){
		billboardShader.load("shadersGL3/Billboard");
	}else{
		billboardShader.load("shadersGL2/Billboard");
	}
	
	// we need to disable ARB textures in order to use normalized texcoords
	ofDisableArbTex();
	texture.loadImage("dot.png");
	ofEnableAlphaBlending();
    
    
}
//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if (m.getAddress() == "/meditation") {
           // cout<<m.getArgAsFloat(0)<<endl;
           meditationLevel = ofMap(m.getArgAsFloat(0), 0, 100, 0, 120);
        cout<<meditationLevel<<endl;
        }
    }
}
//--------------------------------------------------------------
void testApp::draw(){
    if(kinect.isFrameNew()){
        cam.begin();
        
        if(meditationLevel>=90){
            ofVboMesh mesh;
            mesh.setUsage( GL_DYNAMIC_DRAW );
            mesh.setMode(OF_PRIMITIVE_POINTS);
            mesh.getNormals().resize(34133,ofVec3f(0));
            int w = 640;
            int h = 480;
            int step = 3;
            vector<target> targets;
            int i=0;
            float t = (ofGetElapsedTimef()) * 0.9f;
            for(int y=0;y<h;y+=step){
                for(int x=0;x<w;x+=step){
                    if(kinect.getDistanceAt(x, y)>0&&kinect.getDistanceAt(x, y)<1500){
                        mesh.addVertex(ofVec3f(kinect.getWorldCoordinateAt(x, y)));
                        mesh.setNormal(i,ofVec3f(10+ ofNoise(t+i),0,0));
                        i++;
                    }
                }
            }
            ofPushMatrix();
          
            ofSetColor(255);
            ofScale(1,-1,1);
            billboardShader.begin();
            ofEnablePointSprites();
            texture.getTextureReference().bind();
            mesh.draw();
            texture.getTextureReference().unbind();
            ofDisablePointSprites();
            billboardShader.end();
            ofPopMatrix();
        }else{
            
            ofVboMesh mesh;
            ofMesh kinectData;
            mesh.setUsage(GL_DYNAMIC_DRAW);
        

            kinectData.setMode(OF_PRIMITIVE_POINTS);
            mesh.setMode(OF_PRIMITIVE_POINTS);
            int w = 640;
            int h = 480;
            int step = 6;
            vector<target> targets;
            for(int y=0;y<h;y+=step){
                for(int x=0;x<w;x+=step){
                    if(kinect.getDistanceAt(x, y)>0&&kinect.getDistanceAt(x, y)<1500){
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
            //===============SET TARGETS===============
                mesh.getNormals().resize(ps.size(),ofVec3f(0));
            for(int i=0;i<ps.size();i++){
                float minDistance = 100000;
                float index = 0;
                
                for(int b=0;b<targets.size();b++){
                    if(targets[b].choosen==false){
                        float distance;
                        distance = ps[i].location.distance(targets[b].location);
                        if(distance < minDistance){
                            minDistance = distance;
                            index = b;
                        }
                    }
                }
                // cout<<"the "<<i<<"'th particle's"<<" minimum distance is "<<minDistance<<" .......his index in [targets] is: "<<index<<endl;
                ps[i].seek(targets[index].location);
                ps[i].target_assigned = true;
                targets[index].choosen = true;
                ps[i].update();
                //adjust movement parameter based on Meditation Level
                ps[i].maxforce = ofMap(meditationLevel, 0, 90, 0.001, 5);
                ps[i].maxspeed = ofMap(meditationLevel, 0, 90, 20, 5);
                mesh.addVertex(ps[i].getPosition());
                mesh.setNormal(i,ofVec3f(10+ ofNoise(ofGetElapsedTimef()+i),0,0));
                i++;
                
            }
            
            //=========GET CENTER POINT LOCATION=========
            //
            //        ofVec3f centerPoint;
            //        ofVec3f Sum;
            //        Sum.set(0, 0,0);
            //        int count = 0;
            //
            //        for(int i=0;i<ps.size();i+=20){
            //            count++;
            //            Sum+=ps[i].location;
            //        }
            //
            //        centerPoint = Sum / count;
            //        cout<<centerPoint<<endl;
            //
            //        for (int i = 0; i<ps.size(); i++){
            //            if(ps[i].target_assigned==false){
            //                ps[i].seek(centerPoint+ofVec3f(ofRandom(-300,300),ofRandom(-300,300),ofRandom(-300,300)));
            //            }
            //        }
            //
            
            
            
            
            //==================JUST DRAW===============
            ofPushMatrix();
            ofSetColor(0, 0, 0);
            ofScale(1,-1,1);
            billboardShader.begin();
            ofEnablePointSprites();
            texture.getTextureReference().bind();
            mesh.draw();
            texture.getTextureReference().unbind();
            ofDisablePointSprites();
            billboardShader.end();
            ofPopMatrix();
            
            //  cout<<targets.size()<<endl;  //particles amount
            
            
            //        for (int i = 0; i<ps.size(); i++){
            //            ps[i].target_assigned = false;
            //        }
            //
            
            
        }//end [meditationlevel < 80] if_statment
        
        cam.end();
        
        
    }//end the [kinect.frameNew] if_statement
    
    
}

//---------
void testApp::exitUI(){
    gui->saveSettings("settings.xml");
    delete gui;
    
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.getName() == "Meditation_Level")
    {
        ofxUISlider *slider = e.getSlider();
        meditationLevel = slider->getScaledValue();
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
