//
//  MyVboMesh.h
//  baobaoExperiment
//
//  Created by James Kong on 1/5/15.
//
//

#ifndef __baobaoExperiment__MyVboMesh__
#define __baobaoExperiment__MyVboMesh__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAutoReloadedShader.h"
class MyVboMesh
{
public:
    void setup();
    void update();
    void draw();
        ofParameter<bool> isShaderDirty;
private:
    ofVboMesh	mVboBox;
    ofPtr<ofxAutoReloadedShader>	mShdInstanced;
    ofTexture		mTexDepth;
    ofxAssimpModelLoader model;

};
#endif /* defined(__baobaoExperiment__MyVboMesh__) */
