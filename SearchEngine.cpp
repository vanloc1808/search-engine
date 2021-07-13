#include <iostream>
#include <ctime>
#include "UI.h"

using namespace std;

int main()
{
	menu();
	cout << "Session ended, time taken: " << static_cast<double>(clock()) / CLOCKS_PER_SEC << " secs." << endl;
    return 0;
}