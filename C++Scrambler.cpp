#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include "allFuncHeaders.h"
using namespace std;

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
			// * Press E and quit the program by adding a break here
			break;
		}

		if (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 0)
		{
			// * If R is not pressed, stop the current iteration and run the next iteration
			continue;
		}

		if (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 1)
		{
			// * If R is pressed run generate a new scramble by calling the scrambler()
			scrambler();
			runTimer();
			// * If R is kept pressed after running scrambler() calling the below function will stop printing scramble more than once on one key press
			// ! Do no remove doNothing() or below lines or else it'll mess up everything
			while (((GetAsyncKeyState(0x52) == 0) ? 0 : 1) == 1)
			{
				// * Call doNothing() function
				doNothing();
			}
		}
	}
	std::cout << "End" << std::endl;
	return 0;
}