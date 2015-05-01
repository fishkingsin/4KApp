#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(pointLightColor.set("pointLight",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    gui.add(spotLightColor.set("spotLight",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));

    gui.add(directionalLightColor.set("directionLight",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    gui.loadFromFile("settings.xml");
    fbo.allocate(ofGetWidth(), ofGetHeight());
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofSetSmoothLighting(true);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableArbTex();
    ofEnableSmoothing();
    ofEnableSeparateSpecularLight();
//    shader.load("shader");
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( pointLightColor.get());
    
    // specular color, the highlight/shininess color //
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();
    
    spotLight.setDiffuseColor( spotLightColor.get());
    spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    
    // turn the light into spotLight, emit a cone of light //
    spotLight.setSpotlight();
    
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
    spotLight.setSpotlightCutOff( 50 );
    
    // rate of falloff, illumitation decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
    spotLight.setSpotConcentration( 45 );
    
    
    // Directional Lights emit light based on their orientation, regardless of their position //
    directionalLight.setDiffuseColor(directionalLightColor.get());
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );
    material.setShininess( 128 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    
    myVBO.setup();
    radius		= 180.f;
    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
#ifdef USE_PROGRAMMABLE_GL
    // if we are using programmable GL, we load the GLSL version 150 shader pair.
    shader.load("shaders/glossy");
#else
    // if we are using fixed function GL, we load the GLSL version 120 shader pair.
    shader.load("shaders/glossy_120");
#endif
    
    cubemap.loadImages("positive_x.png",
                       "negative_x.png",
                       "positive_y.png",
                       "negative_y.png",
                       "positive_z.png",
                       "negative_z.png");
    ofDisableArbTex();
    bumpmap.loadImage("bumps.png");
    ofEnableArbTex();
}

//--------------------------------------------------------------
void ofApp::update(){
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
                           sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
                           -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    
    spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
    spotLight.setPosition( mouseX, mouseY, 200);
    
    
    pointLight.setDiffuseColor( pointLightColor.get());
    spotLight.setDiffuseColor( spotLightColor.get());
    directionalLight.setDiffuseColor(directionalLightColor.get());
    myVBO.update();
    fbo.begin();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);
    cubemap.bind();
    
    shader.begin();
    shader.setUniform1i("cubeMap", 0);
    shader.setUniformTexture("bumpmap", bumpmap, 1);
    
    material.begin();
    pointLight.enable();
    spotLight.enable();
    directionalLight.enable();
    cam.begin();
    ofClear(0, 0, 0);
    ofPushMatrix();
    
//    ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5,0);
    //    ofRotate(ofGetFrameNum()*0.5, 0, 1, 0);
    //    ofRotate(180, 1, 0, 0);
    
    myVBO.draw();
    //    glutSolidTeapot(ofGetWidth()*0.1);
    
    ofPopMatrix();
    cam.end();
    shader.end();
    
    cubemap.unbind();
    glDisable(GL_DEPTH_TEST);
    material.end();
    // turn off lighting //
    ofDisableLighting();

    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
    if(!isHiddenGui)
    {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
            case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            gui.saveToFile("settings.xml");
            break;
        case 'h':
            isHiddenGui = !isHiddenGui;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    fbo.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
