#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <string>
#include <string.h>
#include <fstream>
#include "FileProgression.h"

using namespace std;

void getSubFolderDirectory(string folder) {
	//the parameter folder is usually "new test"
    char command[100] = { 0 };
    sprintf(command, "dir \"%s\" /s /b /o:n /ad > Path.txt", folder.c_str());
    system(command);
}

void getSubFolderName(string folder, string*& subFolderName) { //folder is usually "new test"
    ifstream fPath;
    fPath.open("Path.txt");
    ofstream subFol;
    subFol.open("SubFolderName.txt");
    subFolderName = new string[100];
    int idx = 0;
    string folderPath;
    while (getline(fPath, folderPath)) {
        subFolderName[idx] = "";
        int pos = 0;
        int len = folderPath.length();
        for (int i = len - 1; i >= 0; i--) {
            if (folderPath[i] == '\\') {
                pos = i;
                break;
            }
        }
        pos++;
        for (; pos < len; pos++) {
            subFolderName[idx] += folderPath[pos];
        }
        subFol << subFolderName[idx] << "\n";
    }
    fPath.close();
    subFol.close();
}

void getFileDirectory(string*& folderName) {

}