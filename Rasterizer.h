//
//  Rasterizer.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Luyao Zhou on 10/12/15.
//  Copyright © 2015 RexWest. All rights reserved.
//

#ifndef Rasterizer_hpp
#define Rasterizer_hpp

#include <stdio.h>
#include "Matrix4.h"


class Rasterizer{
private:

protected:

Matrix4 d;   //Viewport Matrix
Matrix4 p;  //Projection Matrix
public:

    Rasterizer(void);
    ~Rasterizer(void);

    void loadData(void);
    void clearBuffer(void);
    void drawPoint(int,int,float,float,float);
    void rasterizeTriangle();
    void rasterize();
    void reshape(int new_width, int new_height);
    void keyboard(unsigned char key, int, int);
    void display();
    void updateD(void);
    void updateP(void);


};

#endif /* Rasterizer_hpp */
