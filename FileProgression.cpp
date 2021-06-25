#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define PATH_NAME "Path.txt"

#define METADATA_NAME "metadata"

#define SUBFOLDER_NAME "SubFolderName.txt"

#define TF_NAME "tf"

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <string>
#include <string.h>
#include <fstream>
#include <codecvt>
#include "Normalizer.h"
#include "FileProgression.h"
#include "TF.h"
#include "TISManipulation.h"

using namespace std;

int x = 0;
TF_list L;

void getSubFolderDirectory(string folder) {
	//the parameter folder is usually "new test"
    char command[100] = { 0 };
    sprintf(command, "dir \"%s\" /s /b /o:n /ad > " PATH_NAME "", folder.c_str());
    system(command);
}

string extractName(string path)
{
	int pos = path.length() - 1;
	string res = "";
	for (; pos >= 0 && path[pos] != '\\'; pos--);
	for (++pos; pos < path.length(); pos++) res += path[pos];
	return res;
}

void getSubFolderName(string folder/*, string*& subFolderName, int& idx*/) { //folder is usually "new test"
    ifstream fPath;
    fPath.open(PATH_NAME);
    ofstream subFol;
    subFol.open(SUBFOLDER_NAME);
    //subFolderName = new string[100];
    //idx = 0;
    string folderPath;
    while (getline(fPath, folderPath)) {
        /*subFolderName[idx] = "";
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
        }*/
        subFol << extractName(folderPath) << "\n";
        //idx++;
    }
    fPath.close();
    subFol.close();
	system("del /q " PATH_NAME "");
}

void getFileDirectory(string folder/*, string* subFolderName, int idx*/) { //folder is usually "new test"
    system("mkdir " METADATA_NAME "");
	string command = "";
	ifstream fr(SUBFOLDER_NAME, ios::in);
	while (getline(fr, command))
	{
		string listFile = "" METADATA_NAME "\\" + command + "_temp.txt";
		command = "dir \"" + folder + "\\" + command + "\" /s /b /o:n > \"" + listFile + "\"";
		system(command.c_str());

	}
	fr.close();
	fr.open(SUBFOLDER_NAME, ios::in);
	while (getline(fr, command)) {
		string tempListFile = "" METADATA_NAME "\\" + command + "_temp.txt";
		ifstream temp(tempListFile, ios::in);
		string listFile = "" METADATA_NAME "\\" + command + ".txt";
		ofstream direc(listFile, ios::out);
		string tempStr = "";
		while (getline(temp, tempStr)) {
			direc << extractName(tempStr) << "\n";
		}
		temp.close();
		direc.close();
		string toDelete = "del /q \"" + tempListFile + "\"";
		system(toDelete.c_str());
	}
    /*for (int i = 0; i < idx; i++) {
        string name = "metadata\\" + subFolderName[i] + ".txt";
        subFolderName[i] = folder + "\\" + subFolderName[i];
        sprintf(command, "dir \"%s\" /s /b /o:n > \"%s\"", subFolderName[i].c_str(), name.c_str());
        system(command);
    }*/
	fr.close();
}

void fileDirecProgression(string folder/*, string*& subFolderName*/) {
    getSubFolderDirectory(folder);
    int idx = 0;
    getSubFolderName(folder/*, subFolderName, idx*/);
    getFileDirectory(folder/*, subFolderName, idx*/);
    /*delete[]subFolderName;*/
}

void IterateFile(std::string &directory, std::wstring &s, unsigned int &size, unsigned int &capacity, std::string * &strArr)
{
	ifstream file;
	file.open(directory);
	string textFile;
	while (getline(file, textFile)) {
		wifstream fin(textFile);
		fin.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
		while (fin >> s) {
			string tempStr = VEconvert(s);
			if (tempStr.length() == 0) {
				continue;
			}
			if (size == capacity) {
				capacity += 100;
				string* temp = new string[capacity];
				for (int i = 0; i < capacity - 100; i++) {
					temp[i] = strArr[i];
				}
				delete[]strArr;
				strArr = temp;
			}
			strArr[size] = tempStr;
			size++;
		}

		sort_String(strArr, size);
		
		L.size = 0;
		TFList_Input(L, strArr, size);
		
		char path[19];
		itoa(x, path, 10);
		strcat(path, ".tf");
		SaveTFList(path, L);
		x++;
		size = 0;
		fin.close();
	}
	file.close();
}

void fileInput() {
	TFListInit(L);
    ifstream subFolder;
    subFolder.open(SUBFOLDER_NAME);
    string subFolName;
    string* strArr;
    unsigned int capacity = 100;
    unsigned int size = 0;
	wstring s;
	strArr = new string[capacity];
    while (getline(subFolder, subFolName)) {
        if (subFolName.length() == 0) {
            break;
        }
        string directory = "" METADATA_NAME "\\" + subFolName + ".txt";
		IterateFile(directory, s, size, capacity, strArr);
    }
    delete[]strArr;
    subFolder.close();
	FreeTFList(L);
}

void createTF() {
	ifstream subFol(SUBFOLDER_NAME, ios::in);
	string folderName = "";
	while (getline(subFol, folderName)) {
		string toCreate = "mkdir \""  METADATA_NAME + '\\' + folderName + "\"";
		system(toCreate.c_str());
		string listFile = "" METADATA_NAME "\\" + folderName + ".txt";
		ifstream fr(listFile, ios::in);
		string fileName = "";
		while (getline(fr, fileName)) {
			string tfName = "" METADATA_NAME "\\" + folderName + fileName + ".tf";
			ofstream tf(tfName);
			tf.close();
		}

		fr.close();
	}

	subFol.close();
}