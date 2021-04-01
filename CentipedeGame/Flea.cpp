#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "Flea.h"
#include "util.h"
#include "Position.h"
#include "MoveableObject.h"
Flea::Flea()
{
	animationFrame = 0;
	direction = 2;
	id = 9;
}
Flea::Flea(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	animationFrame = 0;
	direction = 2;
	id = 9;
}
Flea::Flea(const Position&pos) : MoveableObject(pos)
{
	animationFrame = 0;
	direction = 2;
	id = 9;
}
int Flea::Move(int direction, int board[30][45])
{
	//Animation Frame increasing
	++animationFrame;
	if (animationFrame > 3)
	{
		animationFrame = 0;
	}
	//Movement
	direction = 2;
	if (board[position.getGridY() + 1][position.getGridX()] == 6)
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
		return 0;
	}
	else if (position.getGridY() == 30)
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
		return -1;
	}
	else
	{
		board[position.getGridY()][position.getGridX()] = 0;
		position.setGridY(position.getGridY() + 1);
		board[position.getGridY()][position.getGridX()] = id;
		return (rand() % 5) + 1;
	}
}

void Flea::Draw()
{
	//------------------------------------------------------------------------
	DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[color3]);
	//------------------------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 18, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 18, 4, colors[color3]);
	//------------------------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[color2]);
	DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 15, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 15, 4, colors[color3]);
	//------------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 12, 4, colors[color3]);
	//------------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 3, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color3]);
	//----------Animation Frame
	DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 9, 4, colors[color3]);
	//---------------------------------------------------------------------------
	DrawSquare(position.getX() + 21, position.getY() + 6, 4, colors[color3]);
	DrawSquare(position.getX() + 24, position.getY() + 6, 4, colors[color3]);
	switch (animationFrame)
	{
	case 0:
	{
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 3, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 0, 4, colors[color1]);
		break;
	}
	case 1:
	{
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 6, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 0, 4, colors[color1]);
		break;
	}
	case 2:
	{
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 9, 4, colors[color1]);
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 0, 4, colors[color1]);
		break;
	}
	case 3:
	{
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
		//------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 3, 4, colors[color1]);
		DrawSquare(position.getX() + 24, position.getY() + 3, 4, colors[color1]);
		//-------------------------------------------------------------------------
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 0, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 0, 4, colors[color1]);
		break;
	}
	}
}