#include "MoveableObject.h"
#include "Position.h"
#ifndef LASER_H
#define LASER_H
class Laser :public MoveableObject 
{
private:
public:
	Laser();
	Laser(int, int);
	Laser(const Position&);
	//Draw and Move
	void Draw();
	int Move(int, int board[30][45]);
};
#endif // !LASER_H
