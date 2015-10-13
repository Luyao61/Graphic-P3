#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"
#include "Vector4.h"

struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
    //Add more members as necessary
};

class OBJObject : public Drawable
{
    
protected:
    
    Vector4 center;

    //Storage vectors
    std::vector<Vector3*>* vertices;
    std::vector<Vector3*>* normals;
    std::vector<Face*>* faces;
    std::vector<Vector3*>* colors;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
public:
    
    OBJObject(std::string);
    OBJObject(OBJObject const &);
    virtual ~OBJObject(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    void moveX();
    void movex();
    void movey();
    void moveY();
    void movez();
    void moveZ();
    void scale(bool);
    void orbit(float);
    
    void reset();
    void spin(float);
    
};

#endif
