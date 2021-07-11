#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include "FileProgression.h"
#include "UI.h"


using namespace std;

int main()
{
	menu();
	cout << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

