#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "Player.h"
#include "util.h"
Player::Player()
{
	id = 4;
	isDead = 0;
	animationFrame = 0;
}
Player::Player(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	id = 4;
	isDead = 0;
	animationFrame = 0;
}
Player::Player(const Position&pos) : MoveableObject(pos)
{
	id = 4;
	isDead = 0;
	animationFrame = 0;
}
//Getter and Setters
void Player::setIsDead(bool d)
{
	isDead = d;
}
bool Player::getIsDead()const
{
	return isDead;
}

void Player::Draw()
{
		//--------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 0, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color3]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[color3]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 6, 4, colors[color3]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[color3]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color3]);
		DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color3]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color2]);
		DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[color2]);
		DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color2]);
		DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color2]);
		DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color3]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[color2]);
		DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[color2]);
		DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[color2]);
		DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[color2]);
		//--------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[color3]);
		DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[color3]);
		//---------------------------------------------------------
		DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[color3]);
}
int Player::Move(int direction, int board[30][45])
{
	switch (direction)
	{
	case 0:
	{
		if ((position.getGridX() > 0) && (board[position.getGridY()][position.getGridX() - 1] == 0))
		{
			board[position.getGridY()][position.getGridX()] = 0;
			position.setGridX(position.getGridX() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 1:
	{
		if ((position.getGridX() < 44) && (board[position.getGridY()][position.getGridX() + 1] == 0))
		{
			board[position.getGridY()][position.getGridX()] = 0;
			position.setGridX(position.getGridX() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 2:
	{
		if ((position.getGridY() > 25) && (board[position.getGridY() - 1][position.getGridX()] == 0))
		{
			board[position.getGridY()][position.getGridX()] = 0;
			position.setGridY(position.getGridY() - 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	case 3:
	{
		if ((position.getGridY() < 31) && (board[position.getGridY() + 1][position.getGridX()] == 0))
		{
			board[position.getGridY()][position.getGridX()] = 0;
			position.setGridY(position.getGridY() + 1);
			board[position.getGridY()][position.getGridX()] = id;
		}
		break;
	}
	}
	return 0;
}