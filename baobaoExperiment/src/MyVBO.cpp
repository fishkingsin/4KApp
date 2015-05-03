//
//  MyVBO.cpp
//  baobaoExperiment
//
//  Created by James Kong on 30/4/15.
//
//

#include "MyVBO.h"
float t;
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
void addFace(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d , bool revert) {
    
    float offset_value = 1.0;
    
    if(revert)
    {
        ofVec3f offset(offset_value,offset_value,0);
        addFace(pos,color,normal, tex_coord, a+offset, b+offset, c+offset);
        addFace(pos,color,normal, tex_coord, a-offset, c-offset, d-offset);
    }
    else{
        ofVec3f offset(-offset_value,offset_value,0);
        addFace(pos,color,normal, tex_coord, a-offset, b-offset, c-offset);
        addFace(pos,color,normal, tex_coord, a+offset, c+offset, d+offset);
    }
}
//--------------------------------------------------------------
void MyVBO::setup(){
//    ofEnableAlphaBlending();
    total = 0;
    float width = ofGetWidth();
    float height = ofGetHeight();
    int H_width = 0;//width*0.5;
    int H_height = 0;//height*0.5;

    int step = 30;
    
    WIDTH = width*1.0/step;
    HEIGHT = height*1.0/step;
    

    int row = 0;
    int col = 0;
    float space = 0.2;
    float step_back_width = space*(width/step)+width*0.5;
    float step_back_height = space*(height/step)+height*0.5;
//    vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for(int _y = 0 ; _y < height ;_y+=step)
    {
        row++;
        for (int _x = 0; _x < width; _x+=step)
        {

            float x = _x + (_x*space) - step_back_width;
            float y = _y + (_y*space) - step_back_height;
            
            ofVec3f nw = ofVec3f( x , y+space , 0);
            ofVec3f ne = ofVec3f( x + step  , y , 0);
            ofVec3f sw = ofVec3f( x , y + step , 0);
            ofVec3f se = ofVec3f( x + step , y + step , 0);
            if( (col%2==0 && row%2==0) ||(col%2==0 && row%2==1) )
            {
                nw = nw.getRotated(90,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
                ne = ne.getRotated(90,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
                sw = sw.getRotated(90,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
                se = se.getRotated(90,ofVec3f( x+step*0.5, y + step*0.5, 0), ofVec3f(0,0,1));
                            addFace(pos,color,normal,tex_coord, nw,ne,se,sw,true);
            }
            else{
                            addFace(pos,color,normal,tex_coord, nw,ne,se,sw,false);
            }
            total+=6;
            col++ ;
        }
    }
    vboMesh.setVertexData(pos.data(), total, GL_DYNAMIC_DRAW);
    
    vboMesh.setColorData(color.data(), total, GL_DYNAMIC_DRAW);
    vboMesh.setNormalData(normal.data(), total, GL_DYNAMIC_DRAW);
    vboMesh.setTexCoordData(tex_coord.data(), total, GL_DYNAMIC_DRAW);
    vert = pos;
}

//--------------------------------------------------------------
void MyVBO::update(){
    
    float count = 0;
    float count2 = 0;
    t = ofGetElapsedTimef()*feq;
    for(int i = 0 ; i< total ;i+=3)
    {
        ofVec3f v1 = ofVec3f(vert[i].x,
                            vert[i].y,
                            (
                             ofSignedNoise(t, vert[i].y*noise_density,vert[i].x*noise_density)
                             +
                             sin(vert[i].x*wave_density+t)+cos(vert[i].y*wave_density+t)
                             ) *pow );

        ofVec3f v2 = ofVec3f(vert[i+1].x,
                             vert[i+1].y,
                             (
                              ofSignedNoise(t, vert[i+1].y*noise_density,vert[i+1].x*noise_density)
                              +
                              sin(vert[i+1].x*wave_density+t)+cos(vert[i+1].y*wave_density+t)
                              )*pow );

        ofVec3f v3 = ofVec3f(vert[i+2].x,
                             vert[i+2].y,
                             (
                              ofSignedNoise(t, vert[i+2].y*noise_density,vert[i+2].x*noise_density)
                              +
                              sin(vert[i+2].x*wave_density+t)+cos(vert[i+2].y*wave_density+t)
                              )*pow );

//        float a = sin((count-=1.1)+ofGetElapsedTimef()+i)*10;
//        float a2 = cos((count2+=0.07)+i)*20;//+ofGetElapsedTimef());
        
        pos[i] = vert[i]+v1;
        pos[i+1] = vert[i+1]+v2;
        pos[i+2] = vert[i+2]+v3;
        
        ofVec3f _normal = ((pos[i+1] - pos[i]).cross(pos[i+2] - pos[i])).normalize();
        
        normal[i] = _normal;
        normal[i+1] = _normal;
        normal[i+2] = _normal;
    }
    if(reload_color)
    {
        for(int i = 0 ; i< total ;i+=3)
        {
            ofFloatColor _color = ofFloatColor::fromHsb(ofRandom(min_hue,max_hue),1.0,1.0);
            color[i] = _color;
            color[i+1] = _color;
            color[i+2] = _color;
        }
        reload_color = false;
    }
    
}

//--------------------------------------------------------------
void MyVBO::draw(){
    ofEnableDepthTest();
    vboMesh.bind();
    vboMesh.updateVertexData(pos.data(), total);
    vboMesh.updateColorData(color.data(), total);
    vboMesh.updateNormalData(normal.data(), total);
    
    
    for(int i = 0 ; i< total ;i+=3)
    {
        vboMesh.draw(GL_TRIANGLE_STRIP, i,3);
    }
    
    vboMesh.unbind();
    ofDisableDepthTest();
}