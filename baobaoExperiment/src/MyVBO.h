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
    
    // helper functions
    void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
    void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c);
    void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d);
//    void addNormals(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
//    void addNormal(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    ofVec3f getVertexFromImg(ofImage& img, int x, int y);
private:
    
    ofMesh mesh;
    ofVboMesh vboMesh;
    ofImage img;
    

};
#endif /* defined(__baobaoExperiment__MyVBO__) */
