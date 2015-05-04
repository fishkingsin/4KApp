//
//  ShaderToy.cpp
//  baobaoExperiment
//
//  Created by James Kong on 3/5/15.
//
//

#include "ShaderToy.h"
void ShaderToy::setup()
{
    texture.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    shader.load("shaders/shadertoy");
}
void ShaderToy::update()
{
    
}
void ShaderToy::draw()
{
    
    shader.begin();
    shader.setUniform3f("iResolution",640,480,0);
    shader.setUniform2f("iMouse",ofGetMouseX(),ofGetMouseY());
    shader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    shader.setUniform1i("tex", 0);
    shader.setUniform1i("maxHeight", ofGetMouseY());
    texture.draw(texture.getWidth()*-0.5,texture.getHeight()*-0.5);
    shader.end();
}