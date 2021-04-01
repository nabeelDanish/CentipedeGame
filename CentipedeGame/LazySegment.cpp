#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "util.h"
#include "LazySegment.h"
LazySegment::LazySegment()
{
	isMagic = 0;
}
LazySegment::LazySegment(int x_grid, int y_grid) :Segment(x_grid, y_grid)
{
	isMagic = 0;
}
LazySegment::LazySegment(const Position& pos) : Segment(pos)
{
	isMagic = 0;
}
int LazySegment::Move(int direction, int board[30][45])
{
	return 0;
}
void LazySegment::Draw()
{
	//------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[color1]);
	//------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 6, 4, colors[color1]);
	//------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 3, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color1]);
	DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[color1]);
	//------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color1]);
	DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[color1]);
	//------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[color1]);
	DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[color1]);
	DrawSquare(position.getX() + 18, position.getY() + 15, 4, colors[color1]);
	//----------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[color1]);
	DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color1]);
	DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[color1]);
	DrawSquare(position.getX() + 15, position.getY() + 18, 4, colors[color1]);
	switch (animationFrame)
	{
	case 1:
	case 2:
	case 3:
	case 13:
	case 14:
	case 15:
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[color3]);
		break;
	case 4:
	case 5:
	case 6:
	case 10:
	case 11:
	case 12:
		DrawSquare(position.getX() + 15, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[color3]);
		break;
	case 7:
	case 8:
	case 9:
		DrawSquare(position.getX() + 18, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 18, position.getY() + 21, 4, colors[color3]);
		break;
	case 19:
	case 20:
	case 21:
		DrawSquare(position.getX() + 9, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[color3]);
		break;
	case 16:
	case 17:
	case 18:
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[color3]);
		break;
	}
	//increasing the Animation frame
	++animationFrame;
	if (animationFrame > 21)
	{
		animationFrame = 1;
	}
	
}