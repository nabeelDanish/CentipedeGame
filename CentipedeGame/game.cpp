//============================================================================
// Name        : CENTIPEDE GAME
// Author      : NABEEL DANISH		i18-0579
// Version     : 
// Copyright   : (c) Reserved
// Description : ATARI 2600 CENTIPEDE GAME
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "Board.h"
#include "util.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
Board *b;
int paused = 0;
void GameDisplay()/**/ 
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	//Drawing Functions
	b->Draw();
	glutSwapBuffers(); // do not modify this line..
	if (!paused)
	{
		glutPostRedisplay();
	}
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT ) 
	{
		if ((b->gameStarted) && (b->playerDyingAnimation == 0))
		{
			b->creatures[0]->Move(0, b->board_array);
		}
	}
	else if (key == GLUT_KEY_RIGHT) 
	{
		if ((b->gameStarted) && (b->playerDyingAnimation == 0))
		{
			b->creatures[0]->Move(1, b->board_array);
		}
	}
	else if (key == GLUT_KEY_UP) 
	{
		if ((b->gameStarted) && (b->playerDyingAnimation == 0))
		{
			b->creatures[0]->Move(2, b->board_array);
		}
	}

	else if (key == GLUT_KEY_DOWN) 
	{
		if ((b->gameStarted) && (b->playerDyingAnimation == 0))
		{
			b->creatures[0]->Move(3, b->board_array);
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	if (!paused)
	{
		glutPostRedisplay();
	}

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		//do something if b is pressed
		cout << "b pressed" << endl;
		b->displayValues();

	}
	if (key == ' ')
	{
		b->Create(6);
	}
	if (key == 'P' || key == 'p')
	{
		if (paused)
		{
			paused = 0;
		}
		else
		{
			paused = 1;
		}
		cout << "Paused = " << paused << endl;
	}
	if (!paused)
	{
		glutPostRedisplay();
	}
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) 
{

	// implement your functionality here
	// once again we tell the library to call our Timer function after next 200/FPS
	if (!paused)
	{
		b->Update();
	}
	if (b->mainMenu == 0)
	{
		glutTimerFunc(25, Timer, 0);
	}
	else
	{
		glutTimerFunc(50, Timer, 0);
	}
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) 
{
	cout << x << " " << y << endl;
	if (!paused)
	{
		glutPostRedisplay();
	}
}
void MouseMoved(int x, int y) 
{

	if (!paused)
	{
		glutPostRedisplay();
	}
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) 
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}
	if (!paused)
	{
		glutPostRedisplay();
	}
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) 
{
	srand(time(NULL));
	b = new Board(24, 24); // create a new board object to use in the Display Function ...
	int width = 1080, height = 720; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay);
	glutTimerFunc(200.0, Timer, 0);
// tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
