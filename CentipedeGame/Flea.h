#include "MoveableObject.h"
#include "Position.h"
#ifndef FLEA_H
#define FLEA_H
class Flea :public MoveableObject
{
private:
	int animationFrame;
public:
	Flea();
	Flea(int, int);
	Flea(const Position&);
	//Draw and Move
	void Draw();
	int Move(int, int board[30][45]);
	//Dropping Mushrooms, while Checking Conditions
};
#endif // !FLEA_H
