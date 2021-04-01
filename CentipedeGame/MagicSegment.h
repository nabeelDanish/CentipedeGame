#include "Segment.h"
#ifndef MAGICSEGMENT_H
#define MAGICSEGMENT_H
class MagicSegment :public Segment
{
private:
	int interval;
	int duration;
	int start;
public:
	MagicSegment();
	MagicSegment(int, int);
	MagicSegment(const Position&);
	//Draw and Move
	void Draw();
	int Move(int, int board[30][45]);
};
#endif // !MAGICSEGMENT_H
