#include "Position.h"
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
class GameObject
{
protected:
	int id;
	Position position;
	bool isActive;
	int color1;
	int color2;
	int color3;
public:
	GameObject();
	GameObject(int, int);
	GameObject(const Position&);
	//Getter and Setters
	//Setters
	void setPosition(const Position&);
	void setActive(bool);
	void setID(int);
	void setColors(int, int, int);
	//Getter
	Position getPosition()const;
	bool getActive()const;
	int getID()const;

	//Draw Function
	virtual void Draw() = 0;
};
#endif // !GAME_OBJECT_H
