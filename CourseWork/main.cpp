#include<iostream>
#include <gl/glut.h>
#include "GameScene.h"
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

GameScene* Game;
void on_size(int width, int height)
{
	Game->on_size(width, height);
}

void on_paint()
{
	Game->on_paint();
}

void on_mouse(int button, int state, int x, int y)
{
	Game->on_mouse(button, state, x, y);
}

void on_motion(int x, int y)
{
	Game->on_motion(x, y);
}

void on_timer(int value)
{
	Game->on_timer(value);
	glutTimerFunc(25, on_timer, 0); 
}

void on_keyboard(unsigned char key, int x, int y)
{
	Game->on_keyboard(key, x, y);
}

void on_special(int key, int x, int y)
{
	Game->initializeKeys(key);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);         
	Game = new GameScene(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("2048");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glutDisplayFunc(on_paint);
	glutReshapeFunc(on_size);
	glutMotionFunc(on_motion);     
	glutMouseFunc(on_mouse);
	glutKeyboardFunc(on_keyboard);
	glutSpecialFunc(on_special);
	glutTimerFunc(25, on_timer, 0);
	glutMainLoop();               
	delete Game;
	return 0;
}