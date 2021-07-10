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

struct STUDENT {
	string fullName;
	string DOB;
	int studentCode;
};

bool isFirstTime() {
	ifstream fin(SUBFOLDER_NAME, ios::in);
	if (!fin.is_open()) {
		return true;
	}
	fin.close();
	return false;
}

void initDatasetFolder() {
	string datasetName;
	cout << "Enter name of the folder that includes dataset: \n";
	cin.ignore();
	getline(cin, datasetName);
	cout << "Please wait while we initialize the metadata files...\n";
	createMetadata(datasetName);
	loadToRAM();
	cout << "Initialization completed.\n";
}

bool errorCheck(int option) {
	const int maxOptionNum = 6;
	return (option <= 0 || option > maxOptionNum);
}

void searchData() {
	string keywords;
	cout << "Enter the keywords to search:\n";
	cin.ignore();
	getline(cin, keywords);
	searchSentence(keywords);
}

void showStudentInfor(STUDENT s) {
	cout << "Full name: " << s.fullName << "\n";
	cout << "Date of birth: " << s.DOB << "\n";
	cout << "Student ID: " << s.studentCode << "\n";
}

void information() {
	cout << "PROJECT SEARCH ENGINE\n";
	STUDENT s1 = { "Nguyen Van Loc", "18/08/2002", 20120131 };
	STUDENT s2 = { "Vo Trong Nghia", "", 20120536 };
	cout << "Member 1.\n";
	showStudentInfor(s1);
	cout << "Member 2.\n";
	showStudentInfor(s2);
}

void showMenu() {
	cout << "Here is the menu of the application.\n";
	cout << "1. Add a folder to the dataset.\n";
	cout << "2. Add a file to the dataset. \n";
	cout << "3. Change the location of folder that includes dataset.\n";
	cout << "4. Search.\n";
	cout << "5. About us.\n";
	cout << "6. Exit the application.\n";
}

void menu() {
	if (isFirstTime()) {
		cout << "First time using? Please help us to create something.\n";
		initDatasetFolder();
	}
	int option = 0;
	char userChoice = 'Y';
	do {
		showMenu();
		cout << "Enter the number of the options that you choose.\n";
		cin >> option;
		if (errorCheck(option)) {
			cout << "Invalid option. Please enter another number.\n";
		}
		else {
			if (option == 1) {

			}
			else if (option == 2) {

			}
			else if (option == 3) {
				string remove = "rmdir /s /q metadata ";
				evalCommand(remove);
				initDatasetFolder();
			}
			else if (option == 4) {
				searchData();
			}
			else if (option == 5) {
				information();
			}
			else if (option == 6) {
				exit(0);
			}
			cout << "Do you want to continue? Press Y/y for yes, N/n for no.";
			cin >> userChoice;
		}
	} while (userChoice == 'Y' || userChoice == 'y');
	string removeFile = "del /q " + (string)SUBFOLDER_NAME;
	evalCommand(removeFile);
}