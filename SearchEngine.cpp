#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "FileProgression.h"
#include <time.h>
#include "IDF.h"

using namespace std;

int main()
{
//    string* subFolderName;
    //fileDirecProgression("new test", subFolderName);
    fileInput();
    cout << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

