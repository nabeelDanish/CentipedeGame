#include "GameObject.h"
#include "Position.h"
#ifndef MUSHROOM_H
#define MUSHROOM_H
class Mushroom :public GameObject 
{
private:
	int health;
	bool isPoisnous;
public:
	Mushroom();
	Mushroom(int, int);
	Mushroom(const Position&);
	//Getter and Setters
	void setHealth(int);
	int getHealth()const;
	void setIsPoisnous(bool);
	bool getIsPoisnous()const;
	//Draw
	void Draw();
};
#endif // !MUSHROOM_H
