#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define PATH_NAME "Path.txt"

#define METADATA_NAME "metadata"

#define SUBFOLDER_NAME "SubFolderName.txt"

#define NEWTEST_NAME "new test";

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

void getSubFolderName(string folder) { //folder is usually "new test"
    ifstream fPath;
    fPath.open(PATH_NAME);
    ofstream subFol;
    subFol.open(SUBFOLDER_NAME);
    string folderPath;
    while (getline(fPath, folderPath)) 
        subFol << extractName(folderPath) << "\n";
    fPath.close();
    subFol.close();
	system("del /q " PATH_NAME "");
}

void getFileDirectory(string folder) { //folder is usually "new test"
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
	fr.close();
}

void fileDirecProgression(string folder) {
    getSubFolderDirectory(folder);
    int idx = 0;
    getSubFolderName(folder);
    getFileDirectory(folder);
}

void IterateFile(std::string &directory, std::wstring &s, unsigned int &size, unsigned int &capacity, std::string * &strArr)
{
	ifstream file;
	file.open( "" METADATA_NAME "\\" + directory + ".txt");
	string textFile;
	while (getline(file, textFile)) {
		wifstream fin("new test\\" + directory + "\\" + textFile);
		fin.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
		while (fin >> s) {
			string tempStr = VEconvert(s);
			if (tempStr.length() == 0) {
				continue;
			}
			if (size == capacity) {
				capacity += 1000;
				string* temp = new string[capacity];
				for (int i = 0; i < capacity - 1000; i++) {
					temp[i] = strArr[i];
				}
				delete[]strArr;
				strArr = temp;
			}
			strArr[size] = tempStr;
			size++;
		}

		//sort_String(strArr, size);
		sort_multiThread(strArr, size);
		
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
    unsigned int capacity = 1000;
    unsigned int size = 0;
	wstring s;
	strArr = new string[capacity];
    while (getline(subFolder, subFolName)) {
        if (subFolName.length() == 0) {
            break;
        }
        //string directory = "" METADATA_NAME "\\" + subFolName + ".txt";
		//IterateFile(directory, s, size, capacity, strArr);
		IterateFile(subFolName, s, size, capacity, strArr);
    }
    delete[]strArr;
    subFolder.close();
	FreeTFList(L);
}

TF_list createTF(string filePath) {
	TF_list L;
	TFListInit(L);
	wifstream fin(filePath, ios::in);
	fin.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
	wstring s;
	string* strArr = NULL;
	strArr = new string[1000];
	while (fin >> s) {
		string tempStr = VEconvert(s);
		if (tempStr.length() == 0) {
			continue;
		}
		if (L.size == L.capacity) {
			L.capacity += 1000;
			string* temp = new string[L.capacity];
			for (int i = 0; i < L.capacity - 1000; i++) {
				temp[i] = strArr[i];
			}
			delete[]strArr;
			strArr = temp;
		}
		strArr[L.size] = tempStr;
		L.size++;
	}
	sort_multiThread(strArr, L.size);
	TFList_Input(L, strArr, L.size);
	fin.close();
	return L;
}

void createMetadata(string folderDataset) {
	ifstream subFol(SUBFOLDER_NAME, ios::in);
	string folderName = "";
	while (getline(subFol, folderName)) {
		string toCreate = "mkdir \""  METADATA_NAME + '\\' + folderName + "\"";
		system(toCreate.c_str());
		string listFile = "" METADATA_NAME "\\" + folderName + ".txt";
		ifstream fr(listFile, ios::in);
		string fileName = "";
		while (getline(fr, fileName)) {
			string tfPath = "" METADATA_NAME "\\" + folderName + '\\' + fileName + ".tf";
			/*ofstream tf(tfName);
			tf.close();*/
			string filePath = folderDataset + "\\" + folderName + "\\" + fileName;
			TF_list L = createTF(filePath);
			SaveTFList((char*)tfPath.c_str(), L);
		}
		fr.close();
	}

	subFol.close();
}

IDF_list createIDF(string folderPath) {
	string directory = folderPath + ".txt"; // for example, metadata\Am nhac -> metadata\Am nhac.txt
	string fileName = "";
	string folderName = "";
	for (int i = folderPath.length() - 5;; i--) { //we skip four character ".txt"
		folderName += folderPath[i];
	}
	std::reverse(folderName.begin(), folderName.end());
	ifstream path(folderPath, ios::in);
	string* strArr = NULL;
	strArr = new string[1000];
	IDF_list idfL;
	IDFListInit(idfL);
	int size = 0;// number of files
	int nWords = 0; //number of words
	while (getline(path, fileName)) {
		if (fileName.length() == 0) {
			continue;
		}
		size++;
		string tfPath = folderPath + fileName + ".tf";
		TF_list tfL;
		LoadTFList((char*)tfPath.c_str(), tfL);
		for (int i = 0; i < tfL.size; i++) {
			string tempStr = tfL.arrNorm[i].word;
			if (tempStr.length() == 0) {
				continue;
			}
			nWords++;
			if (idfL.size == idfL.capacity) {
				idfL.capacity += 1000;
				string* temp = new string[idfL.capacity];
				for (int j = 0; j < idfL.capacity - 1000; j++) {
					temp[j] = strArr[j];
				}
				delete[]strArr;
				strArr = temp;
			}
			strArr[idfL.size] = tempStr;
			idfL.size++;
		}
	}
	sort_multiThread(strArr, idfL.size);
	IDFList_Input(idfL, folderName, size, strArr, nWords);
	path.close();
	return idfL;
}