#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "House.h"
#include "OBJObject.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    
    static Sphere sphere;
    static House house;

	static OBJObject dragon;
	static OBJObject bear;
	static OBJObject bunny;

    //Feel free to add more member variables as needed
        
};

#endif
