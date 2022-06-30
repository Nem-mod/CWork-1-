#ifndef GameScene_h
#define GameScene_h
#include <vector>
#include "Shape.h"

#define RCOL 4
class GameScene
{
private:
	float width, height;
	const int CHS = RCOL;
	float unitSize = CHS / 4;
	int button;           
	float angleX, angleY; 
	float mouseX, mouseY;
	float distZ;


	std::vector<Shape*> shapes;
	std::vector<Shape*> field;
	const float xStep = CHS/4, zStep = CHS / 4;

	bool BoolLose;
	bool BoolStart;
	bool StopGame;
	bool wstep = false;

	int int_score;
	int int_tempscore;
	char chrScore[10];

	char chrTimeNum[10];
	int sec;

public:
	int chress[RCOL][RCOL];
	GameScene(int WIDTH, int HEIGHT);
	void on_paint();
	void on_size(int width, int height);
	void on_motion(int x, int y);
	void on_mouse(int button, int state, int x, int y);
	void on_timer(int value);
	void on_keyboard(unsigned char key, int x, int y);

	void initialize();
	~GameScene();

	//Game controller
	void lose();
	void restart();
	void randNum();
	void countscore(int int_tempscore);

	void initializeKeys(int key);
	int changeChress(int TwoChressNum);
	void up();
	void left();
	void right();
	void down();


	float allocX(int i);
	float allocZ(int i);
};
#endif
