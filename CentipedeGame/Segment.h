#include "MoveableObject.h"
#include "Position.h"
#ifndef SEGMENT_H
#define SEGMENT_H
class Segment :public MoveableObject
{
protected:
	bool isMagic;
	int animationFrame;
public:
	Segment();
	Segment(int, int);
	Segment(const Position&);
	//Getter and Setters
	void setIsMagic(bool);
	bool getisMagic()const;
	//Draw and Move Functions
	virtual void Draw() = 0;
	virtual int Move(int, int board[30][45]) = 0;
};
#endif // !SEGMENT_H
