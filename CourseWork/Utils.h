// utils.h
#ifndef utils_h
#define utils_h


extern float ParalelipipedColor[];
extern float diffWhite[];
extern float ambiWhite[];
extern float specWhite[];


extern float diffGray[];
extern float ambiGray[];
extern float specGray[];


extern float Yellow[];

const float shininess = 64; 

void shuffle(int* a, int size);

void parallelepiped(float length, float width, float height);

void drawString(void* font, const char* text, float x, float y);


#endif