#define _CRT_SECURE_NO_WARNINGS

#include "GameScene.h"
#include "Paralelipiped.h"
#include "Utils.h"
#include "Unit.h"
#include "time.h"
#include <math.h>
#include <string>
#include <glut.h>
#include <stdio.h>


void* font = GLUT_BITMAP_TIMES_ROMAN_24;

GameScene::GameScene(int WIDTH, int HEIGHT) : width(WIDTH), height(HEIGHT)
{
	distZ = -6;
	angleX = 0;
	angleY = 90;
	//
	StopGame = 0;
	BoolLose = 0;
	BoolStart = 0;
	int_score = 0;
	sec = 0;

	field.push_back(new Paralelipiped(0.0, 0.0, 0.0, CHS + 0.1, 0.1, CHS + 0.1, ParalelipipedColor, ParalelipipedColor, ParalelipipedColor));
	field.push_back(new Paralelipiped(0, 0.0, CHS/2 + 0.1, CHS + 0.3, 0.5,  0.1, ParalelipipedColor, ParalelipipedColor, ParalelipipedColor));
	field.push_back(new Paralelipiped(0, 0.0, -CHS / 2 - 0.1, CHS + 0.3, 0.5, 0.1, ParalelipipedColor, ParalelipipedColor, ParalelipipedColor));
	field.push_back(new Paralelipiped(CHS / 2 + 0.1, 0.0, 0, 0.1, 0.5, CHS + 0.1, ParalelipipedColor, ParalelipipedColor, ParalelipipedColor));
	field.push_back(new Paralelipiped(-CHS / 2 - 0.1, 0.0, 0,  0.1, 0.5, CHS + 0.1, ParalelipipedColor, ParalelipipedColor, ParalelipipedColor));

}

void renderBitmapString(
	float x,
	float y,
	float z,
	void* font,
	char* string) {
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
// Initializetion of chress (logic game matrix)
void GameScene::initialize()
{
	if (wstep && BoolLose != 1)
	{
		shapes.clear();

		for (int i = 0; i < CHS; i++)
		{
			for (int j = 0; j < CHS; j++)
			{
				if (chress[i][j] > 0)
				{
					int nb = pow(2,chress[i][j]);
					std::string sbuf = std::to_string(nb);
					char* buffer = new char[sbuf.length()];
					strcpy(buffer, sbuf.c_str());
					renderBitmapString(allocX(j), 0.5, allocZ(i), (void*)font, buffer);
					/*float cy = 1.0 - float(chress[i][j])/10;
					float cYellow[] = { 0.98f, cy, 0.2} ;*/
					shapes.push_back(new Unit(allocX(j), 0, allocZ(i), unitSize, unitSize / 2, unitSize, Yellow, Yellow, Yellow, 0));
				}
			}
		}
		wstep = false;

	}

	for (int i = 0; i < CHS; i++)
	{
		for (int j = 0; j < CHS; j++)
		{
			if (chress[i][j] > 0)
			{
				int nb = pow(2, chress[i][j]);
				std::string sbuf = std::to_string(nb);
				char* buffer = new char[sbuf.length()];
				strcpy(buffer, sbuf.c_str());
				renderBitmapString(allocX(j), 0.3, allocZ(i), (void*)font, buffer);
				renderBitmapString(allocX(j), -0.3, allocZ(i), (void*)font, buffer);
			}
		}
	}
}

// Callbacks
int tick = 0;


void GameScene::on_paint()
{
	char text[128]; 					
	if (StopGame)
	{
		sprintf(text, "Game over. Time: %d sec.   F5 - Restart game   Esc - Exit", sec);
	}
	else
	{
		sprintf(text, "  Score: %d     Time: %d sec.  F5 - Restart game   Esc - Exit", int_score, sec);
	}

	glViewport(0, 0, width, height);

	float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	if (true)
	{
		glClearColor(0.98, 0.97, 0.93, 0);
	}
	

	// Очищуємо буфери:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0, 0, 0); // BLACK 
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
	glPopMatrix();

	// Enable matrix of projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Create perspective for camera 
	gluPerspective(60, width / height, 1, 100);

	// Enable matrix of  modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, distZ);	// locate 

	glRotatef(angleX, 0.0f, 1.0f, 0.0f); 
	glRotatef(angleY, 1.0f, 0.0f, 0.0f); 
	glEnable(GL_DEPTH_TEST);	// Enable depth test and lightning
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Draw
	
	initialize();
	for (int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->draw();
	}
	for (int i = 0; i < field.size(); i++)
	{
		field[i]->draw();
	}
	
	
	
	// Unable depth test and lightning
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	// Display a window
	glutSwapBuffers(); 
}
void GameScene::on_mouse(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if ((state == GLUT_UP)) // Key is unable
	{
	
		this->button = -1;  
		return;
	}
	this->button = button;  
	if (BoolLose)
	{
		return;
	}
}
void GameScene::on_motion(int x, int y)
{
	switch (button)
	{
	case 0: // Left mouse key

		break;
	case 2: // Right mouse key
		angleX += x - mouseX;
		angleY += y - mouseY;
		mouseX = x;
		mouseY = y;
		break;
	};
}
void GameScene::on_timer(int value)
{
	tick++;
	if (tick >= 40)
	{
		if (!BoolLose)
		{
			sec++;
		}
		tick = 0;   
	}
	on_paint();  
}
void GameScene::on_size(int width, int height)
{
	this->width = width;
	if (height == 0)
		height = 1;
	this->height = height;
}
void GameScene::on_keyboard(unsigned char key, int x, int y)
{

	if (key == 119)
	{
		if (distZ <= -5)
			distZ += 0.1;
	}
	if (key == 115)
	{
		if (distZ >= -10)
			distZ -= 0.1;
	}
	if (key == 27)
	{
		exit(0);
	}
}

// Game controllers

void GameScene::restart()
{

	//chress become 0
	for (int y = 0; y < CHS; y++) {
		for (int x = 0; x < CHS; x++) {
			chress[x][y] = 0;
		}
	}
	sec = 0;//time reset
	randNum();
	int_score = 0;//refresh score
	StopGame = 0;//go on game
	BoolStart = 0;//timer don't run
	wstep = true;
}
void GameScene::lose() {

	BoolLose = 1; // to assume BoolLose is 0 (lose)

	//when chress is all != 0
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (chress[x][y] == 0) {
				BoolLose = 0;	//go on game
				break;
			}
		}
	}
	if (BoolLose == 1) {
		StopGame = 1;
	}


}//end p
void GameScene::randNum() {
	// random 1 chess is 1
	srand(time(NULL));
	bool Rand = 1;
	do {
		float a, b;
		a = rand() % 4;//a random eqully
		b = (rand() % 4);

		if (chress[(int)a][(int)b] == 0)
		{
			chress[(int)a][(int)b] = 1;
			Rand = 0;
		}
	} while (Rand == 1);

}

//counting score
void GameScene::countscore(int int_tempscore) {
	if (int_score <= 9999) { //to avoid bug

		for (int i = 0; i < int_tempscore; i++)
		{
			int_score += pow(2, i+2);
		}
	}
}


// Move
void GameScene::initializeKeys(int key)
{
	if (key == GLUT_KEY_UP)
	{
		//up
		up();
	}

	if (key == GLUT_KEY_LEFT)
	{
		//left
		left();
	}

	if (key == GLUT_KEY_RIGHT)
	{
		//RIGHT
		right();
	}

	if (key == GLUT_KEY_DOWN)
	{
		//down
		down();
	}
	if (key == GLUT_KEY_F5)
	{
		//restart game
		restart();
	}

}
int GameScene::changeChress(int TwoChressNum) {
	//change Chress texture
	return (TwoChressNum != 100) ? (TwoChressNum + 1) : 1;

}
void GameScene::right()
{
	BoolStart = 1;// allow time run

	if (StopGame != 1) {
		//running order: chress order arrange,  chk chress sum, chress order arrange

		int i = 0;

		while (i <= 1) {

			//chress order arrange
			for (int x = 0; x < CHS; x++) //x
			{
				for (int j = CHS-1; j > 0; j--)//check y four times
				{
					for (int y = CHS-1; y > 0; y--)//y
					{

						if (chress[x][y] == 0)
						{

							chress[x][y] = chress[x][y - 1];
							chress[x][y - 1] = 0;

						}
					}
				}
			}


			if (i == 0) {
				//chk chress sum
				for (int x = 0; x < CHS; x++)
				{
					for (int y = CHS-1; y > 0; y--)
					{
						if (chress[x][y] == chress[x][y - 1] && chress[x][y] != 0)
						{
							chress[x][y - 1] = 0;
							chress[x][y] = changeChress(chress[x][y]);
							int_tempscore++;
						}
					}

				}
			}

			i++;
		}//end while

		countscore(int_tempscore);// count score with bonus
		int_tempscore = 0;//refresh


	}
	lose();//determine lose

	//random chress
	if (StopGame != 1)
	{
		randNum();
	}
	wstep = true;

}
void GameScene::up()
{
	BoolStart = 1;// allow time run

	//sound 

	if (StopGame != 1) {

		//running order: chress order arrange,  chk chress sum, chress order arrange
		int i = 0;

		while (i <= 1) {

			//left

			for (int y = 0; y < CHS; y++)
			{
				for (int j = 0; j < CHS; j++) {
					for (int x = 0; x < CHS-1; x++)
					{
						if (chress[x][y] == 0)
						{
							chress[x][y] = chress[x + 1][y];
							chress[x + 1][y] = 0;
						}
					}
				}
			}

			if (i == 0)
			{

				//chk

				for (int y = 0; y < CHS; y++)
				{
					for (int x = 0; x < CHS-1; x++)
					{
						if (chress[x][y] == chress[x + 1][y] && chress[x][y] != 0)
						{
							chress[x + 1][y] = 0;
							chress[x][y] = changeChress(chress[x][y]);
							int_tempscore++;
						}
					}
				}
			}
			i++;

		}

		countscore(int_tempscore);// count score with bonus
		int_tempscore = 0;//refresh

	}
	lose();
	//random chress
	if (StopGame != 1)
	{
		randNum();
	}
	wstep = true;

}
void GameScene::down()
{
	BoolStart = 1;// allow time run

	//sound 

	if (StopGame != 1) {
		//btext.text = "RIGHT";

		//running order: chress order arrange,  chk chress sum, chress order arrange
		int i = 0;

		while (i <= 1) {
			//chress order arrange
			for (int y = 0; y < CHS; y++)
			{
				for (int j = 0; j < CHS; j++) {
					for (int x = CHS-1; x > 0; x--)
					{
						if (chress[x][y] == 0)
						{
							chress[x][y] = chress[x - 1][y];
							chress[x - 1][y] = 0;
						}
					}
				}
			}
			//chk chress sum
			if (i == 0) {
				for (int y = 0; y < 4; y++)
				{
					for (int x = 3; x > 0; x--)
					{
						if (chress[x][y] == chress[x - 1][y] && chress[x][y] != 0)
						{
							chress[x][y] = 0;
							chress[x - 1][y] = changeChress(chress[x - 1][y]);
							int_tempscore++;
						}
					}
				}
			}

			i++;
		}//end while

		countscore(int_tempscore);// count score with bonus
		int_tempscore = 0;//refresh


	}
	lose();

	//random chress
	if (StopGame != 1)
	{
		randNum();
	}
	wstep = true;

}
void GameScene::left()
{
	BoolStart = 1;// allow time run

	//sound 


	if (StopGame != 1)
	{
		//down 

		//running order: chress order arrange,  chk chress sum, chress order arrange
		int i = 0;

		while (i <= 1) {
			//chress order arrange
			for (int x = 0; x < CHS; x++)
			{
				for (int j = 0; j < CHS-1; j++)
				{
					for (int y = 0; y < CHS-1; y++)
					{
						if (chress[x][y] == 0)
						{
							chress[x][y] = chress[x][y + 1];
							chress[x][y + 1] = 0;
						}
					}
				}
			}
			if (i == 0)
			{
				//chk chress sum
				for (int x = 0; x < CHS; x++)
				{
					for (int y = 0; y < CHS; y++)
					{
						if (chress[x][y] == chress[x][y + 1] && chress[x][y] != 0)
						{
							chress[x][y + 1] = 0;
							chress[x][y] = changeChress(chress[x][y]);
							int_tempscore++;
						}
					}

				}
			}

			i++;

		}//end while

		countscore(int_tempscore);// count score with bonus
		int_tempscore = 0;//refresh

	}
	lose();

	//random chress
	if (StopGame != 1)
	{
		randNum();
	}
	wstep = true;

}


// Amount location of index x
float GameScene::allocX(int i)
{
	return   xStep * i - (CHS - 1) * xStep / 2;
}

// Amount location of index z
float GameScene::allocZ(int i)
{
	return   zStep * i - (CHS - 1) * zStep / 2;
}

GameScene::~GameScene()
{

}