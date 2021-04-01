#include "Segment.h"
#include "MoveableObject.h"
#include <vector>
using namespace std;
#ifndef CENTIPEDE_H
#define CENTIPEDE_H
class Centipede :public MoveableObject
{
private:
	int animationFrame;
	int numSegments;
	vector<Segment*> body;
	bool reachedPlayArea;
	//--------------------------
	bool isMagic;
	int interval;
	int duration;
	int start;
	//-------------------------
	bool touchedPoisnous;
public:
	Centipede();
	Centipede(int, int, int, int board[30][45]);
	//Move and Draw Functions
	//Getter and Setters
	bool getIsMagic()const;
	void setIsMagic(bool);
	void Draw();
	int Move(int, int board[30][45]);
	int checkCollision(int board[30][45]);
};
#endif // !CENTIPEDE_H
