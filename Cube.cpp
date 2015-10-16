#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Vector4.h"
#include "Globals.h"


Cube::Cube(float size) : Drawable()
{
    this->size = size;
    float halfSize = size/2.0;
    
    for (int i = 0; i < 6; i++) {
        Face* face = new Face;
        
        face->vertexIndices[0] = i*4;
        face->vertexIndices[1] = i*4+1;
        face->vertexIndices[2] = i*4+2;
        face->normalIndices[0] = i;
        face->normalIndices[1] = i;
        face->normalIndices[2] = i;
        
        faces->push_back(face);
        
        Face* face1 = new Face;
        
        face1->vertexIndices[0] = i*4+2;
        face1->vertexIndices[1] = i*4+3;
        face1->vertexIndices[2] = i*4;
        face1->normalIndices[0] = i;
        face1->normalIndices[1] = i;
        face1->normalIndices[2] = i;
        faces->push_back(face1);
    }
    
    Vector3 vn1 = *new Vector3(0.0, 0.0, 1.0);
    Vector3 vn2 = *new Vector3(-1.0, 0.0, 0.0);
    Vector3 vn3 = *new Vector3(1.0, 0.0, 0.0);
    Vector3 vn4 = *new Vector3(0.0, 0.0, -1.0);
    Vector3 vn5 = *new Vector3(0.0, 1.0, 0.0);
    Vector3 vn6 = *new Vector3(0.0, -1.0, 0.0);
    normals -> push_back(&vn1);
    normals -> push_back(&vn2);
    normals -> push_back(&vn3);
    normals -> push_back(&vn4);
    normals -> push_back(&vn5);
    normals -> push_back(&vn6);
    
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  halfSize));
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  halfSize));
    
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  -halfSize));
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  -halfSize));
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  halfSize));
    
    vertices -> push_back(new Vector3(halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(halfSize,  halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  halfSize));
    
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  -halfSize));
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  -halfSize));
    
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(halfSize,  halfSize,  halfSize));
    vertices -> push_back(new Vector3(halfSize,  halfSize,  -halfSize));
    vertices -> push_back(new Vector3(-halfSize,  halfSize,  -halfSize));
    
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  -halfSize));
    vertices -> push_back(new Vector3(halfSize,  -halfSize,  halfSize));
    vertices -> push_back(new Vector3(-halfSize,  -halfSize,  halfSize));
    
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with this material
    material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
    
}

void Cube::reset(){
    toWorld.identity();
    center.set(0, 0, 0, 1);
    center.toVector3().print("Cube New Position");
}
//////

void Cube::update(UpdateData& data)
{
    //
}

//self Centered!;
void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    toWorld = toWorld  * rotation;
}
void Cube::orbit(float radians){
    Matrix4 rotation;
    rotation.makeRotateZ(radians);
    
    toWorld = rotation  * toWorld;
    
    center = rotation * center;
    center.toVector3().print("Cube New Position");

}

void Cube::moveX(){
    Matrix4 move;
    move = move.makeTranslate(0.5, 0, 0);
    
    toWorld = move * toWorld;
    
    center = move * center;
    center.toVector3().print("Cube New Position");

}
void Cube::movex(){
    Matrix4 move;
    move = move.makeTranslate(-0.5, 0, 0);
    
    toWorld = move * toWorld;
    center = move * center;
    center.toVector3().print("Cube New Position");

}

void Cube::moveY(){
    Matrix4 move;
    move = move.makeTranslate(0, 0.5, 0);
    
    toWorld = move * toWorld;
    center = move * center;
    center.toVector3().print("Cube New Position");

}
void Cube::movey(){
    Matrix4 move;
    move = move.makeTranslate(0, -0.5, 0);
    
    toWorld = move * toWorld;
    center = move * center;
    center.toVector3().print("Cube New Position");
}
void Cube::moveZ(){
    Matrix4 move;
    move = move.makeTranslate(0, 0, 0.5);
    
    toWorld = move * toWorld;
    center = move * center;
    center.toVector3().print("Cube New Position");

}
void Cube::movez(){
    Matrix4 move;
    move = move.makeTranslate(0, 0, -0.5);
    
    toWorld = move * toWorld;
    center = move * center;
    center.toVector3().print("Cube New Position");
}


void Cube::scale(bool x){
    Matrix4 scale;
    if (x) {
        scale.makeScale(1.01);
    }
    else{
        scale.makeScale(0.99);
    }
    toWorld = toWorld * scale;
    center.toVector3().print("Cube New Position");
}

