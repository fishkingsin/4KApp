//
//  ShaderToy.h
//  baobaoExperiment
//
//  Created by James Kong on 3/5/15.
//
//

#ifndef __baobaoExperiment__ShaderToy__
#define __baobaoExperiment__ShaderToy__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
class ShaderToy
{
private:
    ofxAutoReloadedShader shader;
    ofTexture texture;
public:
    void setup();
    void update();
    void draw();
    
};
#endif /* defined(__baobaoExperiment__ShaderToy__) */
