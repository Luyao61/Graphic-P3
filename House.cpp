//
//  House.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Luyao Zhou on 10/6/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#include "House.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries
int i = 0;

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
    -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
    -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
    4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
    4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
    4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
    -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face
    
    -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
    -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
    4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
    -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
    4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
    
    0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
    0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
    1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
    0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
    0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

// The index data stores the connectivity of the triangles;
// index 0 refers to the first triangle defined above
int indices[] = {
    0,2,3,    0,1,2,      // front face
    4,6,7,    4,5,6,      // left face
    8,10,11,  8,9,10,     // back face
    12,14,15, 12,13,14,   // right face
    16,18,19, 16,17,18,   // top face
    20,22,23, 20,21,22,   // bottom face
    
    24,26,27, 24,25,26,   // grass
    28,29,30,             // front attic wall
    31,33,34, 31,32,33,   // left slope
    35,37,38, 35,36,37,   // right slope
    39,40,41};            // rear attic wall


House::House(void) : Drawable()
{
}

House::~House(void)
{
    //Delete any dynamically allocated memory/objects here
}


void House::draw(DrawData& data)
{

    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());

    glBegin(GL_QUADS);
    
    glColor3f(colors[0], colors[1], colors[2]);
    glVertex3f(vertices[0], vertices[1], vertices[2]);
    
    glColor3f(colors[3], colors[4], colors[5]);
    glVertex3f(vertices[3], vertices[4], vertices[5]);
    
    glColor3f(colors[6], colors[7], colors[8]);
    glVertex3f(vertices[6], vertices[7], vertices[8]);
    
    glColor3f(colors[9], colors[10], colors[11]);
    glVertex3f(vertices[9], vertices[10], vertices[11]);
    
    glColor3f(colors[12], colors[13], colors[14]);
    glVertex3f(vertices[12], vertices[13], vertices[14]);
    
    glColor3f(colors[15], colors[16], colors[17]);
    glVertex3f(vertices[15], vertices[16], vertices[17]);
    
    glColor3f(colors[18], colors[19], colors[20]);
    glVertex3f(vertices[18], vertices[19], vertices[20]);
    
    glColor3f(colors[21], colors[22], colors[23]);
    glVertex3f(vertices[21], vertices[22], vertices[23]);
    
    glColor3f(colors[24], colors[25], colors[26]);
    glVertex3f(vertices[24], vertices[25], vertices[26]);
    
    glColor3f(colors[27], colors[28], colors[29]);
    glVertex3f(vertices[27], vertices[28], vertices[29]);
    
    glColor3f(colors[30], colors[31], colors[32]);
    glVertex3f(vertices[30], vertices[31], vertices[32]);
    
    glColor3f(colors[33], colors[34], colors[35]);
    glVertex3f(vertices[33], vertices[34], vertices[35]);
    
    glColor3f(colors[36], colors[37], colors[38]);
    glVertex3f(vertices[36], vertices[37], vertices[38]);
    
    glColor3f(colors[39], colors[40], colors[41]);
    glVertex3f(vertices[39], vertices[40], vertices[41]);
    
    glColor3f(colors[42], colors[43], colors[44]);
    glVertex3f(vertices[42], vertices[43], vertices[44]);
    
    glColor3f(colors[45], colors[46], colors[47]);
    glVertex3f(vertices[45], vertices[46], vertices[47]);
    
    glColor3f(colors[48], colors[49], colors[50]);
    glVertex3f(vertices[48], vertices[49], vertices[50]);
    
    glColor3f(colors[51], colors[52], colors[53]);
    glVertex3f(vertices[51], vertices[52], vertices[53]);
    
    glColor3f(colors[54], colors[55], colors[56]);
    glVertex3f(vertices[54], vertices[55], vertices[56]);
    
    glColor3f(colors[57], colors[58], colors[59]);
    glVertex3f(vertices[57], vertices[58], vertices[59]);

    glColor3f(colors[60], colors[61], colors[62]);
    glVertex3f(vertices[60], vertices[61], vertices[62]);
    
    glColor3f(colors[63], colors[64], colors[65]);
    glVertex3f(vertices[63], vertices[64], vertices[65]);
    
    glColor3f(colors[66], colors[67], colors[68]);
    glVertex3f(vertices[66], vertices[67], vertices[68]);
    
    glColor3f(colors[69], colors[70], colors[71]);
    glVertex3f(vertices[69], vertices[70], vertices[71]);

    glEnd();

	glBegin(GL_QUADS);
	glColor3f(colors[72], colors[73], colors[74]);
	glVertex3f(vertices[72], vertices[73], vertices[74]);

	glColor3f(colors[75], colors[76], colors[77]);
	glVertex3f(vertices[75], vertices[76], vertices[77]);

	glColor3f(colors[78], colors[79], colors[80]);
	glVertex3f(vertices[78], vertices[79], vertices[80]);

	glColor3f(colors[81], colors[82], colors[83]);
	glVertex3f(vertices[81], vertices[82], vertices[83]);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(colors[84], colors[85], colors[86]);
	glVertex3f(vertices[84], vertices[85], vertices[86]);

	glColor3f(colors[87], colors[88], colors[89]);
	glVertex3f(vertices[87], vertices[88], vertices[89]);

	glColor3f(colors[90], colors[91], colors[92]);
	glVertex3f(vertices[90], vertices[91], vertices[92]);
	glEnd();
    
    
	glBegin(GL_QUADS);
	glColor3f(colors[93], colors[94], colors[95]);
	glVertex3f(vertices[93], vertices[94], vertices[95]);

	glColor3f(colors[96], colors[97], colors[98]);
	glVertex3f(vertices[96], vertices[97], vertices[98]);

	glColor3f(colors[99], colors[100], colors[101]);
	glVertex3f(vertices[99], vertices[100], vertices[101]);

	glColor3f(colors[102], colors[103], colors[104]);
	glVertex3f(vertices[102], vertices[103], vertices[104]);

	glEnd();	glBegin(GL_QUADS);
	glColor3f(colors[105], colors[106], colors[107]);
	glVertex3f(vertices[105], vertices[106], vertices[107]);

	glColor3f(colors[108], colors[109], colors[110]);
	glVertex3f(vertices[108], vertices[109], vertices[110]);

	glColor3f(colors[111], colors[112], colors[113]);
	glVertex3f(vertices[111], vertices[112], vertices[113]);

	glColor3f(colors[114], colors[115], colors[116]);
	glVertex3f(vertices[114], vertices[115], vertices[116]);

	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(colors[117], colors[118], colors[119]);
	glVertex3f(vertices[117], vertices[118], vertices[119]);

	glColor3f(colors[120], colors[121], colors[122]);
	glVertex3f(vertices[120], vertices[121], vertices[122]);

	glColor3f(colors[123], colors[124], colors[125]);
	glVertex3f(vertices[123], vertices[124], vertices[125]);
	glEnd();
    
    glPopMatrix();
    
}