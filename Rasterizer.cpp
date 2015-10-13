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

using namespace std;

struct Color    // generic color
{
    float r,g,b;
};

Rasterizer::Rasterizer(){
    double aspect = window_width/window_height;
    
    d.set(window_width/2, 0, 0, 0,
          0, window_height/2, 0, 0,
          0, 0, 0.5, 0,
          window_width/2, window_height/2, 0.5, 1);
    
    p.set(1/(aspect*tan(FOV/2)), 0, 0, 0,
          0, 1/tan(FOV/2), 0, 0,
          0, 0, (near+far)/(near-far), -1,
          0, 0, 2*near*far/(near-far), 0);
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
    Color clearColor = {0.0, 0.0, 0.0};   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor.r;
        pixels[i*3+1] = clearColor.g;
        pixels[i*3+2] = clearColor.b;
    }
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
    int offset = y*window_width*3 + x*3;
    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
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
    for (int i=0; i<min(window_width,window_height); ++i)
    {
        drawPoint(i, i, 1.0, 0.0, 0.0);
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
    
    glutSwapBuffers();
    
    clearBuffer();
    drawPoint(window_width, window_height, 0, 0, 0);
}


void Rasterizer::updateD(){
    
    d.set(window_width/2, 0, 0, 0,
          0, window_height/2, 0, 0,
          0, 0, 0.5, 0,
          window_width/2, window_height/2, 0.5, 1);
}

void Rasterizer::updateP(){
    double aspect = window_width/window_height;
    p.set(1/(aspect*tan(FOV/2)), 0, 0, 0,
          0, 1/tan(FOV/2), 0, 0,
          0, 0, (near+far)/(near-far), -1,
          0, 0, 2*near*far/(near-far), 0);
}

