#include "MoveableObject.h"
#include "Position.h"
MoveableObject::MoveableObject()
{
	//EMPTY
}
MoveableObject::MoveableObject(int x_grid, int y_grid) :GameObject(x_grid, y_grid)
{
	//EMPTY
}
MoveableObject::MoveableObject(const Position&pos) : GameObject(pos)
{
	//EMPTY
}
int MoveableObject::getDirection()const
{
	return direction;
}
void MoveableObject::setDirection(int d)
{
	direction = d;
}