#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "Centipede.h"
#include "Segment.h"
#include "util.h"
#include "LazySegment.h"
#include "MagicSegment.h"
using namespace std;
Centipede::Centipede()
{
	id = 8;
	numSegments = 0;
	direction = 1;
	reachedPlayArea = 0;
	animationFrame = 0;
	isMagic = 0;
	interval = (rand() % 7) + 2;
	start = 0;
	duration = 2;
	touchedPoisnous = 0;

}
Centipede::Centipede(int x_grid, int y_grid, int n_s,int board[30][45]) :MoveableObject(x_grid, y_grid)
{
	id = 8;
	direction = 1;
	reachedPlayArea = 0;
	numSegments = n_s;
	animationFrame = 0;
	isMagic = 0;
	interval = (rand() % 7) + 2;
	start = 0;
	duration = 2;
	touchedPoisnous = 0;
	if (numSegments != 0)
	{
		body.resize(numSegments);
	}
	for (int i = 0; i < numSegments; ++i)
	{
		Position temp(position.getGridX() - i - 1, position.getGridY());
		int draw = rand() % 5;
		switch (draw)
		{
		case 0:
		case 1:
		case 2:
		case 3:	body[i] = new LazySegment(temp); break;
		case 4: body[i] = new MagicSegment(temp); break;
		}
		board[position.getGridY()][position.getGridX() - i - 1] = body[i]->getID();
	}
}

//---------------------------------------------Getter and Setters
//---------------Getter
bool Centipede::getIsMagic()const
{
	return isMagic;
}

//---------------Setter
void Centipede::setIsMagic(bool m)
{
	isMagic = m;
}

//--------------------------------------[DRAWING FUNCTION]--------------------------------------------------
void Centipede::Draw()
{
	int eyeColor, bodyColor;
	if (!touchedPoisnous)
	{
		direction == 0 ? (eyeColor = color2, bodyColor = color1) : eyeColor = color1, bodyColor = color2;
	}
	else
	{
		direction == 0 ? (eyeColor = color1, bodyColor = color2) : eyeColor = color2, bodyColor = color1;
	}
	if (duration % 10 == 0)
	{
		//------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 3, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 9, position.getY() + 3, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 12, position.getY() + 3, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 15, position.getY() + 3, 4, colors[bodyColor]);
		//------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 6, 4, colors[color1]);
		DrawSquare(position.getX() + 6, position.getY() + 6, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 9, position.getY() + 6, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 12, position.getY() + 6, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 15, position.getY() + 6, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 18, position.getY() + 6, 4, colors[color1]);
		//------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 3, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 6, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 9, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 12, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 9, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 9, 4, colors[color1]);
		//------------------------------------------------------
		DrawSquare(position.getX() + 0, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 3, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 6, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 9, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 12, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 15, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 18, position.getY() + 12, 4, colors[color1]);
		DrawSquare(position.getX() + 21, position.getY() + 12, 4, colors[color1]);
		//------------------------------------------------------
		DrawSquare(position.getX() + 3, position.getY() + 15, 4, colors[color1]);
		DrawSquare(position.getX() + 6, position.getY() + 15, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 9, position.getY() + 15, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 12, position.getY() + 15, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 15, position.getY() + 15, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 18, position.getY() + 15, 4, colors[color1]);
		//------------------------------------------------------
		DrawSquare(position.getX() + 6, position.getY() + 18, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 9, position.getY() + 18, 4, colors[eyeColor]);
		DrawSquare(position.getX() + 12, position.getY() + 18, 4, colors[bodyColor]);
		DrawSquare(position.getX() + 15, position.getY() + 18, 4, colors[bodyColor]);

		//Drawing the Animated Legs
		switch (animationFrame)
		{
		case 4:
		case 0:
			DrawSquare(position.getX() + 12, position.getY() + 0, 4, colors[color3]);
			DrawSquare(position.getX() + 12, position.getY() + 21, 4, colors[color3]);
			break;
		case 3:
		case 1:
			DrawSquare(position.getX() + 15, position.getY() + 0, 4, colors[color3]);
			DrawSquare(position.getX() + 15, position.getY() + 21, 4, colors[color3]);
			break;
		case 2:
			DrawSquare(position.getX() + 18, position.getY() + 0, 4, colors[color3]);
			DrawSquare(position.getX() + 18, position.getY() + 21, 4, colors[color3]);
			break;
		case 5:
		case 7:
			DrawSquare(position.getX() + 9, position.getY() + 0, 4, colors[color3]);
			DrawSquare(position.getX() + 9, position.getY() + 21, 4, colors[color3]);
			break;
		case 6:
			DrawSquare(position.getX() + 6, position.getY() + 0, 4, colors[color3]);
			DrawSquare(position.getX() + 6, position.getY() + 21, 4, colors[color3]);
			break;
		}
	}

	//Setting Colors for the Rest of the Body
	//Drawing the Rest of the Body
	for (int i = 0; i < numSegments; ++i)
	{
		body[i]->setColors(color1, color2, color3);
		body[i]->Draw();
	}
	//increasing the Animation frame
	++animationFrame;
	if (animationFrame > 7)
	{
		animationFrame = 0;
	}

	//Setting the Magic Segment thing
	++start;//--------------Uncomment this line to start the magic thing
	if (duration == 0)
	{
		isMagic = 0;
	}
	if (duration != 0)
	{
		--duration;
	}
	if (start == interval)
	{
		isMagic = 1;
		interval = rand() % 5000;
		start = 0;
		duration = rand() % 500;
	}
}

//------------------------------------[MOVE FUNCTION]------------------------------------------------------

int Centipede::Move(int d, int board[30][45])
{
	//Updating Body Coordinates, Snake Like Movement.
	if (numSegments != 0)
	{
		for (int i = numSegments - 1; i > 0; --i)
		{
			if (i == numSegments - 1)
			{
				board[body[i]->getPosition().getGridY()][body[i]->getPosition().getGridX()] = 0;
			}
			body[i]->setPosition(body[i - 1]->getPosition());
			board[body[i]->getPosition().getGridY()][body[i]->getPosition().getGridX()] = body[i]->getID();
		}
		if (numSegments - 1 == 0)
		{
			board[body[0]->getPosition().getGridY()][body[0]->getPosition().getGridX()] = 0;
		}
		body[0]->setPosition(position);
	}

	//Checking whether have we reached Player Bounds, so that Centipede may stay there.

	if (position.getGridY() == 29)
	{
		reachedPlayArea = 1;
		touchedPoisnous = 0;
		direction = 0;
	}
	else if (position.getGridY() <= 24)
	{
		reachedPlayArea = 0;
	}

	//Checking Collision with Poisnous Mushroom
	int dir_check = 0;
	switch (direction)
	{
	case 0:		dir_check = -1;	break;
	case 1:		dir_check = 1; break;
	default:	dir_check = 0;
	}
	if (board[position.getGridY()][position.getGridX() + dir_check] == 12)
	{
		touchedPoisnous = 1;
		direction = 2;
	}

	//Removing the Trail from the Board Array
	if (numSegments != 0)
	{
		board[position.getGridY()][position.getGridX()] = 7;
	}
	else
	{
		board[position.getGridY()][position.getGridX()] = 0;
	}

	//Main Direction switch
	switch (direction)
	{
		case 0:
		{
			if ((board[position.getGridY()][position.getGridX() - 1] != 5) && (position.getGridX() - 1 >= 0))
			{
				position.setGridX(position.getGridX() - 1);
				board[position.getGridY()][position.getGridX()] = id;
			}
			else
			{
				if ((reachedPlayArea) || (touchedPoisnous))
				{
					position.setGridY(position.getGridY() - 1);
				}
				else
				{
					position.setGridY(position.getGridY() + 1);
					direction = 1;
				}
				board[position.getGridY()][position.getGridX()] = id;
			}
			break;
		}
		case 1:
		{
			if ((board[position.getGridY()][position.getGridX() + 1] != 5) && (position.getGridX() + 1 < 45))
			{
				position.setGridX(position.getGridX() + 1);
				board[position.getGridY()][position.getGridX()] = id;
			}
			else
			{
				if ((reachedPlayArea) || (touchedPoisnous))
				{
					position.setGridY(position.getGridY() - 1);
				}
				else
				{
					position.setGridY(position.getGridY() + 1);
					direction = 0;
				}
				board[position.getGridY()][position.getGridX()] = id;
			}
			break;
		}
		case 2:
		{
			position.setGridY(position.getGridY() + 1);
			board[position.getGridY()][position.getGridX()] = id;
			break;
		}
	}
	return 0;
}

//============================================[MAIN COLLISION DETECTION FUNCTION]==================================

int Centipede::checkCollision(int board[30][45])
{
	//If the Centipede is in Magic State, it will return -2, that will tell the Board class that no Action needs to be taken
	if (isMagic)
	{
		return -2;
	}

	//Else 
	if (board[position.getGridY() + 1][position.getGridX()] == 6)
	{
		if (numSegments != 0)
		{
			//board[body[numSegments - 1]->getPosition().getGridY()][body[numSegments - 1]->getPosition().getGridX()] = 0;
			position.setValues(body[0]->getPosition().getGridX(), body[0]->getPosition().getGridY());
			for (int i = 0; i < numSegments - 1; ++i)
			{
				body[i]->setPosition(body[i + 1]->getPosition());
			}
			if (numSegments > 1)
			{
				body.pop_back();
				--numSegments;
			}
			else
			{
				numSegments = 0;
				body.clear();
			}
			return -1;
		}
		else
		{
			setActive(0);
			board[position.getGridY()][position.getGridX()] = 0;
			return 0;
		}
	}
	else if (numSegments != 0)
	{
		bool collided = 0;
		int index_collided = 0;
		int temp_segment = numSegments;
		for (int i = 0; i < numSegments; ++i)
		{
			if ((board[body[i]->getPosition().getGridY() + 1][body[i]->getPosition().getGridX()] == 6)&&(!body[i]->getisMagic()))
			{
				collided = 1;
				index_collided = i;
				for (int j = i; j < numSegments; ++j)
				{
					board[body[j]->getPosition().getGridY()][body[j]->getPosition().getGridX()] = 0;
				}
				if ((i == 0) && (i == numSegments - 1))
				{
					body.clear();
					numSegments = 0;
					return -1;
				}
				else if (i == numSegments - 1)
				{
					--numSegments;
					body.erase(body.begin() + i);
					return -1;
				}
				else if (i == 0)
				{
					body.clear();
					numSegments = 0;
				}
				else
				{
					body.erase(body.begin() + i, body.begin() + numSegments - 1);
					numSegments -= numSegments - i;
				}
				break;
			}
		}
		if (collided)
		{
			return temp_segment - index_collided - 1;
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -2;
	}
}