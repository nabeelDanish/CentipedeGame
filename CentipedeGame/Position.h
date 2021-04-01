#ifndef POSITION_H
#define POSITION_H
class Position
{
private:
	int x;
	int y;
	int gridX;
	int gridY;
	int cellsize;
public:
	Position();
	Position(int, int);
	void setValues(int, int);
	//Getter and Setters
	//Getter
	int getX()const;
	int getY()const;
	int getGridX()const;
	int getGridY()const;
	//Setters
	void setGridX(int);
	void setGridY(int);
};
#endif // !POSITION_H
