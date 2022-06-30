// utils.cpp
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <gl/glut.h>
#include "utils.h"



	// Визначення кольорів:
float ParalelipipedColor[] = { 0.7f, 0.6f, 0.6f };
float diffWhite[] = { 1.0f, 1.0f, 1.0f };
float ambiWhite[] = { 0.8f, 0.8f, 0.8f };
float specWhite[] = { 1.0f, 1.0f, 1.0f };


float diffGray[] = { 0.6f, 0.6f, 0.6f };
float ambiGray[] = { 0.2f, 0.2f, 0.2f };
float specGray[] = { 0.8f, 0.8f, 0.8f };

float Yellow[] = { 0.976, 0.392, 0.203 };




// Випадкове "тасування" одновимірного масиву цілих чисел
void shuffle(int* a, int size)
{
	// Ініціалізація генератору випадкових значень поточним часом:
	srand((unsigned)time(0));
	std::random_shuffle(a, a + size); // алгоритм стандартної бібліотеки шаблонів
}

// Малювання паралелепіпеда
void parallelepiped(float length, float width, float height)
{
	glBegin(GL_QUAD_STRIP);
	//грань 1 || YZ, x<0
	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glVertex3f(-length / 2, width / 2, -height / 2);
	glVertex3f(-length / 2, width / 2, height / 2);

	//грань 2 || ZX, y>0
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, width / 2, height / 2);

	//грань 3 || YZ, x>0
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(length / 2, -width / 2, -height / 2);
	glVertex3f(length / 2, -width / 2, height / 2);

	//грань 4 || ZX y<0
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glEnd();

	glBegin(GL_QUADS);
	//грань 5 || YX, z>0
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glVertex3f(-length / 2, width / 2, height / 2);
	glVertex3f(length / 2, width / 2, height / 2);
	glVertex3f(length / 2, -width / 2, height / 2);

	//грань 6  || YX, z<0
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, -width / 2, -height / 2);
	glEnd();
}

// Відображення рядка тексту вказаним шрифтом у вказаній позиції
void drawString(void* font, const char* text, float x, float y)
{
	if (!text) // нульовий указівник
	{
		return;
	}
	// Встановлення позиції тексту:
	glRasterPos2f(x, y);
	while (*text)
	{
		// Рядок виводиться посимвольно:
		glutBitmapCharacter(font, *text);
		text++;
	}
}
