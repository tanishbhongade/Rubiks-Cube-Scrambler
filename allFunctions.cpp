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

void runTimer(){

}