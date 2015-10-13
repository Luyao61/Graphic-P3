#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
#include "Vector4.h"

class Sphere : public Drawable
{
    
public:
    
    double radius;
    int slices, stacks;
    Vector4 center = *new Vector4(0,0,0,1);

    
    Sphere(double, int, int);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void move();
    virtual void calculateSpeed();
    
    virtual void reset();

    
};

#endif
