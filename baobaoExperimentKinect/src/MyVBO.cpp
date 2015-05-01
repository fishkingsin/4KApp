//
//  MyVBO.cpp
//  baobaoExperiment
//
//  Created by James Kong on 30/4/15.
//
//

#include "MyVBO.h"
void addFace(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a, ofVec3f b, ofVec3f c) {
    
    ofVec3f _normal = ((b - a).cross(c - a)).normalize();
    ofFloatColor _color = ofFloatColor::fromHsb(ofRandom(0.5,0.9),1.0,1.0);
    pos.push_back(a);
    pos.push_back(b);
    pos.push_back(c);
    
    color.push_back(_color);
    color.push_back(_color);
    color.push_back(_color);
    
    normal.push_back(_normal);
    normal.push_back(_normal);
    normal.push_back(_normal);
    
    tex_coord.push_back(ofVec2f(0,0));
    tex_coord.push_back(ofVec2f(1,1));
    tex_coord.push_back(ofVec2f(0,1));
}

//--------------------------------------------------------------
void addFace(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
    addFace(pos,color,normal, tex_coord, a, b, c);
    addFace(pos,color,normal, tex_coord, a, c, d);
}
//--------------------------------------------------------------
void MyVBO::setup(){
    ofEnableAlphaBlending();
    total = 0;
    int width = ofGetWidth();
    int height = ofGetHeight();
    int H_width = width*0.5;
    int H_height = height*0.5;

    int step = 160;
    
    WIDTH = width*1.0/step;
    HEIGHT = height*1.0/step;
    
    
    int row = 0;
    int col = 0;
    for(int y = 0 ; y < height ;y+=step)
    {
        row++;
        for (int x = 0; x < width; x+=step)
        {
            
            
            ofVec3f nw = ofVec3f( x-H_width, y-H_height , 0);
            ofVec3f ne = ofVec3f( x + step -H_width, y-H_height, 0);
            ofVec3f sw = ofVec3f( x-H_width, y + step-H_height, 0);
            ofVec3f se = ofVec3f( x-H_width + step, y + step-H_height, 0);
            if( (col%2==1 && row%2==0) || (col%2==0 && row%2==1) )
            {
                nw = nw.getRotated(90,ofVec3f( x+step*0.5-H_width, y + step*0.5-H_height, 0), ofVec3f(0,0,1));
                ne = ne.getRotated(90,ofVec3f( x+step*0.5-H_width, y + step*0.5-H_height, 0), ofVec3f(0,0,1));
                sw = sw.getRotated(90,ofVec3f( x+step*0.5-H_width, y + step*0.5-H_height, 0), ofVec3f(0,0,1));
                se = se.getRotated(90,ofVec3f( x+step*0.5-H_width, y + step*0.5-H_height, 0), ofVec3f(0,0,1));
            }
//            else if( row%2==0 )
//            {
//                nw = nw.getRotated(180,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                ne = ne.getRotated(180,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                sw = sw.getRotated(180,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                se = se.getRotated(180,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//            }
//            else if( row%2==1 )
//            {
//                nw = nw.getRotated(270,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                ne = ne.getRotated(270,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                sw = sw.getRotated(270,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//                se = se.getRotated(270,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
//            }
            addFace(pos,color,normal,tex_coord, nw,ne,se,sw);
            total+=6;
            col++ ;
        }
    }
    vbo.setVertexData(pos.data(), total, GL_DYNAMIC_DRAW);
    
    vbo.setColorData(color.data(), total, GL_DYNAMIC_DRAW);
    vbo.setNormalData(normal.data(), total, GL_DYNAMIC_DRAW);
    vbo.setTexCoordData(tex_coord.data(), total, GL_DYNAMIC_DRAW);
}

//--------------------------------------------------------------
void MyVBO::update(){
    
    float count = 0;
    float count2 = 0;
    for(int i = 0 ; i< total ;i+=3)
    {
        float a = sin((count-=1.1)+ofGetElapsedTimef())*100;
        float a2 = cos((count2+=0.07))*200;//+ofGetElapsedTimef());
        
        pos[i].z = a;
        pos[i+1].z = a2;
        pos[i+2].z = a;
        
        ofVec3f _normal = ((pos[i+1] - pos[i]).cross(pos[i+2] - pos[i])).normalize();
        
        normal[i] = _normal;
        normal[i+1] = _normal;
        normal[i+2] = _normal;
    }
    
}

//--------------------------------------------------------------
void MyVBO::draw(){
    ofBackground(0);
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    
    
    
    vbo.bind();
    vbo.updateVertexData(pos.data(), total);
    vbo.updateColorData(color.data(), total);
    vbo.updateNormalData(normal.data(), total);
    
    
    for(int i = 0 ; i< total ;i+=3)
    {
        vbo.draw(GL_TRIANGLE_FAN, i,3);
    }
    
    vbo.unbind();
    
    ofPopMatrix();
    
}