#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <string>
#include <string.h>
#include "FileProgression.h"

using namespace std;

void fileInput() {
	string folderPath;
	getline(cin, folderPath);
	char command[100] = { 0 };
	sprintf(command, "dir %s /s/b path.txt", folderPath.c_str());
	system(command);
}