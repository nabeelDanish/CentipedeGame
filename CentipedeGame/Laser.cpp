#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "Laser.h"
#include "util.h"
Laser::Laser()
{
	id = 6;
}
Laser::Laser(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	id = 6;
}
Laser::Laser(const Position&pos) : MoveableObject(pos)
{
	id = 6;
}
void Laser::Draw()
{
	DrawSquare(position.getX() + 9, position.getY(), 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[color2]);
	DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color2]);
}
int Laser::Move(int direction, int board[30][45])
{
	direction = 2;
	if (position.getGridY() - 1 == 0)
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
	}
	else if (board[position.getGridY() - 1][position.getGridX()] == 0)
	{
		board[position.getGridY()][position.getGridX()] = 0;
		position.setGridY(position.getGridY() - 1);
		board[position.getGridY()][position.getGridX()] = id;
	}
	else
	{
		setActive(0);
		board[position.getGridY()][position.getGridX()] = 0;
	}
	return 0;
}