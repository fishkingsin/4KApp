//
//  MyVboMesh.cpp
//  baobaoExperiment
//
//  Created by James Kong on 1/5/15.
//
//

#include "MyVboMesh.h"
void MyVboMesh::setup()
{
    model.loadModel("triangle.dae");
//    ofBoxPrimitive tmpBox;
    // set the size to be 2 units.
//    tmpBox.set(2);
    
    mVboBox = model.getMesh(0);
    
    // load depth image
    ofDisableArbTex();
    // note that we disable arb tex, meaning we will use normalized texture coordinates,
    // where a texture's x and y coordinate are each expressed as a normalized float.
    // this makes things slightly easier in the shader.
    
    // load the depth image into our texture
    ofLoadImage(mTexDepth, "depth_image.png");
    ofEnableArbTex();
    isShaderDirty = true;

}
void MyVboMesh::update()
{
    if (isShaderDirty){
        
        // only reload the shader if it is 'dirty', i.e. the user has either requested reloading
        // or the 'isShaderDirty' flag has been initialized to true in setup()
        
        // Since we are using an ofPtr around the shader, the old shader will get destroyed
        // automatically as soon as we assign a new shader object to our mShdInstanced.
        
        ofLogNotice() << "Reloading Shader.";
        mShdInstanced = ofPtr<ofShader>(new ofShader());
        // most of the instanced drawing magic happens in the shaders:
#ifdef USE_PROGRAMMABLE_GL
        // if we are using programmable GL, we load the GLSL version 150 shader pair.
        mShdInstanced->load("shaders/instanced.vert", "shaders/instanced.frag");
#else
        // if we are using fixed function GL, we load the GLSL version 120 shader pair.
        mShdInstanced->load("shaders/instanced_120.vert", "shaders/instanced_120.frag");
#endif
        GLint err = glGetError();
        if (err != GL_NO_ERROR){
            ofLogNotice() << "Load Shader came back with GL error:	" << err;
        }
        
        isShaderDirty = false;
    }

}

void MyVboMesh::draw()
{
    ofEnableDepthTest();

    ofSetColor(ofColor::white);
    
    // bind the shader
    mShdInstanced->begin();
    // give the shader access to our texture
    mShdInstanced->setUniformTexture("tex0", mTexDepth, 0);
    // feed the shader a normalized float value that changes over time, to animate things a little
    mShdInstanced->setUniform1f("timeValue", (ofGetElapsedTimeMillis() % 30000) / 30000.0f);
    // we only want to see triangles facing the camera.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // let's draw 128 * 128 == 16384 boxes !
    mVboBox.drawInstanced(OF_MESH_FILL, 128*128);
    
    glDisable(GL_CULL_FACE);
    mShdInstanced->end();
    
    ofDisableDepthTest();
    

}