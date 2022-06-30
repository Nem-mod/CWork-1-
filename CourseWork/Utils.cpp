// utils.cpp
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <gl/glut.h>
#include "utils.h"



	// ���������� �������:
float ParalelipipedColor[] = { 0.7f, 0.6f, 0.6f };
float diffWhite[] = { 1.0f, 1.0f, 1.0f };
float ambiWhite[] = { 0.8f, 0.8f, 0.8f };
float specWhite[] = { 1.0f, 1.0f, 1.0f };


float diffGray[] = { 0.6f, 0.6f, 0.6f };
float ambiGray[] = { 0.2f, 0.2f, 0.2f };
float specGray[] = { 0.8f, 0.8f, 0.8f };

float Yellow[] = { 0.976, 0.392, 0.203 };




// ��������� "���������" ������������ ������ ����� �����
void shuffle(int* a, int size)
{
	// ����������� ���������� ���������� ������� �������� �����:
	srand((unsigned)time(0));
	std::random_shuffle(a, a + size); // �������� ���������� �������� �������
}

// ��������� �������������
void parallelepiped(float length, float width, float height)
{
	glBegin(GL_QUAD_STRIP);
	//����� 1 || YZ, x<0
	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glVertex3f(-length / 2, width / 2, -height / 2);
	glVertex3f(-length / 2, width / 2, height / 2);

	//����� 2 || ZX, y>0
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, width / 2, height / 2);

	//����� 3 || YZ, x>0
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(length / 2, -width / 2, -height / 2);
	glVertex3f(length / 2, -width / 2, height / 2);

	//����� 4 || ZX y<0
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glEnd();

	glBegin(GL_QUADS);
	//����� 5 || YX, z>0
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-length / 2, -width / 2, height / 2);
	glVertex3f(-length / 2, width / 2, height / 2);
	glVertex3f(length / 2, width / 2, height / 2);
	glVertex3f(length / 2, -width / 2, height / 2);

	//����� 6  || YX, z<0
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-length / 2, -width / 2, -height / 2);
	glVertex3f(-length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, width / 2, -height / 2);
	glVertex3f(length / 2, -width / 2, -height / 2);
	glEnd();
}

// ³���������� ����� ������ �������� ������� � ������� �������
void drawString(void* font, const char* text, float x, float y)
{
	if (!text) // �������� ��������
	{
		return;
	}
	// ������������ ������� ������:
	glRasterPos2f(x, y);
	while (*text)
	{
		// ����� ���������� �����������:
		glutBitmapCharacter(font, *text);
		text++;
	}
}
