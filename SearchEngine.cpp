#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "FileProgression.h"

using namespace std;

int main()
{
    getSubFolderDirectory("new test");
    string* subFolderName;
    getSubFolderName("new test", subFolderName);

   /* string folderPath;
    string* subFolderName = new string[100];
    int idx = 0;
    ifstream fPath;
    fPath.open("Path.txt");
    ofstream subFolder;
    subFolder.open("SubFolderName.txt");
    system("mkdir metadata");
    char command[100] = { 0 };
    while (getline(fPath, folderPath)) {
        if (folderPath[folderPath.length() - 1] == '\r') {
            folderPath.pop_back();
        }
        int len = folderPath.length();
        if (len == 0) {
            break;
        }
        int pos = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (folderPath[i] == '\\') {
                pos = i;
                break;
            }
        }
        subFolderName[idx] = "new test\\";
        string name = "metadata\\";
        int tempPos = pos + 1;
        for (; pos < len; pos++) {
            subFolderName[idx] += folderPath[pos];
            name += folderPath[pos];
        } 
        for (; tempPos < len; tempPos++) {
            subFolder << folderPath[tempPos];
        }
        subFolder << "\n";
        name += ".txt";
        sprintf(command, "dir \"%s\" /s /b /o:n > \"%s\"", subFolderName[idx].c_str(), name.c_str());
        system(command);
        idx++;
    }
    delete[]subFolderName;
    fPath.close();
    subFolder.close();*/

    return 0;
}

