#include "UI.h"

#include <codecvt>
#include <fstream>
#include <iostream>
#include <string>

#include "FileProgression.h"
#include "Utility.h"

using namespace std;

void initDatasetFolder() {
	string dataset_name;
	cout << "Enter name of the folder that includes dataset: \n";
	getline(cin, dataset_name);
	cout << "Please wait while we initialize the metadata files...\n";
	createMetadata(dataset_name);
	cout << "Initialization completed.\n";
}

bool errorCheck(const int Option) {
	const int max_option_num = 5;
	return (Option <= 0 || Option > max_option_num);
}

void searchData() {
	string keywords;
	cout << "Enter the keywords to search:\n";
	cin.ignore();
	getline(cin, keywords);
	searchSentence(keywords);
}

// information tab
void information() {
	cout << "PROJECT SEARCH ENGINE\n";

	cout << "Member 1.\n";
	cout << "Full name: " << "Nguyen Van Loc" << "\n";
	cout << "Date of birth: " << "18/08/2002" << "\n";
	cout << "Student ID: " << 20120131 << "\n";
	
	cout << "Member 2.\n";
	cout << "Full name: " << "Vo Trong Nghia" << "\n";
	cout << "Date of birth: " << "04/04/2002" << "\n";
	cout << "Student ID: " << 20120536 << "\n";
}

// Menu of program
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
	cout << "Enter path to the folder you want to add: ";
	string path;
	cin.ignore();
	getline(cin, path);
	updateMetadata(path);
}

void menu() {
	// Load database for first time
	if (isFirstTime()) {
		cout << "First time using? Please help us to create something.\n";
		initDatasetFolder();
	}
	cout << "Loading database!, please be patient!\n";
	loadToRAM();
	
	do {
		int option = 0;
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
				cout << "Reloading database!, please be patient\n";
				freeRAM();
				loadToRAM();
			}
			else if (option == 2) {
				freeRAM();
				string remove = "rmdir /s /q metadata ";
				evalCommand(remove);
				cin.ignore();
				initDatasetFolder();
				loadToRAM();
			}
			else if (option == 3) {
				searchData();
			}
			else if (option == 4) {
				information();
			}
			else if (option == 5) {
				cout << "Thank you very much! See you again!\n";
				break;
			}
			evalCommand("pause");
		}
	} while (true);
}