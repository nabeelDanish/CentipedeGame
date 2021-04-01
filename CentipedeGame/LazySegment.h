#include "Segment.h"
#ifndef LAZYSEGMENT_H
#define LAZYSEGMENT_H
class LazySegment :public Segment
{
public:
	LazySegment();
	LazySegment(int,int);
	LazySegment(const Position&);
	//Draw and Move Functions
	void Draw();
	int Move(int, int board[30][45]);
};
#endif // !LAZYSEGMENT_H
