#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "util.h"
#include "MagicSegment.h"
MagicSegment::MagicSegment()
{
	isMagic = 0;
	interval = (rand() % 7) + 2;
	start = 0;
	duration = 2;
}
MagicSegment::MagicSegment(int x_grid, int y_grid) :Segment(x_grid, y_grid)
{
	isMagic = 0;
	interval = (rand() % 7) + 2;
	start = 0;
	duration = 2;
}
MagicSegment::MagicSegment(const Position&pos) :Segment(pos)
{
	isMagic = 0;
	interval = (rand() % 7) + 2;
	start = 0;
	duration = 2;
}
int MagicSegment::Move(int direction, int board[30][45])
{
	return 0;
}
void MagicSegment::Draw()
{
	if (duration % 10 == 0)
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
	}
	switch (animationFrame)
	{
	case 4:
	case 0:
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[WHITE]);
		DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[WHITE]);
		break;
	case 3:
	case 1:
		DrawSquare(position.getX() + 15, position.getY() + 0, 4, colors[WHITE]);
		DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[WHITE]);
		break;
	case 2:
		DrawSquare(position.getX() + 18, position.getY() + 0, 4, colors[WHITE]);
		DrawSquare(position.getX() + 18, position.getY() + 21, 4, colors[WHITE]);
		break;
	case 5:
	case 7:
		DrawSquare(position.getX() + 9, position.getY() + 0, 4, colors[WHITE]);
		DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[WHITE]);
		break;
	case 6:
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[WHITE]);
		DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[WHITE]);
		break;
	}
	//increasing the Animation frame
	++animationFrame;
	if (animationFrame > 7)
	{
		animationFrame = 0;
	}
	//Taking care of Blinking
	++start;
	if (duration == 0)
	{
		isMagic = 0;
	}
	if (duration != 0)
	{
		--duration;
	}
	if (start == interval)
	{
		isMagic = 1;
		interval = rand() % 5000;
		start = 0;
		duration = rand() % 500;
	}
}