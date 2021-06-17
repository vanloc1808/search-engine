#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char command[100] = { 0 };
    string path = "new test";
    sprintf(command, "dir \"%s\" /s /b /o:n /ad > path.txt", path.c_str());
    system(command);

    string* folderPath = (string*)calloc(100, sizeof(string));
    string* subFolderName = (string*)calloc(100, sizeof(string));
    int idx = 0;
    ifstream fPath;
    fPath.open("path.txt");
    while (getline(fPath, folderPath[idx])) {
        int len = folderPath[idx].length();
        if (len == 0) {
            break;
        }
        int pos = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (folderPath[idx][i] == '\\') {
                pos = i;
                break;
            }
        }
        subFolderName[idx] = "";
        for (; pos < len; pos++) {
            subFolderName[idx] += folderPath[idx][pos];
        }
        idx++;
    }

    fPath.close();

    return 0;
}

