#include "MoveableObject.h"
#include "Position.h"
#ifndef SPIDER_H
#define SPIDER_H
class Spider :public MoveableObject
{
private:
	int animationFrame;
	int changeDirection;
public:
	Spider();
	Spider(int, int);
	Spider(const Position&);
	//Draw and Move Function
	void Draw();
	int Move(int, int board[30][45]);
	bool checkCollision(int board[30][45]);
};
#endif // !SPIDER_H
