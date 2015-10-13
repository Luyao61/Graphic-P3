#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Vector4.h"

class Cube : public Drawable
{
    
public:
    
    float size;
    Vector4 center = * new Vector4(0,0,0,1);
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    void spin(float);
    void moveX();
    void movex();
    void movey();
    void moveY();
    void movez();
    void moveZ();
    void scale(bool);
    void orbit(float);
    
    void reset();
    
};

#endif

