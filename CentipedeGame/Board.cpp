#include <Windows.h>
#include <gl/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include "Board.h"
#include "Player.h"
#include "Mushroom.h"
#include "Player.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include "Laser.h"
#include "Centipede.h"
#include "Segment.h"
#include "Flea.h"
#include "Scorpio.h"
#include "Spider.h"
#include <cstdio>

//----------------------------------------------------SETTING ENUMERATED DATA TYPE-----------------------------------------
enum BoardParts
{
	NILL, S_BRICK, G_BRICK, R_BRICK, PLAYER, MUSHROOM, LASER, SEGMENT, CENTIPEDE, FLEA, SCORPIO, SPIDER, POISON_MUSHROOM
};


//=========================================================================================================================
//----------------------------------------------[CONSTRUCTOR]--------------------------------------------------------------
//=========================================================================================================================
Board::Board(int xsize, int ysize)
{
	cout << "Constructor board" << endl;
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	for (int i = 0; i < BOARD_Y; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j)
		{
			board_array[i][j] = 0;
		}
	}
	gameStarted = 0;
	resetGame = 1;
	mainMenu = 0;
	mainMenuAnimationFrame = 0;
	playerDyingAnimation = 0;
	x_pos = 320;
	y_pos = 580;
	playerDead = 0;
	//set up board
}

//=========================================================================================================================
//----------------------------------------------[DESTRUCTOR]---------------------------------------------------------------
//=========================================================================================================================
Board::~Board(void) 
{
	centipedes.clear();
	mushrooms.clear();
	creatures.clear();
	//EMPTY
}

//=========================================================================================================================
//----------------------------------------------[MAIN INITALIZEBOARD FUNCTION]---------------------------------------------
//=========================================================================================================================

void Board::InitalizeBoard(int w, int h) 
{
	if (!gameStarted)
	{
		creatures.clear();
		numCreature = 0;
		centipedes.clear();
		numCentipede = 0;
		mushrooms.clear();
		numMushroom = 0;
		scoreBoard.reset();
		mainMenuAnimationFrame = 0;
		playerDead = 0;
		//Setting up the ScoreBoard Object
		Position score(0, 0);
		scoreBoard.setPosition(score);
		cout << "Initialize board" << endl;
		width = w;
		height = h;
		for (int i = 0; i < BOARD_Y - 1; ++i)
		{
			for (int j = 0; j < BOARD_X; ++j)
			{
				// can use G_BRICK, R_BRICK, or S_BRICK here
				board_array[i][j] = NILL;
			}
		}
	}
	if (resetGame)
	{
		//Resetting Variables
		numFlea = 0;
		numSpider = 0;
		numScorpio = 0;
		playerDead = 0;
		playerCollided = 0;
		playerDyingAnimation = 0;
		if (gameStarted)
		{
			if (creatures.size() > 1)
			{
				creatures[0]->getPosition().setValues(16, 1);//Ressetting the Player coordinates
				creatures.erase(creatures.begin() + 1, creatures.end());
			}
		}
		for (int i = 0; i < BOARD_Y; ++i)
		{
			for (int j = 0; j < BOARD_X; ++j)
			{
				if ((board_array[i][j] != MUSHROOM) && (board_array[i][j] != POISON_MUSHROOM))
				{
					board_array[i][j] = NILL;
				}
			}
		}
		if (!gameStarted)
		{
			numMushroom = 20;
			mushrooms.resize(numMushroom);
			for (int i = 0; i < numMushroom; ++i)
			{
				int temp_x;
				int temp_y;
				temp_x = GetRandInRange(2, 44);
				temp_y = GetRandInRange(2, 25);
				if (checkPlacingConditions(temp_x, temp_y))
				{
					mushrooms[i] = new Mushroom(temp_x, temp_y);
					board_array[temp_y][temp_x] = MUSHROOM;
					//mushrooms[i]->setIsPoisnous(1);				For Debugging
				}
				else
				{
					--i;
				}
			}
			if (mainMenu == 1)
			{
				numCreature = 1;
				creatures.resize(numCreature);
				creatures[0] = new Player(22, 28);
				for (int i = 0; i < numCreature; ++i)
				{
					board_array[creatures[i]->getPosition().getGridY()][creatures[i]->getPosition().getGridX()] = creatures[i]->getID();
				}
			}
			gameStarted = 1;
		}
		//Creating More Mushrooms
		if (scoreBoard.getLevel() > 1)
		{
			int prev_index = numMushroom - 1;
			numMushroom += scoreBoard.getLevel() * 3;
			mushrooms.resize(numMushroom);
			for (int i = prev_index; i < numMushroom; ++i)
			{
				if (i < mushrooms.size())
				{
					int temp_x;
					int temp_y;
					temp_x = GetRandInRange(2, 44);
					temp_y = GetRandInRange(2, 25);
					if (checkPlacingConditions(temp_x, temp_y))
					{
						mushrooms[i] = new Mushroom(temp_x, temp_y);
						board_array[temp_y][temp_x] = MUSHROOM;
						//mushrooms[i]->setIsPoisnous(1);				For Debugging
					}
					else
					{
						--i;
					}
				}
			}
		}
		//Setting up the Health for Previous Mushrooms, while giving points for Regenerated ones
		for (int i = 0; i < numMushroom; ++i)
		{
			if (mushrooms[i]->getHealth() == 1)
			{
				mushrooms[i]->setHealth(2);
				scoreBoard.increaseScore(5);
			}
		}
		//Creating the Centipede
		numCentipede = scoreBoard.getLevel();
		centipedes.resize(numCentipede);
		short int size = 10 - scoreBoard.getLevel();
		if (size < 0)
		{
			size = 0;
		}
		centipedes[0] = new Centipede(16, 1, size, board_array);
		for (int i = 1; i < numCentipede; ++i)
		{
			centipedes[i] = new Centipede(16, 1 + i, 0, board_array);
			centipedes[i]->setDirection(centipedes[i - 1]->getDirection() == 0 ? 1 : 0);
		}
		for (int i = 0; i < numCentipede; ++i)
		{
			board_array[centipedes[i]->getPosition().getGridY()][centipedes[i]->getPosition().getGridX()] = centipedes[i]->getID();
		}

		//Setting the Speed of the Creatures
		centipedeSpeed = 0;
		spiderSpeed = 0;
		scorpioSpeed = 0;
		//displayValues(); Debug Function
		resetGame = 0;
		//scoreBoard.setLevel(4);
		switch (scoreBoard.getLevel())
		{
		case 1:		color1 = FOREST_GREEN, color2 = RED, color3 = WHITE; break;
		case 2:		color1 = AQUA, color2 = DEEP_PINK, color3 = BRIGHT_YELLOW; break;
		case 3:		color1 = DEEP_PINK, color2 = AQUA, color3 = RED; break;
		case 4:		color1 = RED, color2 = DARK_BLUE, color3 = BRIGHT_YELLOW; break;
		case 5:		color1 = AQUA, color2 = BRIGHT_YELLOW, color3 = DARK_BLUE; break;
		case 6:		color1 = BRIGHT_YELLOW, color2 = DARK_BLUE, color3 = AQUA; break;
		case 7:		color1 = DEEP_PINK, color2 = AQUA, color3 = BRIGHT_YELLOW; break;
		case 8:		color1 = RED, color2 = BRIGHT_YELLOW, color3 = AQUA; break;
		case 9:		color1 = FOREST_GREEN, color2 = DEEP_PINK, color3 = BRIGHT_YELLOW; break;
		case 10:	color1 = WHITE, color2 = RED, color3 = AQUA; break;
		case 11:	color1 = FOREST_GREEN, color2 = DEEP_PINK, color3 = WHITE; break;
		case 12:	color1 = AQUA, color2 = DARK_BLUE, color3 = BRIGHT_YELLOW; break;
		}
	}
}


//------------------------------Debug Function Display Values that can be used to Debug

void Board::displayValues()
{
	cout << "BOARD : " << endl;
	for (int i = 0; i < BOARD_Y; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j)
		{
			cout << board_array[i][j] << " ";
		}
		cout << endl;
	}
}

//=========================================================================================================================
//-----------------------------------------------[MAIN DRAWING FUNCTION]---------------------------------------------------
//=========================================================================================================================

void Board::Draw() 
{
	//Setting up the Color Scheme
	for (int i = 0; i < numMushroom; ++i)
	{
		if (i < mushrooms.size())
		{
			mushrooms[i]->setColors(color1, color2, color3);
		}
	}
	for (int i = 0; i < numCreature; ++i)
	{
		if (i < creatures.size())
		{
			creatures[i]->setColors(color1, color2, color3);
		}
	}
	for (int i = 0; i < numCentipede; ++i)
	{
		if (i < centipedes.size())
		{
			centipedes[i]->setColors(color1, color2, color3);
		}
	}
	scoreBoard.setColors(color1, color2, color3);
	glColor3f(0, 0, 1);
 	glPushMatrix();
	if (mainMenu == 1)
	{
 		scoreBoard.Draw();
	}
	for (int i = 0; i < numCreature; ++i)
	{
		creatures[i]->Draw();
	}
	for (int i = 0; i < numMushroom; ++i)
	{
		mushrooms[i]->Draw();
	}
	for (int i = 0; i < numCentipede; ++i)
	{
		centipedes[i]->Draw();
	}
	if (mainMenu == 0)
	{
		DrawMainMenu();
	}
	glPopMatrix();
}

//=========================================================================================================================
//-----------------------------------------------[LASER CREATION FUNCTION]-------------------------------------------------
//=========================================================================================================================

void Board::Create(int id)
{
	switch (id)
	{
	case LASER:
	{
		if (mainMenu == 1)
		{
			{
				//cout << "LASER CREATED" << endl;
				++numCreature;
				creatures.resize(numCreature);
				creatures[numCreature - 1] = new Laser(creatures[0]->getPosition().getGridX(), creatures[0]->getPosition().getGridY() - 1);
				board_array[creatures[0]->getPosition().getGridY() - 1][creatures[0]->getPosition().getGridX()] = LASER;

			}
		}
		else
		{
			startGame();
		}
		break;
	}
	default:
		{
			break;
		}
	}
}
//-----------------USELESS FUNCTION
void Board::GetInitTextPosition(int &x, int &y) 
{
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

//=========================================================================================================================
//--------------------------------------------[MAIN MENU FUNCTION/UPDATE]--------------------------------------------------
//=========================================================================================================================
void Board::Update()
{
	if ((playerDyingAnimation > 0) && (playerDyingAnimation < 50))
	{
		++playerDyingAnimation;
	}
	if (playerDyingAnimation == 50)
	{
		playerDyingAnimation = 0;
		playerDead = 1;
	}
	switch (mainMenu)
	{
	case 0:
	{
		switch (mainMenuAnimationFrame)
		{
		case 100:		color1 = FOREST_GREEN, color2 = RED, color3 = WHITE; break;
		case 200:		color1 = AQUA, color2 = DEEP_PINK, color3 = BRIGHT_YELLOW; break;
		case 300:		color1 = DEEP_PINK, color2 = AQUA, color3 = RED; break;
		case 400:		color1 = RED, color2 = DARK_BLUE, color3 = BRIGHT_YELLOW; break;
		case 500:		color1 = AQUA, color2 = BRIGHT_YELLOW, color3 = DARK_BLUE; break;
		case 600:		color1 = BRIGHT_YELLOW, color2 = DARK_BLUE, color3 = AQUA; break;
		case 700:		color1 = DEEP_PINK, color2 = AQUA, color3 = BRIGHT_YELLOW; break;
		case 800:		color1 = RED, color2 = BRIGHT_YELLOW, color3 = AQUA; break;
		case 900:		color1 = FOREST_GREEN, color2 = DEEP_PINK, color3 = BRIGHT_YELLOW; break;
		case 1000:		color1 = WHITE, color2 = RED, color3 = AQUA; break;
		case 1100:		color1 = FOREST_GREEN, color2 = DEEP_PINK, color3 = WHITE; break;
		case 1200:	color1 = AQUA, color2 = DARK_BLUE, color3 = BRIGHT_YELLOW; break;
		default:	break;
		}
		++mainMenuAnimationFrame;
		if (mainMenuAnimationFrame > 1300)
		{
			mainMenuAnimationFrame = 0;
		}
	}
	case 1:
		if (playerDyingAnimation == 0)
		{
			Game();		break;
		}
	}
}
void Board::startGame()
{
	playerDyingAnimation = 0;
	mainMenu = 1;
	resetGame = 1;
	gameStarted = 0;
	playerDead = 0;
	InitalizeBoard(width, height);
}
//=========================================================================================================================
//--------------------------------------------[MAIN GAME FUNCTION]-------------------------------------------------------
//=========================================================================================================================


void Board::Game()
{
	if (playerDyingAnimation > 0)
	{
		return;
	}
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------Creature Check, if not Active they will be deleted from the Array

	for (int i = 1; i < numCreature; ++i)
	{
		if (!creatures[i]->getActive())
		{
			if (creatures[i]->getID() == FLEA)
			{
				numFlea = 0;
			}
			else if (creatures[i]->getID() == SCORPIO)
			{
				numScorpio = 0;
			}
			else if (creatures[i]->getID() == SPIDER)
			{
				numSpider = 0;
			}
			board_array[creatures[i]->getPosition().getGridY()][creatures[i]->getPosition().getGridX()] = 0;
			delete creatures[i];
			creatures.erase(creatures.begin() + i);
			--numCreature;
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	for (int i = 0; i < numMushroom; ++i)
	{
		if ((!mushrooms[i]->getActive()) && i < mushrooms.size())
		{
			board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX()] = 0;
			//delete mushrooms[i]; This causese Heap Memory leak, can't solve
			mushrooms.erase(mushrooms.begin() + i);
			--numMushroom;
			--i;
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	//-------------------------------------------Creatures Moving Function

	for (int i = 1; i < numCreature; ++i)
	{
		if (i < creatures.size())
		{
			int switch_check = -1;
			if (creatures[i]->getID() == SCORPIO)
			{
				if (scorpioSpeed == 4)
				{
					switch_check = creatures[i]->Move(0, board_array);
				}
			}
			else if (creatures[i]->getID() == SPIDER)
			{
				if (spiderSpeed == 1)
				{
					switch_check = creatures[i]->Move(0, board_array);
				}
			}
			else
			{
				switch_check = creatures[i]->Move(0, board_array);
			}
			switch (switch_check)
			{
			case 0:
			{
				switch (creatures[i]->getID())
				{
				case FLEA:		scoreBoard.increaseScore(200);		break;
				case SCORPIO:	scoreBoard.increaseScore(1000);		break;
				case SPIDER:	scoreBoard.increaseScore(300); break;
				default:	break;
				}
				break;
			}
			case 1:
			{
				if (checkPlacingConditions(creatures[i]->getPosition().getGridX(), creatures[i]->getPosition().getGridY() - 2))
				{
					if (creatures[i]->getPosition().getGridY() < 25)
					{
						++numMushroom;
						mushrooms.resize(numMushroom);
						mushrooms[numMushroom - 1] = new Mushroom(creatures[i]->getPosition());
					}
				}
				break;
			}
			}
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	//---------------------------------------------------[CENTIPEDE COLLISON]------------------------------------------------------

	for (int i = 0; i < numCentipede; ++i)
	{
		if (centipedeSpeed == 2)
		{
			centipedes[i]->Move(0, board_array);
		}
		if (!centipedes[i]->getIsMagic())
		{
			int switch_check = centipedes[i]->checkCollision(board_array);
			switch (switch_check)
			{
			case -2:
			{
				break;
			}
			case -1:
			{
				//HEADSHOT!!, increasing Score
				scoreBoard.increaseScore(100);
				break;
			}
			case 0:
			{
				//-------------------CREATING NEW MUSHROOM
				++numMushroom;
				Position temp(centipedes[i]->getPosition().getGridX(), centipedes[i]->getPosition().getGridY() - 1);
				mushrooms.resize(numMushroom);
				mushrooms[numMushroom - 1] = new Mushroom(temp);
				board_array[mushrooms[numMushroom - 1]->getPosition().getGridY()][mushrooms[numMushroom - 1]->getPosition().getGridX()] = MUSHROOM;
				//Deleting the old Centipede
				board_array[centipedes[i]->getPosition().getGridY()][centipedes[i]->getPosition().getGridX()] = 0;
				//delete centipedes[i]; This line is causing Memory leaks, can't debug this :(
				centipedes.erase(centipedes.begin() + i);
				--numCentipede;
				--i;
				//HEADSHOT!!, increasing Score
				scoreBoard.increaseScore(100);
				break;
			}
			default://------------------------------------------CENTIPEDE IS CREATED HERE
			{
				if (switch_check < 0)
				{
					switch_check = 0;
				}
				++numCentipede;
				centipedes.resize(numCentipede);
				delete centipedes[numCentipede - 1];
				int temp_direction = !centipedes[i]->getDirection();
				int x_pos = centipedes[i]->getDirection() == 0 ? (switch_check + 1) : -(switch_check + 1);
				centipedes[numCentipede - 1] = new Centipede(centipedes[i]->getPosition().getGridX() + x_pos, centipedes[i]->getPosition().getGridY(), switch_check, board_array);
				centipedes[numCentipede - 1]->setDirection(temp_direction);
				board_array[centipedes[i]->getPosition().getGridY()][centipedes[i]->getPosition().getGridX()] = CENTIPEDE;
				//-------------------CREATING NEW MUSHROOM
				++numMushroom;
				Position temp(centipedes[i]->getPosition().getGridX() + x_pos, centipedes[i]->getPosition().getGridY());
				mushrooms.resize(numMushroom);
				mushrooms[numMushroom - 1] = new Mushroom(temp);
				board_array[mushrooms[numMushroom - 1]->getPosition().getGridY()][mushrooms[numMushroom - 1]->getPosition().getGridX()] = MUSHROOM;
				//Scoring
				scoreBoard.increaseScore(10);
				break;
			}
			}

			//Deleting the Laser Shot
			if (switch_check != -2)
			{
				for (int i = 0; i < numCreature; ++i)
				{
					if ((creatures[i]->getID() == 6) && (i < creatures.size()))
					{
						creatures[i]->setActive(0);
						board_array[creatures[i]->getPosition().getGridY()][creatures[i]->getPosition().getGridX()] = 0;
						break;
					}
				}
			}
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------


	//--------------------Checking if a Centipede is in Player Zone
	if (gameStarted)
	{
		for (int i = 0; i < numCentipede; ++i)
		{
			if (centipedes[i]->getPosition().getGridY() >= 25)
			{
				int draw = rand() % 500;
				if (draw == 0)
				{
					int y_pos = GetRandInRange(20, 25);
					++numCentipede;
					centipedes.resize(numCentipede);
					centipedes[numCentipede - 1] = new Centipede(0, y_pos, 0, board_array);
				}
			}
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	//-------------------------------------------------[MUSHROOM COLLISION]-------------------------------------------------

	//Mushroom Collision with Spider
	for (int i = 0; i < numMushroom; ++i)
	{
		//Restating the ID on the Board, in case it gets overriden by creatures
		board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX()] = mushrooms[i]->getID();
		if (
			//Conditions for Spider
			(board_array[mushrooms[i]->getPosition().getGridY() + 1][mushrooms[i]->getPosition().getGridX() + 0] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() + 1][mushrooms[i]->getPosition().getGridX() + 1] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() + 1][mushrooms[i]->getPosition().getGridX() - 1] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() + 0][mushrooms[i]->getPosition().getGridX() + 1] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() + 0][mushrooms[i]->getPosition().getGridX() - 1] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() - 1][mushrooms[i]->getPosition().getGridX() + 0] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() - 1][mushrooms[i]->getPosition().getGridX() + 1] == SPIDER)
			|| (board_array[mushrooms[i]->getPosition().getGridY() - 1][mushrooms[i]->getPosition().getGridX() - 1] == SPIDER)
			)
		{
			mushrooms[i]->setHealth(mushrooms[i]->getHealth() - 1);
			if (mushrooms[i]->getHealth() == 0)
			{
				mushrooms[i]->setActive(0);
				board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX()] = 0;
			}
		}
	}
	//Mushroom Collision with Laser
	for (int i = 0; i < numMushroom; ++i)
	{
		if (board_array[mushrooms[i]->getPosition().getGridY() + 1][mushrooms[i]->getPosition().getGridX()] == LASER)
		{
			mushrooms[i]->setHealth(mushrooms[i]->getHealth() - 1);
			if (mushrooms[i]->getHealth() == 0)
			{
				mushrooms[i]->setActive(0);
				board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX()] = 0;
			}
			scoreBoard.increaseScore(1);
			//Deleting the Laser Shot
			for (int i = 0; i < numCreature; ++i)
			{
				if (creatures[i]->getID() == 6)
				{
					creatures[i]->setActive(0);
					break;
				}
			}
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------
	//Mushroom Collision with Scorpio
	for (int i = 0; i < mushrooms.size(); ++i)
	{

		if (board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX() + 1] == 10)
		{
			mushrooms[i]->setIsPoisnous(1);
			board_array[mushrooms[i]->getPosition().getGridY()][mushrooms[i]->getPosition().getGridX()] = POISON_MUSHROOM;
		}
	}

	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	//----------------------------------------------------GENERATING RANDOM CREATURES
	//------------------FLEA
	for (int i = 0; i < numCreature; ++i)
	{
		if (creatures[i]->getID() == 9)
		{
			numFlea = 1;
		}
		else if (creatures[i]->getID() == 10)
		{

		}
	}
	if (!numFlea)
	{
		int draw;
		draw = GetRandInRange(0, 150);
		if (draw == 1)
		{
			int x_pos;
			x_pos = GetRandInRange(1, 44);
			int numMushroomsinRow = 0;
			for (int i = 0; i < BOARD_Y; ++i)
			{
				if (board_array[i][x_pos] == MUSHROOM)
				{
					++numMushroomsinRow;
				}
			}
			if (numMushroomsinRow <= 3)
			{
				++numCreature;
				creatures.resize(numCreature);
				creatures[numCreature - 1] = new Flea(x_pos, 1);
				board_array[creatures[numCreature - 1]->getPosition().getGridY()][creatures[numCreature - 1]->getPosition().getGridX()] = creatures[numCreature - 1]->getID();
			}
		}
	}

	//-------------------SCORPIO
	if (!numScorpio)
	{
		int draw = rand() % 400;
		if (draw == 1)
		{
			int y_pos = GetRandInRange(1, 20);
			++numCreature;
			creatures.resize(numCreature);
			creatures[numCreature - 1] = new Scorpio(44, y_pos);
			board_array[creatures[numCreature - 1]->getPosition().getGridY()][creatures[numCreature - 1]->getPosition().getGridX()] = creatures[numCreature - 1]->getID();
			board_array[creatures[numCreature - 1]->getPosition().getGridY()][creatures[numCreature - 1]->getPosition().getGridX() + 1] = creatures[numCreature - 1]->getID();
			numScorpio = 1;
		}
	}
	//-----------------SPIDER
	if (!numSpider)
	{
		int draw = rand() % 100;
		if (draw == 1)
		{
			int y_pos = GetRandInRange(15, 29);
			int x_pos = ((rand() % 2) * 43) + 1;
			++numCreature;
			creatures.resize(numCreature);
			creatures[numCreature - 1] = new Spider(x_pos, y_pos);
			board_array[creatures[numCreature - 1]->getPosition().getGridY()][creatures[numCreature - 1]->getPosition().getGridX()] = creatures[numCreature - 1]->getID();
			numSpider = 1;
		}
	}



	//--------------------------------------------------[MAIN PLAYER COLLISION]------------------------------------
	for (int i = 0; (i < creatures.size() && (i < numCreature)); ++i)
	{
		//Collision for Flea
		if (creatures[i]->getID() == FLEA)
		{
			if (board_array[creatures[i]->getPosition().getGridY() + 1][creatures[i]->getPosition().getGridX()] == PLAYER)
			{
				playerCollided = 1;
				break;
			}
		}
		//Collision for Spider
		if (creatures[i]->getID() == SPIDER)
		{
			if ((board_array[creatures[i]->getPosition().getGridY() + 1][creatures[i]->getPosition().getGridX()] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY() - 1][creatures[i]->getPosition().getGridX()] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY()][creatures[i]->getPosition().getGridX() + 1] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY()][creatures[i]->getPosition().getGridX() - 1] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY() - 1][creatures[i]->getPosition().getGridX() - 1] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY() + 1][creatures[i]->getPosition().getGridX() + 1] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY() - 1][creatures[i]->getPosition().getGridX() + 1] == PLAYER)
				|| (board_array[creatures[i]->getPosition().getGridY() + 1][creatures[i]->getPosition().getGridX() - 1] == PLAYER)
				)
			{
				playerCollided = 1;
				break;
			}
		}
	}
	//Collision for Centipede Head
	for (int i = 0; i < numCentipede; ++i)
	{
		if (i < centipedes.size())
		{
			switch (centipedes[i]->getDirection())
			{
			case 0:
			{
				if (board_array[centipedes[i]->getPosition().getGridY()][centipedes[i]->getPosition().getGridX() - 1] == PLAYER)
				{
					playerCollided = 1;
				}
				break;
			}
			case 1:
			{
				if (board_array[centipedes[i]->getPosition().getGridY()][centipedes[i]->getPosition().getGridX() + 1] == PLAYER)
				{
					playerCollided = 1;
				}
				break;
			}
			case 2:
			{
				if (board_array[centipedes[i]->getPosition().getGridY() + 1][centipedes[i]->getPosition().getGridX()] == PLAYER)
				{
					playerCollided = 1;
				}
				break;
			}
			}
			if (playerCollided)
			{
				break;
			}
		}
	}
	//--------------------------------------------LEVEL UP DETECTION
	if (numCentipede == 0)
	{
		resetGame = 1;
		scoreBoard.setLevel(scoreBoard.getLevel() + 1);
		InitalizeBoard(width, height);
	}
	//--------------------------------------------GAME END DETECTION
	if (mainMenu == 1)
	{
		if (playerCollided)
		{
			if (!playerDead)
			{
				scoreBoard.setNumLives(scoreBoard.getNumLives() - 1);
				playerDyingAnimation = 1;
				creatures[0]->setActive(0);
			}
			else
			{
				playerDead = 0;
				if (!scoreBoard.gameEnd())
				{
					resetGame = 1;
					InitalizeBoard(width, height);
				}
				else
				{
					mainMenu = 0;
					resetGame = 1;
					gameStarted = 0;
					InitalizeBoard(width, height);
				}
			}
		}
	}



	//Solving Index Out of Bound Problems
	numMushroom = mushrooms.size();
	numCentipede = centipedes.size();
	numCreature = creatures.size();
	//---------------------------------

	//Taking care of other Varibless
	++centipedeSpeed; ++scorpioSpeed; ++spiderSpeed;
	if (centipedeSpeed > 2)
	{
		centipedeSpeed = 0;
	}
	if (scorpioSpeed > 4)
	{
		scorpioSpeed = 0;
	}
	if (spiderSpeed > 1)
	{
		spiderSpeed = 0;
	}
}


//=========================================================================================================================
//---------------------------------------ADDITIONAL UTILITY FUNCTIONS------------------------------------------------------
//=========================================================================================================================

//Placing Conditions for Mushrooms
bool Board::checkPlacingConditions(int x, int y)
{
	bool set = 1;
	if (board_array[y][x] != 0)
	{
		set = 0;
	}
	else if ((board_array[y][x + 1] != 0) || (board_array[y][x - 1] != 0))
	{
		set = 0;
	}
	else if ((board_array[y + 1][x] != 0) || (board_array[y - 1][x] != 0))
	{
		set = 0;
	}
	else if ((board_array[y + 1][x + 1] != 0) || (board_array[y - 1][x - 1] != 0))
	{
		set = 0;
	}
	else if ((board_array[y + 1][x - 1] != 0) || (board_array[y - 1][x + 1] != 0))
	{
		set = 0;
	}
	return set;
}

//Main Menu Animation
void Board::setColors(int c1, int c2, int c3)
{
	color1 = c1;
	color2 = c2;
	color3 = c3;
}

//Main Menu Drawing
void Board::DrawMainMenu()
{
	//===========================[C]
	//--------------------------------------------
	DrawSquare(x_pos + 0, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 0, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 0, y_pos + 20, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 5, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 5, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 5, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 5, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 5, y_pos + 25, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 10, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 10, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 10, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 10, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 15, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 15, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 20, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 20, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 25, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 25, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 25, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 25, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 30, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 30, y_pos + 25, 6, colors[color3]);

	//===========================[E]
	//--------------------------------------------
	DrawSquare(x_pos + 50, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 50, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 55, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 55, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 60, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 60, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 60, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 65, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 65, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 65, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 70, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 70, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 70, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 75, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 75, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 80, y_pos + 0, 6, colors[color3]);

	//===========================[N]
//--------------------------------------------
	DrawSquare(x_pos + 100, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 100, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 105, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 105, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 110, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 110, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 110, y_pos + 25, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 115, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 115, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 115, y_pos + 20, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 120, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 120, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 120, y_pos + 15, 6, colors[color3]);
	//---------------------------------------------------------
	DrawSquare(x_pos + 125, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 125, y_pos + 30, 6, colors[color3]);
	//---------------------------------------------------------
	DrawSquare(x_pos + 130, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 130, y_pos + 30, 6, colors[color3]);

	//===========================[T]
	//--------------------------------------------
	DrawSquare(x_pos + 150, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 155, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 160, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 160, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 165, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 165, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 170, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 175, y_pos + 30, 6, colors[color3]);

	//===========================[I]
	//--------------------------------------------
	DrawSquare(x_pos + 195, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 195, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 200, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 200, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 205, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 205, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 210, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 210, y_pos + 30, 6, colors[color3]);
	//----------------------------------------------
	DrawSquare(x_pos + 215, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 215, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 220, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 220, y_pos + 30, 6, colors[color3]);

	//===========================[P]
//--------------------------------------------
	DrawSquare(x_pos + 240, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 240, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 245, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 245, y_pos + 30, 6, colors[color3]);
	//---------------------------------------------
	DrawSquare(x_pos + 250, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 250, y_pos + 30, 6, colors[color3]);
	//---------------------------------------------
	DrawSquare(x_pos + 255, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 255, y_pos + 30, 6, colors[color3]);
	//---------------------------------------------
	DrawSquare(x_pos + 260, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 260, y_pos + 30, 6, colors[color3]);
	//---------------------------------------------
	DrawSquare(x_pos + 265, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 265, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 265, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 265, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 265, y_pos + 30, 6, colors[color3]);
	//----------------------------------------------
	DrawSquare(x_pos + 270, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 270, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 270, y_pos + 25, 6, colors[color3]);

	//===========================[E]
	//--------------------------------------------
	DrawSquare(x_pos + 290, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 290, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 295, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 295, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 300, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 300, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 300, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 305, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 305, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 305, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 310, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 310, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 310, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 315, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 315, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 320, y_pos + 0, 6, colors[color3]);

	//===========================[D]
//--------------------------------------------
	DrawSquare(x_pos + 340, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 340, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 345, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 345, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 350, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 350, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 355, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 355, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 360, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 360, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 360, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 360, y_pos + 30, 6, colors[color3]);
	//----------------------------------------------
	DrawSquare(x_pos + 365, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 365, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 365, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 365, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 365, y_pos + 25, 6, colors[color3]);
	//----------------------------------------------
	DrawSquare(x_pos + 370, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 370, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 370, y_pos + 20, 6, colors[color3]);

	//===========================[E]
//--------------------------------------------
	DrawSquare(x_pos + 390, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 390, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 395, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 5, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 10, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 20, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 25, 6, colors[color3]);
	DrawSquare(x_pos + 395, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 400, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 400, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 400, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 405, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 405, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 405, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 410, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 410, y_pos + 15, 6, colors[color3]);
	DrawSquare(x_pos + 410, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 415, y_pos + 0, 6, colors[color3]);
	DrawSquare(x_pos + 415, y_pos + 30, 6, colors[color3]);
	//--------------------------------------------
	DrawSquare(x_pos + 420, y_pos + 0, 6, colors[color3]);


	//Drawing the String
	DrawString(x_pos + 100, y_pos - 350, "PRESS SPACE TO INSERT COIN", colors[color3]);
}
