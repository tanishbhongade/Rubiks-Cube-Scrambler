#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomNum()
{
	int a = rand() % (100 + 1);
	return a;
}

int scrambler()
{
	char setArray[6] = {'U', 'F', 'B', 'D', 'R', 'L'};
	srand(time(0));
	int i = 0;
	char completedMove;
	int totalNum;
	int inputLength = 20;

	while (i++ < inputLength)
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
					cout << turn << "2";
				}
				else
				{
					cout << turn << "'";
				}
			}
			else if (addOne != true && ignore == false)
			{
				if (doTwo == true)
				{
					cout << turn << "2";
				}
				else
				{
					cout << turn;
				}
			}
			if (ignore == false)
			{
				cout << " ";
			}
		}

		completedMove = turn;
	}
	cout << "\n";
}

void doNothing()
{
}

int main()
{
	std::cout << "Start" << std::endl;
	/*
		GetAsyncKeyState(int vKey) is a Windows API which takes virtual key code as a character:
		*	0x52 represents R key
		*	0x45 represents E key

		*	Pressing R key will create a new scramble
		*	Pressing E key will exit the program
	*/

	while (true)
	{
		if (GetAsyncKeyState(0x45) != 0)
		{
			// Press E and quit the program by adding a break here
			break;
		}

		if (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 0)
		{
			// If R is not pressed, stop the current iteration and run the next iteration
			continue;
		}

		if (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 1)
		{
			// If R is pressed run generate a new scramble by calling the scrambler()
			scrambler();
			// If R is kept pressed after running scrambler() calling the below function will stop printing scramble more than once on one key press
			// ! Do no remove doNothing() or below lines or else it'll mess up everything
			while (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 1)
			{
				// Call doNothing() function
				doNothing();
			}
		}
	}
	std::cout << "End" << std::endl;
	return 0;
}