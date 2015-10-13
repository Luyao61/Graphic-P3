#include "Sphere.h"
#include "Globals.h"
#include "Window.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
float x = 0.7;
float y = 0.2;
float z = 0.5;
float g = 0.1;  //gravity
//float f = 0.05; //fraction 0.05m/s^2
float s_y, s_x, s_z;


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}


void Sphere::move(){
    Matrix4 displacement;
    //Matrix4 gravity;
    
    calculateSpeed();
    //std::cout << "Ball x: " << *(center.ptr()) << std::endl;
    //std::cout << "Ball y: " << *(center.ptr()+1) << std::endl;
    //std::cout << "Ball z: " << *(center.ptr()+2) << std::endl;

    if (*center.ptr() >= 10 || *center.ptr() <= -10) {
        x = -x * 0.9;
    }
    if (*(center.ptr()+1) >= 10 || *(center.ptr()+1) <= -10) {
        y = -y * 0.9;
    }
    if (*(center.ptr()+2) >= 10 || *(center.ptr()+2) <= -10) {
        z = -z * 0.9;
    }

    displacement = displacement.makeTranslate(x, s_y, z);
    //gravity = gravity.makeTranslate(0, g, 0);

    toWorld = displacement * toWorld;
    center = displacement * center;
    
    //toWorld = gravity * toWorld;
    //center = gravity * center;
}

void Sphere::reset(){
    toWorld.identity();
    center.set(0, 0, 0, 1);
    x = 0.7;
    y = 0.9;
    z = 0.5;

}


void Sphere::calculateSpeed(){
    s_y = y  + 0.5 * (-g);
    y = y + (-g)*y;
}




