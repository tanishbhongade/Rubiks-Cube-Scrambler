#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "libraries/mainHeader.h"

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

int randomNum()
{
	// Generates a random integer
	int a = rand() % (100 + 1);
	return a;
}

void scrambler(char *scrambleArray)
{
	char setArray[6] = {'U', 'F', 'B', 'D', 'R', 'L'};
	srand(time(0));
	int i = 1;
	char completedMove = 0;
	int totalNum;
	int inputLength = 20;
	int j = 0;

	while (i++ < 40)
	{
		bool doTwo = false;
		bool addOne = false;
		bool ignore = false;
		int r = randomNum();
		int initFirst = (r % 10);
		int initNon = ((int)(r / 10));
		if ((initNon) > 5)
		{
			addOne = true;
		}
		if ((((initNon)*3) % 10) > 3)
		{
			doTwo = true;
		}
		if (initFirst > 5)
		{
			initFirst = initFirst / 2;
		}
		char turn;
		turn = setArray[initFirst];
		r /= 10;
		if (turn != completedMove)
		{
			if (addOne == true && ignore == false)
			{
				if (doTwo == true)
				{
					// cout << turn << "2";
					scrambleArray[j] = turn;
					j++;
					scrambleArray[j] = '2';
					// scrambleArray[++j]=' ';
					j++;
				}
				else
				{
					// cout << turn << "'";
					scrambleArray[j] = turn;
					j++;
					scrambleArray[j] = char(39);
					// scrambleArray[++j]=' ';
					j++;
				}
			}
			else if (addOne != true && ignore == false)
			{
				if (doTwo == true)
				{
					// cout << turn << "2";
					scrambleArray[j] = turn;
					j++;
					scrambleArray[j] = '2';
					// scrambleArray[++j]=' ';
					j++;
				}
				else
				{
					// cout << turn;
					scrambleArray[j] = turn;
					// scrambleArray[++j]=turn;
					j++;
				}
			}
			if (ignore == false)
			{
				// cout << " ";
				scrambleArray[j] = ' ';
				j++;
			}
		}

		completedMove = turn;
	}
	std::cout << std::endl;
}

void printScramble(char *scrambleArray)
{
	int i = 0;

	scrambler(scrambleArray);

	while (i < 100)
	{
		if (scrambleArray[i] == 'R' || scrambleArray[i] == 'U' || scrambleArray[i] == 'F' || scrambleArray[i] == 'D' || scrambleArray[i] == 'B' || scrambleArray[i] == 'L' || scrambleArray[i] == char(39) || scrambleArray[i] == '2' || scrambleArray[i] == ' ')
		{
			std::cout << scrambleArray[i];
			i++;
		}
		else
		{
			break;
		}
	}
	std::cout << std::endl;
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
	printScramble(scrambleArray);
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