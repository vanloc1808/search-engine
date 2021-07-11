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
		fin.close();
		return true;
	}
	fin.close();
	return false;
}

void initDatasetFolder() {
	string datasetName;
	cout << "Enter name of the folder that includes dataset: \n";
	getline(cin, datasetName);
	cout << "Please wait while we initialize the metadata files...\n";
	createMetadata(datasetName);
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
	STUDENT s2 = { "Vo Trong Nghia", "04/04/2002", 20120536 };
	cout << "Member 1.\n";
	showStudentInfor(s1);
	cout << "Member 2.\n";
	showStudentInfor(s2);
}

void showMenu() {
	cout << "Here is the menu of the application.\n";
	cout << "1. Add a folder to the dataset.\n";
	cout << "2. Change the location of folder that includes dataset.\n";
	cout << "3. Search.\n";
	cout << "4. About us.\n";
	cout << "5. Exit the application.\n";
}

void updateFolder()
{
	cout << "Enter path to the folder you want to add:";
	string path;
	cin.ignore();
	getline(cin, path);
	updateMetadata(path);
}

void menu() {
	if (isFirstTime()) {
		cout << "First time using? Please help us to create something.\n";
		initDatasetFolder();
	}
	int option = 0;

	cout << "Loading database!, please patience\n";
	loadToRAM();

	do {
		evalCommand("cls");
		showMenu();
		cout << "Enter the number of the options that you choose.\n";
		cout << "Your option: ";
		cin >> option;
		if (errorCheck(option)) {
			cout << "Invalid option. Please enter another number.\n";
		}
		else {
			if (option == 1) {
				updateFolder();
				cout << "Reloading database!, please patience\n";
				freeRAM();
				loadToRAM();
			}
			else if (option == 2) {
				freeRAM();
				string remove = "rmdir /s /q metadata ";
				evalCommand(remove);
				initDatasetFolder();
			}
			else if (option == 3) {
				searchData();
			}
			else if (option == 4) {
				information();
			}
			else if (option == 5) {
				break;
			}
		}
		evalCommand("pause");
	} while (true);
}