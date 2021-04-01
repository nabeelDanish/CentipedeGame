#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "util.h"
#include "Mushroom.h"
Mushroom::Mushroom()
{
	id = 5;
	health = 2;
	isPoisnous = 0;
}
Mushroom::Mushroom(int x_grid, int y_grid) :GameObject(x_grid, y_grid)
{
	health = 2;
	id = 5;
	isPoisnous = 0;
}
Mushroom::Mushroom(const Position&pos) : GameObject(pos)
{
	health = 2;
	id = 5;
	isPoisnous = 0;
}
void Mushroom::setHealth(int h)
{
	health = h;
}
int Mushroom::getHealth()const
{
	return health;
}
bool Mushroom::getIsPoisnous()const
{
	return isPoisnous;
}
void Mushroom::setIsPoisnous(bool p)
{
	isPoisnous = p;
	id = 12;
}
void Mushroom::Draw()
{
	int c1, c2;
	isPoisnous ? c1 = color3, c2 = color2 : c1 = color1, c2 = color2;
	//DrawSquare(position.getX(), position.getY(), 24, colors[color1]);
	if (health == 2)
	{
		DrawSquare(position.getX() + 6, position.getY(), 4, colors[c2]);
		DrawSquare(position.getX() + 9, position.getY(), 4, colors[c2]);
		DrawSquare(position.getX() + 12, position.getY(), 4, colors[c2]);
		DrawSquare(position.getX() + 15, position.getY(), 4, colors[c2]);
		//-----------------------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[c2]);
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[c1]);
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[c1]);
		DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[c2]);
	}
	//-----------------------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[c2]);
	if (health == 2)
	{
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[c1]);
		DrawSquare(position.getX() + 12, position.getY() + 6, 4, colors[c1]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[c2]);
	}
	//----------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[c2]);
	if (health == 2)
	{
		DrawSquare(position.getX() + 3, position.getY() + 9, 4, colors[c2]);
	}
	DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[c2]);
	if (health == 2)
	{
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[c2]);
	}
	DrawSquare(position.getX() + 12, position.getY() + 9, 4, colors[c2]);
	if (health == 2)
	{
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[c2]);
	}
	DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[c2]);
	DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[c2]);
	//----------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 12, 4, colors[c2]);
	DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[c1]);
	DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[c2]);
	//----------------------------------------------------------------------
	DrawSquare(position.getX() + 0, position.getY() + 15, 4, colors[c2]);
	DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 18, position.getY() + 15, 4, colors[c1]);
	DrawSquare(position.getX() + 21, position.getY() + 15, 4, colors[c2]);
	//----------------------------------------------------------------------
	DrawSquare(position.getX() + 3, position.getY() + 18, 4, colors[c2]);
	DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[c1]);
	DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[c1]);
	DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[c1]);
	DrawSquare(position.getX() + 15, position.getY() + 18, 4, colors[c1]);
	DrawSquare(position.getX() + 18, position.getY() + 18, 4, colors[c2]);
	//----------------------------------------------------------------------
	DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[c2]);
	DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[c2]);
	DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[c2]);
	DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[c2]);
}
