#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <time.h>
#include "FileProgression.h"


using namespace std;

int main()
{
	//createMetadata("new test");

	loadToRAM();
	cout << (double)clock() / CLOCKS_PER_SEC << endl;

	cout << "Enter keyword.\n";

	string sentence;
	getline(cin, sentence);
	testSentence(sentence);

	cout << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

