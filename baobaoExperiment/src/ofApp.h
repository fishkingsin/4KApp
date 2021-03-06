#pragma once
// #define USE_PROGRAMMABLE_GL
#include "ofMain.h"
#include "GLUT/glut.h"
#include "ofxAutoReloadedShader.h"
#include "MyVBO.h"
#include "MyVboMesh.h"
#include "ofxGui.h"
#include "ofxCubeMap.h"
#include "ShaderToy.h"
#include "MyVbo2.h"
#include "ofxGameCamera.h"
#include "ofxPostProcessing.h"
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void onPointLightColorChanged(ofColor& pointLightColor);
    void onSpotLightColorChanged(ofColor& spotLightColor);
    void onDirectionalLightColorChanged(ofColor& directionalLightColor);
    ofxGameCamera cam;
    ofLight pointLight;
    ofLight spotLight;
    ofLight directionalLight;
    ofMaterial material;
    MyVBO myVBO;
    MyVboMesh myVboMesh;
    MyVbo2 myVbo2;
//    ofFbo fbo;
    ofVec3f center;
    float radius;
    ofxPanel gui;
    bool isHiddenGui;
    ofParameter<ofColor>pointLightColor;
    ofParameter<ofColor>spotLightColor;
    ofParameter<ofColor>directionalLightColor;
    ofParameter<bool>useShader;
    ofParameter<bool>useFbo;
    ofParameter<int>mode;
    
    ofxAutoReloadedShader shader;
    ofxCubeMap cubemap;
    ofImage bumpmap;
    
    ShaderToy shaderToy;
    
    ofxPostProcessing post;
};
