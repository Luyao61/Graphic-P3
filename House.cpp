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

// These are the x,y,z coordinates of the houseVertices of the triangles
float houseVertices[] = {
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

// These are the RGB househouseColors corresponding to the houseVertices, in the same order
float househouseColors[] = {
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


    //load vertexIndices into faces;
    //load vertices into vertices
    for (int i = 0 ; i<60; i+=3){
        Face* face = new Face;
        face->vertexIndices[0] = indices[i];
        face->vertexIndices[1] = indices[i+1];
        face->vertexIndices[2] = indices[i+2];

        faces->push_back(face);
    }
    
    for (int i = 0; i<nVerts; i++) {
        vertices->push_back(new Vector3(houseVertices[i*3],houseVertices[i*3+1],houseVertices[i*3+2]));
    }
    
    std::cout<< "HOUSE Done parsing." << std::endl;
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
    
    glColor3f(househouseColors[0], househouseColors[1], househouseColors[2]);
    glVertex3f(houseVertices[0], houseVertices[1], houseVertices[2]);
    
    glColor3f(househouseColors[3], househouseColors[4], househouseColors[5]);
    glVertex3f(houseVertices[3], houseVertices[4], houseVertices[5]);
    
    glColor3f(househouseColors[6], househouseColors[7], househouseColors[8]);
    glVertex3f(houseVertices[6], houseVertices[7], houseVertices[8]);
    
    glColor3f(househouseColors[9], househouseColors[10], househouseColors[11]);
    glVertex3f(houseVertices[9], houseVertices[10], houseVertices[11]);
    
    glColor3f(househouseColors[12], househouseColors[13], househouseColors[14]);
    glVertex3f(houseVertices[12], houseVertices[13], houseVertices[14]);
    
    glColor3f(househouseColors[15], househouseColors[16], househouseColors[17]);
    glVertex3f(houseVertices[15], houseVertices[16], houseVertices[17]);
    
    glColor3f(househouseColors[18], househouseColors[19], househouseColors[20]);
    glVertex3f(houseVertices[18], houseVertices[19], houseVertices[20]);
    
    glColor3f(househouseColors[21], househouseColors[22], househouseColors[23]);
    glVertex3f(houseVertices[21], houseVertices[22], houseVertices[23]);
    
    glColor3f(househouseColors[24], househouseColors[25], househouseColors[26]);
    glVertex3f(houseVertices[24], houseVertices[25], houseVertices[26]);
    
    glColor3f(househouseColors[27], househouseColors[28], househouseColors[29]);
    glVertex3f(houseVertices[27], houseVertices[28], houseVertices[29]);
    
    glColor3f(househouseColors[30], househouseColors[31], househouseColors[32]);
    glVertex3f(houseVertices[30], houseVertices[31], houseVertices[32]);
    
    glColor3f(househouseColors[33], househouseColors[34], househouseColors[35]);
    glVertex3f(houseVertices[33], houseVertices[34], houseVertices[35]);
    
    glColor3f(househouseColors[36], househouseColors[37], househouseColors[38]);
    glVertex3f(houseVertices[36], houseVertices[37], houseVertices[38]);
    
    glColor3f(househouseColors[39], househouseColors[40], househouseColors[41]);
    glVertex3f(houseVertices[39], houseVertices[40], houseVertices[41]);
    
    glColor3f(househouseColors[42], househouseColors[43], househouseColors[44]);
    glVertex3f(houseVertices[42], houseVertices[43], houseVertices[44]);
    
    glColor3f(househouseColors[45], househouseColors[46], househouseColors[47]);
    glVertex3f(houseVertices[45], houseVertices[46], houseVertices[47]);
    
    glColor3f(househouseColors[48], househouseColors[49], househouseColors[50]);
    glVertex3f(houseVertices[48], houseVertices[49], houseVertices[50]);
    
    glColor3f(househouseColors[51], househouseColors[52], househouseColors[53]);
    glVertex3f(houseVertices[51], houseVertices[52], houseVertices[53]);
    
    glColor3f(househouseColors[54], househouseColors[55], househouseColors[56]);
    glVertex3f(houseVertices[54], houseVertices[55], houseVertices[56]);
    
    glColor3f(househouseColors[57], househouseColors[58], househouseColors[59]);
    glVertex3f(houseVertices[57], houseVertices[58], houseVertices[59]);

    glColor3f(househouseColors[60], househouseColors[61], househouseColors[62]);
    glVertex3f(houseVertices[60], houseVertices[61], houseVertices[62]);
    
    glColor3f(househouseColors[63], househouseColors[64], househouseColors[65]);
    glVertex3f(houseVertices[63], houseVertices[64], houseVertices[65]);
    
    glColor3f(househouseColors[66], househouseColors[67], househouseColors[68]);
    glVertex3f(houseVertices[66], houseVertices[67], houseVertices[68]);
    
    glColor3f(househouseColors[69], househouseColors[70], househouseColors[71]);
    glVertex3f(houseVertices[69], houseVertices[70], houseVertices[71]);

    glEnd();

	glBegin(GL_QUADS);
	glColor3f(househouseColors[72], househouseColors[73], househouseColors[74]);
	glVertex3f(houseVertices[72], houseVertices[73], houseVertices[74]);

	glColor3f(househouseColors[75], househouseColors[76], househouseColors[77]);
	glVertex3f(houseVertices[75], houseVertices[76], houseVertices[77]);

	glColor3f(househouseColors[78], househouseColors[79], househouseColors[80]);
	glVertex3f(houseVertices[78], houseVertices[79], houseVertices[80]);

	glColor3f(househouseColors[81], househouseColors[82], househouseColors[83]);
	glVertex3f(houseVertices[81], houseVertices[82], houseVertices[83]);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(househouseColors[84], househouseColors[85], househouseColors[86]);
	glVertex3f(houseVertices[84], houseVertices[85], houseVertices[86]);

	glColor3f(househouseColors[87], househouseColors[88], househouseColors[89]);
	glVertex3f(houseVertices[87], houseVertices[88], houseVertices[89]);

	glColor3f(househouseColors[90], househouseColors[91], househouseColors[92]);
	glVertex3f(houseVertices[90], houseVertices[91], houseVertices[92]);
	glEnd();
    
    
	glBegin(GL_QUADS);
	glColor3f(househouseColors[93], househouseColors[94], househouseColors[95]);
	glVertex3f(houseVertices[93], houseVertices[94], houseVertices[95]);

	glColor3f(househouseColors[96], househouseColors[97], househouseColors[98]);
	glVertex3f(houseVertices[96], houseVertices[97], houseVertices[98]);

	glColor3f(househouseColors[99], househouseColors[100], househouseColors[101]);
	glVertex3f(houseVertices[99], houseVertices[100], houseVertices[101]);

	glColor3f(househouseColors[102], househouseColors[103], househouseColors[104]);
	glVertex3f(houseVertices[102], houseVertices[103], houseVertices[104]);

	glEnd();	glBegin(GL_QUADS);
	glColor3f(househouseColors[105], househouseColors[106], househouseColors[107]);
	glVertex3f(houseVertices[105], houseVertices[106], houseVertices[107]);

	glColor3f(househouseColors[108], househouseColors[109], househouseColors[110]);
	glVertex3f(houseVertices[108], houseVertices[109], houseVertices[110]);

	glColor3f(househouseColors[111], househouseColors[112], househouseColors[113]);
	glVertex3f(houseVertices[111], houseVertices[112], houseVertices[113]);

	glColor3f(househouseColors[114], househouseColors[115], househouseColors[116]);
	glVertex3f(houseVertices[114], houseVertices[115], houseVertices[116]);

	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(househouseColors[117], househouseColors[118], househouseColors[119]);
	glVertex3f(houseVertices[117], houseVertices[118], houseVertices[119]);

	glColor3f(househouseColors[120], househouseColors[121], househouseColors[122]);
	glVertex3f(houseVertices[120], houseVertices[121], houseVertices[122]);

	glColor3f(househouseColors[123], househouseColors[124], househouseColors[125]);
	glVertex3f(houseVertices[123], houseVertices[124], houseVertices[125]);
	glEnd();
    
    glPopMatrix();
    
}