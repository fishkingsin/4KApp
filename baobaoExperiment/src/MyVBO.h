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
private:
    
    ofVbo vboMesh;
    vector<ofVec3f> pos;//[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    vector<ofVec3f> vert;
    vector<ofVec3f> normal;//[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    vector<ofFloatColor> color;//[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    vector<ofVec2f> tex_coord;//[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofVec3f center;
    
    
    int total;
    int WIDTH;
    int HEIGHT;
    int space;
};
#endif /* defined(__baobaoExperiment__MyVBO__) */
