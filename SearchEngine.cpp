#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "FileProgression.h"
#include <time.h>
#include "IDF.h"
#include "TF.h"

using namespace std;

int main()
{
    //string* subFolderName;
    //fileDirecProgression("new test"/*, subFolderName*/);
    //fileInput();
    createMetadata("new test");
    /*ifstream subfol("SubFolderName.txt", ios::in);
    string folder = "";
    int x = 0;
    char file[30];
    while (getline(subfol, folder)) {
        string path = string("metadata\\") + folder;
        IDF_list idf = createIDF(path);
        sprintf(file, "metadata\\%d.idf", x);
        SaveIDFList(file, idf);
        x++;
        FreeIDFList(idf);
    }

    subfol.close();*/

    cout << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

