#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include "util.h"
#include "Segment.h"
using namespace std;
Segment::Segment()
{
	id = 7;
	isMagic = 0;
	animationFrame = 0;
}
Segment::Segment(int x_grid, int y_grid) :MoveableObject(x_grid, y_grid)
{
	id = 7;
	isMagic = 0;
	animationFrame = 0;
}
Segment::Segment(const Position&pos) : MoveableObject(pos)
{
	id = 7;
	isMagic = 0;
	animationFrame = 0;
}
void Segment::setIsMagic(bool mg)
{
	isMagic = mg;
}
bool Segment::getisMagic()const
{
	return isMagic;
}