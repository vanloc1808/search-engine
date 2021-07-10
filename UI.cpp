#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define METADATA_NAME "metadata"

#define SUBFOLDER_NAME "FolderList.txt"

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <fstream>
#include <codecvt>
#include <sstream>
#include "Normalizer.h"
#include "FileProgression.h"
#include "TF.h"
#include "IDF.h"
#include "Utility.h"

using namespace std;

bool isFirstTime() {
	ifstream fin(SUBFOLDER_NAME, ios::in);
	if (!fin.is_open()) {
		return false;
	}
	fin.close();
	return true;
}

void firstTimeUsing() {
	string datasetName;
	cout << "Enter name of the folder that includes dataset: \n";
	getline(cin, datasetName);
	cout << "Please wait while we initialize the metadata files.\n";
	createMetadata(datasetName);
	cout << "Initialization completed.\n";
}

bool errorCheck(int option) {
	const int maxOptionNum = 5;
	return (option <= 0 || option > maxOptionNum);
}

void menu() {
	cout << "Here is the menu of the application.\n";
	cout << "1. Add a folder to the dataset.\n";
	cout << "2. Change the location of folder that includes dataset.\n";
	cout << "3. Search.\n";

	cout << ". Exit the application.\n";
	int option = 0;
	cout << "Enter the number of the options that you choose.\n";
	cin >> option;
	if (errorCheck(option)) {
		cout << "Invalid option. Please enter another number.\n";
	}
	else {

	}
}