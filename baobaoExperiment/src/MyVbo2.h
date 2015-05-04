//
//  MyVbo2.h
//  baobaoExperiment
//
//  Created by James Kong on 3/5/15.
//
//

#ifndef __baobaoExperiment__MyVbo2__
#define __baobaoExperiment__MyVbo2__

#include <stdio.h>
#include "ofMain.h"
#define GRID_WIDTH  16
#define GRID_HEIGHT 16
#define LENGTH		6
class MyVbo2
{
public:
    void setup();
    void update();
    void draw();
private:
    ofVbo vbo;
    ofVec3f pos[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofVec3f vert[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofVec2f tex_coord[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofVec3f normal[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofFloatColor color[GRID_WIDTH*GRID_HEIGHT*LENGTH];
    ofVec3f center;
    int total;
    int space;
};
#endif /* defined(__baobaoExperiment__MyVbo2__) */
