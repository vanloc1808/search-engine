#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <time.h>
#include "FileProgression.h"


using namespace std;

int main()
{
	createMetadata("new test");

    cout << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

