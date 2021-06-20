#define _CRT_SECURE_NO_WARNINGS

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

using namespace std;

void getSubFolderDirectory(string folder) {
	//the parameter folder is usually "new test"
    char command[100] = { 0 };
    sprintf(command, "dir \"%s\" /s /b /o:n /ad > Path.txt", folder.c_str());
    system(command);
}

void getSubFolderName(string folder, string*& subFolderName, int& idx) { //folder is usually "new test"
    ifstream fPath;
    fPath.open("Path.txt");
    ofstream subFol;
    subFol.open("SubFolderName.txt");
    subFolderName = new string[100];
    idx = 0;
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
        idx++;
    }
    fPath.close();
    subFol.close();
}

void getFileDirectory(string folder, string* subFolderName, int idx) { //folder is usually "new test"
    system("mkdir metadata");
    char command[100] = { 0 };
    for (int i = 0; i < idx; i++) {
        string name = "metadata\\" + subFolderName[i] + ".txt";
        subFolderName[i] = folder + "\\" + subFolderName[i];
        sprintf(command, "dir \"%s\" /s /b /o:n > \"%s\"", subFolderName[i].c_str(), name.c_str());
        system(command);
    }
}

void fileDirecProgression(string folder, string*& subFolderName) {
    getSubFolderDirectory(folder);
    int idx = 0;
    getSubFolderName(folder, subFolderName, idx);
    getFileDirectory(folder, subFolderName, idx);
    delete[]subFolderName;
}
/*
void convertToVE(wifstream& fin, wstring& s, string* strArr, unsigned int& size, unsigned int& capacity){
    string tempStr = VEconvert(s);
    if (tempStr.length() == 0) {
        return;
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

void everyFolder(string textFile) {
    wifstream fin(textFile);
    fin.imbue(locale(locale::empty(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    wstring s;
    string* strArr;
    unsigned int capacity = 100;
    strArr = new string[capacity];
    unsigned int size = 0;
    while (fin >> s) {
        convertToVE(fin, s, strArr, size, capacity);
    }

    fin.close();
}
*/

void fileInput() {
    ifstream subFolder;
    subFolder.open("SubFolderName.txt");
    string subFolName;
    string* strArr;
    unsigned int capacity = 100;
    unsigned int size = 0;
    while (getline(subFolder, subFolName)) {
        if (subFolName.length() == 0) {
            break;
        }
        string directory = "metadata\\" + subFolName + ".txt";
        ifstream file;
        file.open(directory);
        string textFile;
        while (getline(file, textFile)) {
            wifstream fin(textFile);
            fin.imbue(locale(locale::empty(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
            wstring s;
            strArr = new string[capacity];
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
            size = 0;
            fin.close();
        }
        file.close();
    }
    delete[]strArr;
    subFolder.close();
}