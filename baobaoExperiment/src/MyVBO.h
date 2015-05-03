//
//  MyVBO.h
//  baobaoExperiment
//
//  Created by James Kong on 30/4/15.
//
//

#ifndef __baobaoExperiment__MyVBO__
#define __baobaoExperiment__MyVBO__

#include <stdio.h>
#include "ofMain.h"
class MyVBO
{
public:
    void setup();
    void update();
    void draw();
    ofParameter <float> feq;
    ofParameter <float> pow;
    ofParameter <float> wave_density;
    ofParameter <float> noise_density;
private:
    
    ofVbo vboMesh;
    vector<ofVec3f> pos;
    vector<ofVec3f> vert;
    vector<ofVec3f> normal;
    vector<ofFloatColor> color;
    vector<ofVec2f> tex_coord;
    ofVec3f center;
    

    
    int total;
    int WIDTH;
    int HEIGHT;
    int space;
};
#endif /* defined(__baobaoExperiment__MyVBO__) */
