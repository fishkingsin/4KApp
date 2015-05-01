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
    
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();		// opens first available kinect
    //kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }

    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    nearThreshold = 230;
    farThreshold = 70;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    // start from the front
    bDrawPointCloud = false;
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
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            unsigned char * pix = grayImage.getPixels();
            
            int numPixels = grayImage.getWidth() * grayImage.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
//        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
    }
}
//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    fbo.draw(0,0,ofGetWidth(),ofGetHeight());
    if(bDrawPointCloud) {
        //        easyCam.begin();
        //        drawPointCloud();
        //        easyCam.end();
    } else {
        // draw from the live kinect
        kinect.drawDepth(10, 10, 400, 300);
        kinect.draw(420, 10, 400, 300);
        
        grayImage.draw(10, 320, 400, 300);
        //        contourFinder.draw(10, 320, 400, 300);
        
#ifdef USE_TWO_KINECTS
        kinect2.draw(420, 320, 400, 300);
#endif
    }
    if(!isHiddenGui)
    {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
