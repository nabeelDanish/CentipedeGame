#include "GameObject.h"
#include "Position.h"
#include "util.h"
GameObject::GameObject()
{
	setActive(1);
	position.setValues(0, 0);
	setColors(GREEN, RED, WHITE);
}
GameObject::GameObject(int x_grid, int y_grid)
{
	setActive(1);
	position.setValues(x_grid, y_grid);
	setColors(GREEN, RED, WHITE);
}
GameObject::GameObject(const Position&pos)
{
	setActive(1);
	setPosition(pos);
	setColors(GREEN, RED, WHITE);
}
void GameObject::setActive(bool active)
{
	isActive = active;
}
void GameObject::setPosition(const Position&pos)
{
	position = pos;
}
void GameObject::setID(int i)
{
	id = i;
}
void GameObject::setColors(int c1, int c2, int c3)
{
	color1 = c1;
	color2 = c2;
	color3 = c3;
}
int GameObject::getID()const
{
	return id;
}
Position GameObject::getPosition()const
{
	return position;
}
bool GameObject::getActive()const
{
	return isActive;
}