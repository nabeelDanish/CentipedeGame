#include "GameObject.h"
#include "Position.h"
#ifndef MOVEABLE_OBJECT_H
#define MOVEABLE_OBJECT_H
class MoveableObject :public GameObject
{
protected:
	int direction;
public:
	MoveableObject();
	MoveableObject(int, int);
	MoveableObject(const Position&);
	//Getter and Setter
	int getDirection()const;
	void setDirection(int);
	//Draw and Move
	virtual int Move(int, int board[30][45]) = 0;
};
#endif // !MOVEABLE_OBJECT_H
