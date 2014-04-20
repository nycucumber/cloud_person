//
//  target.h
//  PARTICLE_SYSTEM_TEST
//
//  Created by Yang Wang on 4/20/14.
//
//

#ifndef __PARTICLE_SYSTEM_TEST__target__
#define __PARTICLE_SYSTEM_TEST__target__

#include <iostream>
#include "ofMain.h"


class target {
public:
    
    
    target(ofVec3f _location);
    
    ofVec3f location;
    bool choosen;
    
    
    
};
#endif /* defined(__PARTICLE_SYSTEM_TEST__target__) */
