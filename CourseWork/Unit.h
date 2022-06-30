#ifndef Unit_h
#define Unit_h
#include "Shape.h"
class Unit : public Shape
{
private:
	unsigned int value;
	unsigned int id;
public:
    Unit(float xCenter, float yCenter, float zCenter,
        float xSize, float ySize, float zSize,
        float* diffColor, float* ambiColor, float* specColor, 
        unsigned int id)
        : Shape(xCenter, yCenter, zCenter,
            xSize, ySize, zSize,
            specColor, diffColor, ambiColor),
        id(id) { }
    virtual void draw();
};
#endif // !Unit_h

