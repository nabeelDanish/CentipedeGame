#include "GameObject.h"
#include <string>
using namespace std;
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
class ScoreBoard :public GameObject
{
private:
	int numLives;
	int score;
	int level;
public:
	ScoreBoard();
	ScoreBoard(int, int);
	ScoreBoard(const Position&);
	//Getter and Setters
	//Setters
	void setNumLives(int);
	void setScore(int);
	void setLevel(int);
	//Getters
	int getNumLives()const;
	int getScore()const;
	int getLevel()const;
	//Other Function
	void increaseScore(int);
	void increaseLives(int);
	bool gameEnd()const;
	void reset();
	//Draw Function
	void Draw();
};
#endif // !SCOREBOARD_H
