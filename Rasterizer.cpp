//
//  Rasterizer.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Luyao Zhou on 10/12/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "Rasterizer.h"
#include "Globals.h"

#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float FOV = 60;
static float near = 1.0;
static float far = 1000.0;
Drawable *toDraw;
float *zbuffer = new float[window_width * window_height];

bool colorP3isEmpty = true;
bool debugMode = false;

using namespace std;

Rasterizer::Rasterizer() : Drawable(){
    d.makeViewport(0, window_width, 0, window_height);
    p.makePerspectiveProjection(FOV, window_width, window_height, near, far);
}

Rasterizer::~Rasterizer(){
    
}

void Rasterizer::loadData()
{
    // put code to load data model here
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
    Color clearColor = *new Color(0,0,0);   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = *clearColor.ptr();
        pixels[i*3+1] = *(clearColor.ptr()+1);
        pixels[i*3+2] = *(clearColor.ptr()+2);
        
        //clear zbuffer
        zbuffer[i] = 1.0;
    }
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
    int offset = y*window_width*3 + x*3;
    if ( x>=0 && x<= window_width && y>=0 && y <= window_height) {
        pixels[offset]   = r;
        pixels[offset+1] = g;
        pixels[offset+2] = b;
    }
}

Vector4 Rasterizer:: rasterizeVertex(Vector4 point){
        point = this->toWorld * point;
        
        point = Globals::camera.getInverseMatrix() * point;
        
        point = p * point;
        
        point = point.dehomogenize();
        
        point = d * point;

    
    return point;
}


void Rasterizer::rasterizeTriangle()
{
    float nAx, nAy, nAz, nBx, nBy, nBz, nCx, nCy, nCz;
    // Add code to rasterize a triangle
    for (int i = 0; i< this->faces->size(); i++) {
        Vector3 a = *vertices -> at(faces->at(i)->vertexIndices[0]);
        Vector3 b = *vertices -> at(faces->at(i)->vertexIndices[1]);
        Vector3 c = *vertices -> at(faces->at(i)->vertexIndices[2]);
        Vector4 newA = rasterizeVertex(a.toVector4(1));
        Vector4 newB = rasterizeVertex(b.toVector4(1));
        Vector4 newC = rasterizeVertex(c.toVector4(1));
        if (normals->size() != 0) {
            Vector3 normalA = *normals -> at(faces->at(i)->normalIndices[0]);
            Vector3 normalB = *normals -> at(faces->at(i)->normalIndices[1]);
            Vector3 normalC = *normals -> at(faces->at(i)->normalIndices[2]);
            
            normalA = normalA*0.5 + *new Vector3(0.5,0.5,0.5);
            normalB = normalB*0.5 + *new Vector3(0.5,0.5,0.5);
            normalB = normalB*0.5 + *new Vector3(0.5,0.5,0.5);
            
            nAx = *normalA.ptr();
            nBx = *normalB.ptr();
            nCx = *normalC.ptr();
            nAy = *(normalA.ptr()+1);
            nBy = *(normalB.ptr()+1);
            nCy = *(normalC.ptr()+1);
            nAz = *(normalA.ptr()+2);
            nBz = *(normalB.ptr()+2);
            nCz = *(normalC.ptr()+2);
        }
        
        float ax = *newA.ptr();
        float ay = *(newA.ptr()+1);
        float bx = *newB.ptr();
        float by = *(newB.ptr()+1);
        float cx = *newC.ptr();
        float cy = *(newC.ptr()+1);

        int minX = min(min(ax,bx),cx);
        int minY = min(min(ay,by),cy);
        
        int maxX = max(max(ax,bx),cx);
        int maxY = max(max(ay,by),cy);
        
        if (minX<0) {
            minX = 0;
        }
        if (maxX > window_width) {
            maxX = window_width - 1;
        }
        if (minY<0) {
            minY = 0;
        }
        if (maxY > window_width) {
            maxY = window_width - 1;
        }
        if (colorP3isEmpty){
            colorP3->push_back(new Color((rand()%256)/(float)256,(rand()%256)/(float)256,(rand()%256)/(float)256));
        }
        
        for (int m = minX; m<=maxX; m++) {
            for ( int n = minY; n<=maxY; n++) {
                
                float v0x = cx-ax;
                float v0y = cy-ay;
                float v1x = bx-ax;
                float v1y = by-ay;
                float v2x = m-ax;
                float v2y = n-ay;
                float dot00 = v0x*v0x + v0y*v0y;
                float dot01 = v0x*v1x + v0y*v1y;
                float dot02 = v0x*v2x + v0y*v2y;
                float dot11 = v1x*v1x + v1y*v1y;
                float dot12 = v1x*v2x + v1y*v2y;
                float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
                float u = (dot11 * dot02 - dot01 * dot12) * invDenom; //
                float v = (dot00 * dot12 - dot01 * dot02) * invDenom; //beta
                
                float z = (1-u-v) * *(newA.ptr()+2) + v * *(newB.ptr()+2) + u * *(newC.ptr()+2);

                if ( (u >= 0) && (v >= 0) && (u + v <= 1) ) {
                    if(renderMode == 1){
                        drawPoint(m, n, *colorP3->at(i)->ptr(), *(colorP3->at(i)->ptr()+1), *(colorP3->at(i)->ptr()+2));
                    }else if(renderMode==2 || renderMode == 3 || renderMode == 4){
                        if (z<zbuffer[m+n*window_width] && z>0) {
                            if (renderMode == 2) {
                                drawPoint(m, n, *colorP3->at(i)->ptr(), *(colorP3->at(i)->ptr()+1), *(colorP3->at(i)->ptr()+2));
                                zbuffer[m+n*window_width] = z;
                            }
                            else if(renderMode == 3){
                                if(normals -> size() != 0){
                                    Vector3 normalA = *normals -> at(faces->at(i)->normalIndices[0]);
                                    Vector3 normalB = *normals -> at(faces->at(i)->normalIndices[1]);
                                    Vector3 normalC = *normals -> at(faces->at(i)->normalIndices[2]);
                                    normalA = normalA.normalize();
                                    normalB = normalB.normalize();
                                    normalC = normalC.normalize();
                                    normalA = normalA*0.5 + *new Vector3(0.5,0.5,0.5);
                                    normalB = normalB*0.5 + *new Vector3(0.5,0.5,0.5);
                                    normalC = normalC*0.5 + *new Vector3(0.5,0.5,0.5);
                                    
                                    nAx = *normalA.ptr();
                                    nBx = *normalB.ptr();
                                    nCx = *normalC.ptr();
                                    nAy = *(normalA.ptr()+1);
                                    nBy = *(normalB.ptr()+1);
                                    nCy = *(normalC.ptr()+1);
                                    nAz = *(normalA.ptr()+2);
                                    nBz = *(normalB.ptr()+2);
                                    nCz = *(normalC.ptr()+2);
                                    
                                    float r =(1-u-v) * nAx + v * nBx + u * nCx;
                                    float g =(1-u-v) * nAy + v * nBy + u * nCy;
                                    float b =(1-u-v) * nAz + v * nBz + u * nCz;
                                    
                                    drawPoint(m, n, r,g,b);
                                    zbuffer[m+n*window_width] = z;
                                }
                            }
                            else if (renderMode == 4){ //EXTRA CREDIT
                                //colorP3.at(i);
                                
                                Vector3 cameraPos = Globals::camera.e;
                                Vector3 lightPos = Globals::light.position.toVector3();
                                
                                Vector3 cameraPos_a = cameraPos - a;
                                Vector3 lightPos_a = lightPos - a;
                                
                                Vector3 cameraPos_b = cameraPos - b;
                                Vector3 lightPos_b = lightPos - b;
                                
                                Vector3 cameraPos_c = cameraPos - c;
                                Vector3 lightPos_c = lightPos - c;
                                
                                
                                cameraPos_a = cameraPos_a.normalize();
                                lightPos_a = lightPos_a.normalize();

                                
                                cameraPos_b = cameraPos_b.normalize();
                                lightPos_b = lightPos_b.normalize();

                                
                                cameraPos_c = cameraPos_c.normalize();
                                lightPos_c = lightPos_c.normalize();

                                Vector3 h_a, h_b, h_c;
                                
                                h_a = cameraPos_a.add(lightPos_a);
                                h_a = h_a.multiply(1/h_a.magnitude());
                                
                                h_b = cameraPos_b.add(lightPos_b);
                                h_b = h_b.multiply(1/h_b.magnitude());
                                
                                h_c = cameraPos_c.add(lightPos_c);
                                h_c = h_c.multiply(1/h_c.magnitude());
                                
                                Vector3 normalA, normalB, normalC;
                                if(normals -> size() != 0){
                                    normalA = *normals -> at(faces->at(i)->normalIndices[0]);
                                    normalB = *normals -> at(faces->at(i)->normalIndices[1]);
                                    normalC = *normals -> at(faces->at(i)->normalIndices[2]);
                                    normalA = normalA.normalize();
                                    normalB = normalB.normalize();
                                    normalC = normalC.normalize();
                                }
                                
                                /*
                                Vector3 specular;
                                specular.set(*Globals::light.specularColor.ptr(),
                                             *(Globals::light.specularColor.ptr()+1),
                                             *(Globals::light.specularColor.ptr()+2));
                                
                                Vector3 diffuse;
                                diffuse.set(*Globals::light.diffuseColor.ptr(),
                                             *(Globals::light.diffuseColor.ptr()+1),
                                             *(Globals::light.diffuseColor.ptr()+2));
                                
                                */
                                Vector3 specular = *new Vector3(1,1,1);
                                Vector3 diffuse = *new Vector3(1,1,1);
                                
                                Vector3 original_Color;
                                original_Color.set(*colorP3->at(i)->ptr(), *(colorP3->at(i)->ptr()+1), *(colorP3->at(i)->ptr()+2));
                                
                                Vector3 white, zero;
                                white.set(1,1,1);
                                zero.set(0,0,0);
                                
                                
                                Vector3 newColor_A, newColor_B, newColor_C;
                                if (normalA.dot(lightPos_a) < 0) {
                                    newColor_A = diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_A = diffuse.multiply(normalA.dot(lightPos_a))*original_Color;
                                }
                                
                                if (normalA.dot(h_a) < 0) {
                                    newColor_A = newColor_A + diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_A = newColor_A + diffuse.multiply(pow(normalA.dot(h_a),10))*original_Color;
                                }
                                

                                if (normalB.dot(lightPos_b) < 0) {
                                    newColor_B = diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_B = diffuse.multiply(normalB.dot(lightPos_b))*original_Color;
                                }
                                
                                if (normalB.dot(h_b) < 0) {
                                    newColor_B = newColor_B + diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_B = newColor_B + diffuse.multiply(pow(normalB.dot(h_b),10))*original_Color;
                                }
                                
                                
                                if (normalC.dot(lightPos_c) < 0) {
                                    newColor_C = diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_C = diffuse.multiply(normalC.dot(lightPos_c))*original_Color;
                                }
                                
                                if (normalC.dot(h_c) < 0) {
                                    newColor_C = newColor_C + diffuse.multiply(0)*original_Color;
                                }else{
                                    newColor_C = newColor_C + diffuse.multiply(pow(normalC.dot(h_c),10))*original_Color;
                                }

                                
                                newColor_A = newColor_A.normalize();
                                newColor_B = newColor_B.normalize();
                                newColor_C = newColor_C.normalize();
                                newColor_A = newColor_A*0.5 + *new Vector3(0.5,0.5,0.5);
                                newColor_B = newColor_B*0.5 + *new Vector3(0.5,0.5,0.5);
                                newColor_C = newColor_C*0.5 + *new Vector3(0.5,0.5,0.5);
                                
                                nAx = *newColor_A.ptr();
                                nBx = *newColor_B.ptr();
                                nCx = *newColor_C.ptr();
                                nAy = *(newColor_A.ptr()+1);
                                nBy = *(newColor_B.ptr()+1);
                                nCy = *(newColor_C.ptr()+1);
                                nAz = *(newColor_A.ptr()+2);
                                nBz = *(newColor_B.ptr()+2);
                                nCz = *(newColor_C.ptr()+2);
                                
                                float r =(1-u-v) * nAx + v * nBx + u * nCx;
                                float g =(1-u-v) * nAy + v * nBy + u * nCy;
                                float b =(1-u-v) * nAz + v * nBz + u * nCz;
                                
                                drawPoint(m, n, r, g, b);
                            }
                        }
                    }
                }
                if (debugMode) {
                    //debug mode;
                    if (m == minX || m == maxX || n == minY || n == maxY) {
                        Color colorRed = *new Color(0xff0000ff);
                        drawPoint(m, n, *colorRed.ptr(), *(colorRed.ptr()+1), *(colorRed.ptr()+2));
                    }

                }
            }
        }


    }
    colorP3isEmpty = false;
}

void Rasterizer::rasterize()
{
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it
    
    // example: draw diagonal line:
    

    if (toDraw != nullptr) {
        this->vertices = toDraw->vertices;
        this->normals = toDraw->normals;
        this->faces = toDraw->faces;
        this->colors = toDraw->colors;
        
        if (renderMode == 0) {
            for (int i=0; i< this->vertices->size(); ++i)
            {
                Vector4 temp = rasterizeVertex(toDraw->vertices->at(i)->toVector4(1));
                drawPoint(*temp.ptr(), *(temp.ptr()+1), 1.0, 1.0, 1.0);
            }
        }
        else if(renderMode == 1 || renderMode == 2 || renderMode ==3 || renderMode == 4){
            //TODO::
            rasterizeTriangle();
        }
    }
}

// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    pixels = new float[window_width * window_height * 3];
    updateD();
    updateP();
    zbuffer = new float[window_height*window_width];
}

void Rasterizer::keyboard(unsigned char key, int, int)
{
    if (key == '-') {
        renderMode--;
        if (renderMode < 0) {
            renderMode = 0;
        }
    }
    else if (key == '+'){
        renderMode++;
        if (renderMode > 4) {
            renderMode = 4;
        }
    }
    else if(key == 'd'){
        debugMode = !debugMode;
        //std::cout <<"DEBUG MODE: "<< debugMode<<std::endl;
    }
    else if(key == GLUT_KEY_F1 || key == GLUT_KEY_F2
            || key == GLUT_KEY_F3 || key == GLUT_KEY_F4
            || key == GLUT_KEY_F5 || key == GLUT_KEY_F6){
        
        this->vertices = new std::vector<Vector3*>();
        this->normals = new std::vector<Vector3*>();
        this->faces = new std::vector<Face*>();
        this->colors = new std::vector<Vector3*>();

        this->vertices = toDraw->vertices;
        this->normals = toDraw->normals;
        this->faces = toDraw->faces;
        this->colors = toDraw->colors;
        
        colorP3isEmpty = true;
        this->colorP3 = new std::vector<Color*>();
        this->reset();
    }
}

void Rasterizer::display()
{
    clearBuffer();
    rasterize();
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    
    //glutSwapBuffers();
}

void Rasterizer::updateD(){
    d.makeViewport(0, window_width, 0, window_height);
}

void Rasterizer::updateP(){
    p.makePerspectiveProjection(FOV, window_width, window_height, near, far);
}

