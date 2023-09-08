#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include "../libraries/main_header.h"

constexpr char moveSet[] = {'R', 'U', 'F', 'D', 'L', 'B'}; // Move-set
constexpr char moveSpecSet[] = {' ', '2', char(39)};	   // Move-set specialisation
constexpr int highestScrambleLength = 25;				   // Highest scramble length
constexpr int lowestScrambleLength = 20;				   // Lowest scramble length

inline bool spacePressed()
{
	// Return false if spacebar is pressed else true
	return (GetAsyncKeyState(VK_SPACE) == 0) ? false : true;
}

inline bool rPressed()
{
	// Return false if R is pressed else true
	return (GetAsyncKeyState(0x52) == 0) ? false : true;
}

inline bool ePressed()
{
	// Return false if E is pressed else true
	return (GetAsyncKeyState(0x45) == 0) ? false : true;
}

inline void doNothing()
{
	// Does as its name
}

inline int randomNum(int lowerLimit, int upperLimit)
{
	// Generates scramble between the specified limit
	return (lowerLimit + (rand() % (upperLimit - lowerLimit + 1)));
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
	// This function is responsible for generation of scramble which is of good quality
	char previousMove, currentMove;												 // Variables for holding previously done and current move to be done
	int moveToDo, moveSpecToDo;													 // Indexes for moveSet and moveSpecialisationSet
	int scramblePt = 1;															 // Variable for current scramble point
	int scrambleLength = randomNum(lowestScrambleLength, highestScrambleLength); // Before generation of scramble, it'll hold randomly generated scramble length between 20 and 25

	// ! Below is a debug statement, toggle only if you wish to print scramble length before scramble
	// std::cout<<"("<<scrambleLength<<")"<<" ";
	std::vector<char> scramble; // Helper scramble vector for generating scramble

	// Set up initial move and move specialisation
	moveToDo = randomNum(0, 5);		// 0 and 5 are inputs because index of moveSet can vary between 0 and 5.
	moveSpecToDo = randomNum(0, 2); // 0 and 2 are inputs because index of moveSpecSet can vary between 0 and 2.

	// Push move to scramble vector
	currentMove = moveSet[moveToDo];
	scramble.push_back(currentMove);

	if (moveSpecToDo != 0)
	{
		// If moveSpecToDo==1 append '2' or if moveSpecToDo==2 append inverted comma
		scramble.push_back(moveSpecSet[moveSpecToDo]);
		scramble.push_back(' ');
	}
	else if (moveSpecToDo == 0)
	{
		// If standard move is chosen, push blank to scramble
		scramble.push_back(' ');
	}

	// Main scramble generation loop
	while (scramblePt < scrambleLength)
	{
		// Set up initial move and move specialisation
		moveToDo = randomNum(0, 5);		// 0 and 5 are inputs because index of moveSet can vary between 0 and 5.
		moveSpecToDo = randomNum(0, 2); // 0 and 2 are inputs because index of moveSpecSet can vary between 0 and 2.

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
			// If moveSpecToDo==1 append '2' or if moveSpecToDo==2 append inverted comma
			scramble.push_back(moveSpecSet[moveSpecToDo]);
			scramble.push_back(' ');
		}
		else if (moveSpecToDo == 0)
		{
			// If standard move is chosen, push blank-space to scramble
			scramble.push_back(' ');
		}
		// After completing each move, increment scramblePt
		scramblePt++;
	}
	// Return scramble vector
	return scramble;
}

double phaseOne()
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
		return double(double(finalTime - initialTime) / double(CLOCKS_PER_SEC));
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
	double timeTaken;
	for (int i = 0; i < scramble.size(); i++)
	{
		// Prints scramble
		std::cout << scramble.at(i);
	}
	std::cout << "\n";
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

	// The below code pushes scramble and solve to external file for more calculations
	timeTaken = phaseOne();
	std::ofstream file;
	file.open("main/times.txt", std::ios::app);
	for (int i = 0; i < scramble.size(); i++)
	{
		file << scramble.at(i);
	}
	file << ":: " << timeTaken << "s"
		 << "\n";
	file.close();

	phaseTwo();
}