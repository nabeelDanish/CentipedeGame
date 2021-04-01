#include "Position.h"
Position::Position()
{
	cellsize = 24;
	setValues(0, 0);
}
Position::Position(int x_grid, int y_grid)
{
	cellsize = 24;
	setValues(x_grid, y_grid);
}
void Position::setValues(int x_grid, int y_grid)
{
	setGridX(x_grid);
	setGridY(y_grid);
}
void Position::setGridX(int x_grid)
{
	gridX = x_grid;
	x = gridX * cellsize;
}
void Position::setGridY(int y_grid)
{
	gridY = y_grid;
	y = (29 - y_grid) * cellsize;
}
int Position::getGridX()const
{
	return gridX;
}
int Position::getGridY()const
{
	return gridY;
}
int Position::getX()const
{
	return x;
}
int Position::getY()const
{
	return y;
}