/*
    Author: Tanish Bhongade
    Credits: "https://www.flaticon.com/free-icons/rubik"
*/
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include "../libraries/main_header.h"
using namespace std;

/*
 *	GetAsyncKeyState(int vKey) is a Windows API which takes virtual key code as a character:
 *	0x52 represents R key
 *	0x45 represents E key
 *	Pressing R key will create a new scramble
 *	Pressing E key will exit the program
 */

int main()
{
    char scrambleArray[100];
    int timeTaken;
    // std::ofstream file;
    // file.open("times.txt",std::ios::app);

    while (true)
    {
        runTimer(scrambleArray);
        // file<<scrambleArray<<"::"<<timeTaken<<"\n";
    }
    // file.close();
    return 0;
}