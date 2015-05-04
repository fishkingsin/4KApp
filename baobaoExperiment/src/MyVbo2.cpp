//
//  MyVbo2.cpp
//  baobaoExperiment
//
//  Created by James Kong on 3/5/15.
//
//

#include "MyVbo2.h"

void MyVbo2::setup()
{
    center.set(0,0);
    float SIZE = (ofGetWidth()/GRID_WIDTH*1.0f)*0.5;
    space      = sin((1/6.0f)*2*M_PI)*SIZE*2.5;
    float minX = center.x - (GRID_WIDTH * space)*0.5;
    float minY = center.y - (GRID_HEIGHT * space)*0.5;
    float maxWidth = (GRID_WIDTH * space+((GRID_HEIGHT%2)*0.5)*space) + center.x - (GRID_WIDTH * space)*0.5 - minX;
    float maxHeight = (GRID_HEIGHT * space) + center.y - (GRID_HEIGHT * space)*0.5  - minY;
    for (int j=0; j<GRID_HEIGHT; j++) {
        for (int i=0; i<GRID_WIDTH; i++) {
            int x	  = (i * space+((j%2)*0.5)*space) + center.x - (GRID_WIDTH * space)*0.5;//
            int y     = (j * space) + center.y - (GRID_HEIGHT * space)*0.5;
            int z     = 0;
            int index = (j*GRID_WIDTH+i) * LENGTH;
            
            // now we are at each line
            int hex_index = 0;
            
            float rdnSize = 1;//abs( ofRandomf());
            float hue = ofRandom(0.5,1.0);

            
            for (int k=0; k<LENGTH; k++) {
                
                
                pos[index +k].x = x+sin((hex_index/6.0f)*2*M_PI)*SIZE*rdnSize;
                pos[index +k].y = y+cos((hex_index/6.0f)*2*M_PI)*SIZE*rdnSize;
                pos[index +k].z = z;
                
                tex_coord[index +k].x = ofMap(pos[index +k].x,minX , maxWidth , 0,640);
                tex_coord[index +k].y = ofMap(pos[index +k].y,minY , maxHeight, 0,480);
                
                hex_index++;

                color[index + k] = ofFloatColor::fromHsb(hue,1,1);
                vert [index +k ] = pos[index+k];
                
                
                
            }

//            for (int k=0; k<LENGTH; k++) {
//
//                
//                ofVec3f _normal = ((pos[(index +k+1)%LENGTH] -
//                                    pos[index +k]).cross(pos[(index +k+2)%LENGTH] -
//                                                         pos[index +k])).normalize();
//                normal[index +k] = _normal;
//
//            }

            
            
        }
    }
    total = GRID_WIDTH*GRID_HEIGHT*LENGTH;

    vbo.setVertexData(pos, total, GL_DYNAMIC_DRAW);
    vbo.setColorData(color, total, GL_DYNAMIC_DRAW);
    vbo.setTexCoordData(tex_coord, total, GL_DYNAMIC_DRAW);
//    vbo.setNormalData(normal, total, GL_DYNAMIC_DRAW);
}

void MyVbo2::update()
{
    float t = ofGetElapsedTimef()*0.1;
    float noise_density = 0.01;
    float wave_density = 0.01;
    float pow = 100;
    for (int j=0; j<GRID_HEIGHT; j++) {
        for (int i=0; i<GRID_WIDTH; i++) {
            int index = (j*GRID_WIDTH+i) * LENGTH;
//            ofVec3f _normal(0,0,0) ;
            for (int k=0; k<LENGTH; k++) {
                ofVec3f v = ofVec3f(vert[index + k].x,
                                    vert[index + k].y,
                                    (
                                     ofSignedNoise(t, vert[index + k].y*noise_density,vert[index + k].x*noise_density)
                                     +
                                     sin(vert[index + k].x*wave_density+t)+cos(vert[index + k].y*wave_density+t)
                                     ) *pow );
                pos[index + k] = vert[index + k]+v;
//                _normal += pos[index +k].crossed(pos[(index +k+1)%LENGTH]) ;
            }
            
//            _normal.normalize();
//            
//            for (int k=0; k<LENGTH; k++) {
//                normal[index +k] = _normal;
//            }
        }
    }
}

void MyVbo2::draw()
{
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    
    
    vbo.bind();
    vbo.updateVertexData(pos, total);
    vbo.updateColorData(color, total);
    vbo.updateTexCoordData(tex_coord, total);
//    vbo.updateNormalData(normal, total);
    
    for (int i=0; i<GRID_WIDTH; i++) {
        for (int j=0; j<GRID_HEIGHT; j++) {
            int index = (j*GRID_WIDTH+i) * LENGTH;
            //			for(int k = 0; k < LENGTH ; k++)
            {
                //				vbo.draw(GL_LINES, index,LENGTH);
                vbo.draw(GL_TRIANGLE_FAN, index,LENGTH);
            }
        }
    }
    vbo.unbind();
    
    ofPopMatrix();
    
    
}