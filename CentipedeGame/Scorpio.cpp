#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "util.h"
#include "Scorpio.h"
Scorpio::Scorpio()
{
	direction = rand() % 2;
	animationFrame = 0;
	id = 10;
}
Scorpio::Scorpio(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	direction = rand() % 2;
	animationFrame = 0;
	id = 10;
}
Scorpio::Scorpio(const Position&pos) :MoveableObject(pos)
{
	direction = rand() % 2;
	animationFrame = 0;
	id = 10;
}
int Scorpio::Move(int direction, int board[30][45])
{
	++animationFrame;
	if (animationFrame > 3)
	{
		animationFrame = 0;
	}
	if ((position.getGridX() < 0) || (position.getGridX() > 44))
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
		board[position.getGridY()][position.getGridX() + 1] = 0;
		return -1;
	}
	//Condition for Laser Shot
	else if ((board[position.getGridY() + 1][position.getGridX()] == 6) || ((board[position.getGridY() + 1][position.getGridX() + 1] == 6))
		|| ((board[position.getGridY() + 1][position.getGridX() - 1] == 6)))
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
		board[position.getGridY()][position.getGridX() + 1] = 0;
		return 0;
	}
	else
	{
		board[position.getGridY()][position.getGridX()] = 0;
		board[position.getGridY()][position.getGridX() + 1] = 0;
		position.setGridX(position.getGridX() - 1);
		board[position.getGridY()][position.getGridX()] = id;
		board[position.getGridY()][position.getGridX() + 1] = id;
		return -1;
	}
	
}

//---------------------------------[PIXEL PER PIXEL DRAWING FUNCTION]---------------------------------------

void Scorpio::Draw()
{
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 18, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 27, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 30, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 33, position.getY() + 0, 4, colors[color3]);
	DrawSquare(position.getX() + 36, position.getY() + 0, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 27, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 30, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 33, position.getY() + 3, 4, colors[color3]);
	DrawSquare(position.getX() + 36, position.getY() + 3, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 6, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 6, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 27, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 30, position.getY() + 12, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 30, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 33, position.getY() + 15, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 18, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[color2]);
	DrawSquare(position.getX() + 15, position.getY() + 18, 4, colors[color2]);
	DrawSquare(position.getX() + 18, position.getY() + 18, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 18, 4, colors[color2]);
	DrawSquare(position.getX() + 24, position.getY() + 18, 4, colors[color2]);
	DrawSquare(position.getX() + 33, position.getY() + 18, 4, colors[color3]);
	//-------------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[color2]);
	DrawSquare(position.getX() + 18, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 21, 4, colors[color2]);
	DrawSquare(position.getX() + 30, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 36, position.getY() + 21, 4, colors[color3]);

	//Drawing the Animation
	switch (animationFrame)
	{
	case 0:
	{
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		break;
	case 1:
	{
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 2:
	{
		DrawSquare(position.getX() + 36, position.getY() + 6, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 6, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 9, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 12, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 48, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 48, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 51, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 15, 4, colors[color3]);
		break;
	}
	case 3:
	{
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 39, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 39, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 42, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 42, position.getY() + 18, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 45, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 45, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 48, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 48, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 48, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 48, position.getY() + 15, 4, colors[color3]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 51, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 51, position.getY() + 12, 4, colors[color3]);
		break;
	}
	}
	}
}