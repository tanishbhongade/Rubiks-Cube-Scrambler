#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include "libraries/mainHeader.h"

const char moveSet[] = {'R', 'U', 'F', 'D', 'L', 'B'};
const char moveSpecSet[] = {' ', '2', char(39)};

inline bool spacePressed()
{
	return (GetAsyncKeyState(VK_SPACE) == 0) ? false : true;
}

inline bool rPressed()
{
	return (GetAsyncKeyState(0x52) == 0) ? false : true;
}

inline bool ePressed()
{
	return (GetAsyncKeyState(0x45) == 0) ? false : true;
}

inline void doNothing()
{
}

inline int randomNum(int lowerLimit, int upperLimit)
{
	// Generates scramble between the specified limit
	return (lowerLimit + (rand() % (upperLimit + 1)));
}

char getOppositeMove(char move)
{
	// Returns opposite move
	if (move == 'R')
	{
		// L is opposite of R
		return 'L';
	}
	else if (move == 'U')
	{
		// Same as first condition
		return 'D';
	}
	else if (move == 'F')
	{
		return 'B';
	}
	else if (move == 'D')
	{
		return 'U';
	}
	else if (move == 'L')
	{
		return 'R';
	}
	else if (move == 'B')
	{
		return 'F';
	}
}

std::vector<char> scrambler()
{
	// Responsible for generation of scramble
	char previousMove, currentMove; // Variables
	int moveToDo, moveSpecToDo;		// Indexes for moveSet and moveSpecialisationSet
	int scramblePt = 1;				// Shows current scramble point
	std::vector<char> scramble;		// Helper scramble vector for generating scramble

	// Set up initial move and move specialisation
	moveToDo = randomNum(0, 5);
	moveSpecToDo = randomNum(0, 2);

	// Push move to scramble vector
	currentMove = moveSet[moveToDo];
	scramble.push_back(currentMove);

	if (moveSpecToDo != 0)
	{
		// If moveSpec != 0 there are two conditions possible
		if (moveSpecToDo == 1)
		{
			// If double move is chosen, push double move to scramble
			scramble.push_back('2');
			scramble.push_back(' ');
		}
		else if (moveSpecToDo == 2)
		{
			// If inverse is chosen, push inverted comma to scramble
			scramble.push_back(char(39));
			scramble.push_back(' ');
		}
	}
	else if (moveSpecToDo == 0)
	{
		// If standard move is chosen, push blank to scramble
		scramble.push_back(' ');
	}

	// Main scramble generation loop
	while (scramblePt <= 20)
	{
		// Set up initial move and move specialisation
		moveToDo = randomNum(0, 5);
		moveSpecToDo = randomNum(0, 2);

		previousMove = currentMove;		 // Make previousMove = currentMove
		currentMove = moveSet[moveToDo]; // Assign currentMove as new generated move

		while (previousMove == currentMove || previousMove == getOppositeMove(currentMove))
		{
			// Keep generating currentMove until previousMove and currentMove are not equal or previousMove and currentMove's opposite move are not equal
			moveToDo = randomNum(0, 5);
			currentMove = moveSet[moveToDo];
		}
		// After generating currentMove, push it to scramble vector
		scramble.push_back(currentMove);

		if (moveSpecToDo != 0)
		{
			// If moveSpec != 0 there are two conditions possible
			if (moveSpecToDo == 1)
			{
				// If double move is chosen, push double move to scramble
				scramble.push_back('2');
				scramble.push_back(' ');
			}
			else if (moveSpecToDo == 2)
			{
				// If inverse is chosen, push inverted comma to scramble
				scramble.push_back(char(39));
				scramble.push_back(' ');
			}
		}
		else if (moveSpecToDo == 0)
		{
			// If standard move is chosen, push blank-space to scramble
			scramble.push_back(' ');
		}
		// After completing each move, increment scramblePt
		scramblePt++;
	}
	// After everything, make last character as newline in scramble vector
	scramble.push_back('\n');
	// Return scramble vector
	return scramble;
}

void phaseOne()
{
	// This function is solely responsible for calculating time passed between solve
	clock_t initialTime = 0; // This variable holds initial time
	clock_t finalTime = 0;	 // This variable holds final time

	std::cout << "Solve!" << std::endl;
	initialTime = clock(); // Assigning initial time

	while (spacePressed() == false)
	{
		// This spacePressed()==false will ensure to do nothing if space is not pressed.
		doNothing();
	}
	if (spacePressed() == true)
	{
		// As soon as space is pressed
		finalTime = clock(); // Record time after solve
		while (spacePressed() == true)
		{
			// Keep doing nothing after once time has been captured and space is kept pressed
			doNothing();
		}
		// After leaving space bar, print time passed.
		std::cout << "Time passed is " << double(double(finalTime - initialTime) / double(CLOCKS_PER_SEC));
	}
}

void phaseTwo()
{
	// std::cout << "Inside phaseTwo() timer" << std::endl;
	while (true)
	{
		// After phaseOne() runs until R is not pressed, do nothing
		if (rPressed() == false)
		{
			doNothing();
			// Keep checking whether e is not pressed or not
			if (ePressed() == true)
			{
				// If e is pressed exit the program
				exit(0);
			}
		}
		// If r is pressed, enter else if statement
		else if (rPressed() == true)
		{
			while (rPressed() == true)
			{
				// Once r is pressed, keep doing nothing if r is pressed more than once
				doNothing();
			}
			// Clear terminal after doing all this
			system("cls");
			return; // Go back to runTimer()
		}
	}
}

void beforeTimerRuns()
{
	while (spacePressed() == false)
	{
		// Until space bar is not pressed keep doing nothing
		doNothing();
	}
	if (spacePressed() == true)
	{
		// As soon as space is pressed enter this if condition
		std::cout << "Space pressed!" << std::endl;
		while (spacePressed() == true)
		{
			// Once this loop is entered it will keep doing nothing until space is pressed
			doNothing();
		}
		return;
	}
}

void runTimer(char *scrambleArray)
{
	// printScramble(scrambleArray);
	srand(time(0));
	std::vector<char> scramble = scrambler();
	for (int i = 0; i < scramble.size(); i++)
	{
		// Prints scramble
		std::cout << scramble.at(i);
	}

	while (rPressed() == false && spacePressed() == false && ePressed() == false)
	{
		// While r is not pressed, space is not pressed and e is not pressed, do nothing
		doNothing();
	}
	while (rPressed() == true && ePressed() == false && spacePressed() == false)
	{
		// While r is pressed, space is not pressed and e is not pressed, do nothing
		doNothing();
	}
	if (rPressed() == false && ePressed() == false && spacePressed() == false)
	{
		// After releasing r, clear screen and return to main()
		system("cls");
		return;
	}
	while (ePressed() == false && spacePressed() == false && rPressed() == false)
	{
		// While e is pressed, space is not pressed, r is not pressed, do nothing
		doNothing();
	}
	if (ePressed() == true && spacePressed() == false && rPressed() == false)
	{
		// If e is pressed, the program will stop execution
		exit(0);
	}

	beforeTimerRuns();
	phaseOne();
	phaseTwo();
}