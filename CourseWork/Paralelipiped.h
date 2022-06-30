#ifndef Paralelipiped_h
#define Paralelipiped_h
#include "Shape.h"
class Paralelipiped : public Shape
{
public:
    Paralelipiped(float xCenter, float yCenter, float zCenter,
        float xSize, float ySize, float zSize,
        float* diffColor, float* ambiColor, float* specColor)
        : Shape(xCenter, yCenter, zCenter,
            xSize, ySize, zSize,
            specColor, diffColor, ambiColor) { }
    virtual void draw();
};
#endif // !Paralelipiped_h



