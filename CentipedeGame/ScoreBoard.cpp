#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "util.h"
#include "ScoreBoard.h"
ScoreBoard::ScoreBoard()
{
	isActive = 1;
	numLives = 3;
	score = 0;
	level = 1;
}
ScoreBoard::ScoreBoard(int x_grid, int y_grid) :GameObject(x_grid, y_grid)
{
	isActive = 1;
	numLives = 3;
	score = 0;
	level = 1;
}
ScoreBoard::ScoreBoard(const Position&pos) :GameObject(pos)
{
	isActive = 1;
	numLives = 3;
	score = 0;
	level = 1;
}
//======================================Getter and Setters
//------------------------Setters
void ScoreBoard::setNumLives(int nLives)
{
	numLives = nLives;
}
void ScoreBoard::setScore(int s)
{
	score = s;
}
void ScoreBoard::setLevel(int l)
{
	level = l;
}
//------------------------Getters
int ScoreBoard::getNumLives()const
{
	return numLives;
}
int ScoreBoard::getScore()const
{
	return score;
}
int ScoreBoard::getLevel()const
{
	return level;

}
//======================================Other Function
void ScoreBoard::increaseScore(int s)
{
	score += s;
}
void ScoreBoard::increaseLives(int lives)
{
	numLives += lives;
}
bool ScoreBoard::gameEnd()const
{
	if (numLives <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void ScoreBoard::reset()
{
	isActive = 1;
	numLives = 3;
	score = 0;
	level = 1;
}
//======================================Draw Function
void ScoreBoard::Draw()
{
	string scoreString = Num2Str(score);
	string liveString = Num2Str(numLives);
	string levelString = Num2Str(level);
	DrawString(position.getX() + 2, position.getY() + 5, "SCORE = ", colors[color3]);
	DrawString(position.getX() + 75, position.getY() + 5, scoreString, colors[color3]);
	DrawString(position.getX() + 250, position.getY() + 5, "LIVES = ", colors[color3]);
	DrawString(position.getX() + 320, position.getY() + 5, liveString, colors[color3]);
	DrawString(position.getX() + 400, position.getY() + 5,"LEVEL = ", colors[color3]);
	DrawString(position.getX() + 480, position.getY() + 5, levelString, colors[color3]);
}