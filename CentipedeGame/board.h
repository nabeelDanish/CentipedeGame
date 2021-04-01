/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "MoveableObject.h"
#include "Player.h"
#include "GameObject.h"
#include "Position.h"
#include "Mushroom.h"
#include "Centipede.h"
#include "Segment.h"
#include "Flea.h"
#include "ScoreBoard.h"
 //#define WITH_TEXTURES
using namespace std;

class Board 
{
private:

	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	short color1, color2, color3;
	short boardAnimation;
	int x_pos, y_pos;
		
public:
	//Variables---------------------------------------------------------------------------------------
	static const int BOARD_X = 45;
	static const int BOARD_Y = 30;
	/*
	 static const int BOARD_X=17;
	 static const int BOARD_Y=14;
	 */
	//Arrays of Different Things
	vector<Mushroom*> mushrooms;
	vector<MoveableObject*> creatures;
	int board_array[BOARD_Y][BOARD_X];
	vector<Centipede*> centipedes;
	//Scoreboard Object
	ScoreBoard scoreBoard;
	//Important Integer Variables
	int numMushroom;
	int numCreature;
	int numCentipede;
	//Speed of Various Creatures
	int centipedeSpeed;
	int scorpioSpeed;
	int spiderSpeed;
	//Important bool Variables
	bool numFlea;
	bool numScorpio;
	bool numSpider;

	//GAME CONTROLLING VARIABLES
	bool gameStarted;
	bool resetGame;
	int mainMenu;
	int mainMenuAnimationFrame;
	int playerDyingAnimation;
	bool playerDead;
	bool playerCollided;
	//FUNCTIONS------------------------------------------------------------------------------------------
	Board(int xsize = 8, int ysize = 8);
	~Board(void);
	void InitalizeBoard(int, int);
	//draw the board
	void Draw();
	//My Functions
	void Create(int);
	void startGame();
	void setColors(int, int, int);
	void DrawMainMenu();
	//================================[GAME FUNCTION]========================================
	void Game();
	//--------------------------------------------------------------------------------------

	void Update();
	void displayValues();
	bool checkPlacingConditions(int x, int y);
	//Other Useless Functions
	static int GetBoardX() 
	{
		return BOARD_X;
	}
	static int GetBoardY() 
	{
		return BOARD_Y;
	}
	int GetMidX() 
	{
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() 
	{
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() 
	{
		return xcellsize;
	}
	void GetInitRandomPosition(int &x, int &y) 
	{
		// leave 10 units from all sides
		x = GetRandInRange(50, width - 50);
		y = GetRandInRange(50, height - 50);
	}
	int GetWidth() 
	{
		return width;
	}
	int GetHeight() 
	{
		return height;
	}
	void GetInitTextPosition(int &x, int &y);
};

#endif
