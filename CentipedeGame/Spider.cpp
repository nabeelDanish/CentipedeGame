#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "util.h"
#include "Spider.h"
Spider::Spider()
{
	id = 11;
	direction = 1;
	changeDirection = 0;
	animationFrame = 1;
}
Spider::Spider(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	id = 11;
	direction = 1;
	changeDirection = 0;
	animationFrame = 1;
}
Spider::Spider(const Position&pos) : MoveableObject(pos)
{
	id = 11;
	direction = 1;
	changeDirection = 0;
	animationFrame = 1;
}

//Collision Detection
bool Spider::checkCollision(int board[30][45])
{
	if ((board[position.getGridY() + 1][position.getGridX()] == 6)
		|| (board[position.getGridY() + 1][position.getGridX() + 1] == 6)
		)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//---------------------------------------------[MAIN MOVEMENT FUNCITON]--------------------------------------------

int Spider::Move(int d, int board[30][45])
{
	//Taking care of Animation
	++animationFrame;
	if (animationFrame > 40)
	{
		animationFrame = 1;
	}
	//Checking Collision with Laser
	if (checkCollision(board))
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
		return 0;
	}
	//Moving
	if (changeDirection == 10)
	{
		direction = rand() % 8;
		changeDirection = 0;
	}
	board[position.getGridY()][position.getGridX()] = 0;
	switch (direction)
	{
	case 0:
	{
		if (position.getGridX() > 0)
		{
			position.setGridX(position.getGridX() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 1:
	{
		if (position.getGridX() < 43)
		{
			position.setGridX(position.getGridX() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 2:
	{
		if (position.getGridY() < 27)
		{
			position.setGridY(position.getGridY() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 3:
	{
		if (position.getGridY() > 20)
		{
			position.setGridY(position.getGridY() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 4:
	{
		if ((position.getGridY() > 20) && (position.getGridX() < 44))
		{
			position.setGridY(position.getGridY() - 1);
			position.setGridX(position.getGridX() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 5:
	{
		if ((position.getGridY() < 27) && (position.getGridX() < 44))
		{
			position.setGridY(position.getGridY() + 1);
			position.setGridX(position.getGridX() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 6:
	{
		if ((position.getGridY() < 27) && (position.getGridX() > 1))
		{
			position.setGridY(position.getGridY() + 1);
			position.setGridX(position.getGridX() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 7:
	{
		if ((position.getGridY() > 20) && (position.getGridX() > 1))
		{
			position.setGridY(position.getGridY() - 1);
			position.setGridX(position.getGridX() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	default:
		break;
	}
	++changeDirection;
	return -1;
}
void Spider::Draw()
{
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 21, position.getY() + 0, 4, colors[color1]);
	DrawSquare(position.getX() + 24, position.getY() + 0, 4, colors[color2]);
	DrawSquare(position.getX() + 27, position.getY() + 0, 4, colors[color1]);
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 3, 4, colors[color1]);
	DrawSquare(position.getX() + 30, position.getY() + 3, 4, colors[color1]);
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 21, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 24, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 27, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 30, position.getY() + 6, 4, colors[color1]);
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color2]);
	DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[color2]);
	DrawSquare(position.getX() + 24, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 27, position.getY() + 9, 4, colors[color2]);
	DrawSquare(position.getX() + 30, position.getY() + 9, 4, colors[color2]);
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[color2]);
	DrawSquare(position.getX() + 24, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 27, position.getY() + 12, 4, colors[color2]);
	DrawSquare(position.getX() + 30, position.getY() + 12, 4, colors[color3]);
	//------------------------------------------------------------------------------
	DrawSquare(position.getX() + 24, position.getY() + 15, 4, colors[color1]);

	//Animation Drawing
	switch (animationFrame)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color2]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 0, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 33, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 36, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 21, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color1]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 0, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 33, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 36, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color2]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 33, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 36, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color1]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 3, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 3, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 6, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 12, 4, colors[color3]);
		break;
	}
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color2]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 36, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 21, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	{
		//Mouth
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color2]);
		DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color1]);
		//Legs
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 24, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 33, position.getY() + 9, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 36, position.getY() + 12, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 21, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 24, 4, colors[color3]);
		break;
	}
	}
}