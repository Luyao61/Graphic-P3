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
    // Add code to rasterize a triangle
}

void Rasterizer::rasterize()
{
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it
    
    // example: draw diagonal line:
    
    //toDraw
    if (toDraw != nullptr) {
        for (int i=0; i< toDraw->vertices->size(); ++i)
        {
            Vector4 temp = rasterizeVertex(toDraw->vertices->at(i)->toVector4(1));
            drawPoint(*temp.ptr(), *(temp.ptr()+1), 1.0, 1.0, 1.0);
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
}

void Rasterizer::keyboard(unsigned char key, int, int)
{
    cerr << "Key pressed: " << key << endl;
}

void Rasterizer::display()
{
    clearBuffer();
    rasterize();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
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

