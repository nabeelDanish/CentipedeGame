#include "MoveableObject.h"
#include "Position.h"
#ifndef SCORPIO_H
#define SCORPIO_H
class Scorpio :public MoveableObject
{
private:
	int animationFrame;
public:
	Scorpio();
	Scorpio(int, int);
	Scorpio(const Position&);
	//Draw and Move Functions
	void Draw();
	int Move(int, int board[30][45]);
};
#endif // !SCORPIO
