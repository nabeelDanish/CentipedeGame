#include "MoveableObject.h"
#include "Position.h"
#ifndef PLAYER_H
#define PLAYER_H
class Player :public MoveableObject
{
private:
	bool isDead;
	short animationFrame;
public:
	Player();
	Player(int, int);
	Player(const Position&);
	//Getter and Setter
	void setIsDead(bool);
	bool getIsDead()const;
	//Move and Draw
	void Draw();
	int Move(int, int board[30][45]);
};
#endif // !PLAYER_H
