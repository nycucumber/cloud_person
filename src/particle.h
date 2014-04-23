//
//  particle.h
//  PARTICLE_SYSTEM_TEST
//
//  Created by Yang Wang on 4/18/14.
//
//

#ifndef __PARTICLE_SYSTEM_TEST__particle__
#define __PARTICLE_SYSTEM_TEST__particle__

#include <iostream>
#include "ofMain.h"


class particle {
public:
    
    //constructor
    particle(ofVec3f _location);
    
    //Methods
    void update();
    void seek(ofVec3f _target);
    void display();
    ofVec3f getPosition();
    
    //properties
    ofVec3f location;
    ofVec3f velocity;
    ofVec3f acceleration;
    float maxforce;
    float maxspeed;
    bool target_assigned;
    //tail
  //  vector<ofVec3f> history;
    
    
    
};


#endif /* defined(__PARTICLE_SYSTEM_TEST__particle__) */
