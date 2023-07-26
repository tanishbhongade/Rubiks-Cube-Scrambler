#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
using namespace std;

inline void doNothing()
{
}

int randomNum()
{
	int a = rand() % (100 + 1);
	return a;
}

int scrambler(char *scrambleArray)
{
	char setArray[6] = {'U', 'F', 'B', 'D', 'R', 'L'};
	srand(time(0));
	int i = 1;
	char completedMove;
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
					scrambleArray[++j] = '2';
					// scrambleArray[++j]=' ';
					j++;
				}
				else
				{
					// cout << turn << "'";
					scrambleArray[j] = turn;
					scrambleArray[++j] = char(39);
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
					scrambleArray[++j] = '2';
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
				scrambleArray[j++] = ' ';
			}
		}

		completedMove = turn;
	}
	cout << "\n";
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

inline bool spacePressed()
{
	return (GetAsyncKeyState(VK_SPACE) == 0) ? 0 : 1;
}

inline bool rPressed()
{
	return (GetAsyncKeyState(0x52) == 0) ? 0 : 1;
}

inline bool ePressed()
{
	return (GetAsyncKeyState(0x45) == 0) ? 0 : 1;
}

void phaseOne()
{
	clock_t initialTime = 0;
	clock_t finalTime = 0;

	std::cout << "Solve!" << std::endl;
	initialTime = clock();
	while (spacePressed() == false)
	{
		if (spacePressed() == true)
		{
			finalTime = clock();
			while (spacePressed() == true)
			{
				doNothing();
			}
			std::cout << "Time passed is " <<double(double(finalTime-initialTime)/double(CLOCKS_PER_SEC));
			break;
		}
	}
}

void runTimer(char *scrambleArray)
{
	while (true)
	{
		printScramble(scrambleArray);
		while (spacePressed() == false)
		{
			doNothing();
		}
		if (spacePressed() == true)
		{
			std::cout << "Space pressed!" << std::endl;
			while (spacePressed() == true)
			{
				doNothing();
			}
			phaseOne();
			while (true)
			{
				if (rPressed() == false)
				{
					doNothing();
					if (ePressed() == true)
					{
						exit(0);
					}
				}
				else if (rPressed() == true)
				{
					while (rPressed() == true)
					{
						doNothing();
					}
					system("cls");
					runTimer(scrambleArray);
				}
			}
		}
	}
}